#include "Arena.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdlib>
#include <dlfcn.h>
#include <thread>
#include <chrono>
#include <cmath>

Arena::Arena()
    : m_height(20),
      m_width(20),
      m_max_rounds(10000),
      m_sleep_interval(0.5),
      m_live_mode(true),
      m_num_flamethrowers(5),
      m_num_pits(5),
      m_num_mounds(5),
      m_round(1),
      m_rng(std::random_device{}())
{
}

bool Arena::load_config(const std::string& filename) {
    std::ifstream fin(filename);

    if (!fin) {
        std::cerr << "Could not open config file: " << filename << "\n";
        return false;
    }

    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string key;

        std::getline(ss, key, ':');

        if (key == "Arena_Size") {
            ss >> m_height >> m_width;
        }
        else if (key == "Max_Rounds") {
            ss >> m_max_rounds;
        }
        else if (key == "Sleep_interval") {
            ss >> m_sleep_interval;
        }
        else if (key == "Game_State_Live") {
            std::string value;
            ss >> value;
            m_live_mode = value == "true";
        }
        else if (key == "Flamethrowers") {
            ss >> m_num_flamethrowers;
        }
        else if (key == "Pits") {
            ss >> m_num_pits;
        }
        else if (key == "Mounds") {
            ss >> m_num_mounds;
        }
    }

    return true;
}

void Arena::setup() {
    initialize_grid();
    place_obstacles();
    load_robots();
}

void Arena::initialize_grid() {
    m_grid.clear();
    m_grid.resize(m_height, std::vector<Cell>(m_width));
}

void Arena::place_obstacles() {
    for (int i = 0; i < m_num_mounds; i++) {
        place_random_obstacle(CellType::Mound, 'M');
    }

    for (int i = 0; i < m_num_pits; i++) {
        place_random_obstacle(CellType::Pit, 'P');
    }

    for (int i = 0; i < m_num_flamethrowers; i++) {
        place_random_obstacle(CellType::Flame, 'F');
    }
}

void Arena::place_random_obstacle(CellType type, char symbol) {
    while (true) {
        int row = random_int(0, m_height - 1);
        int col = random_int(0, m_width - 1);

        if (m_grid[row][col].type == CellType::Empty) {
            m_grid[row][col].type = type;
            m_grid[row][col].symbol = symbol;
            return;
        }
    }
}

void Arena::load_robots() {
    std::vector<char> symbols = {
        '@', '$', '#', '&', '!', '%', '*', '+', '?', '~'
    };

    int symbol_index = 0;

    if (!std::filesystem::exists("robots")) {
        std::cerr << "No robots directory found.\n";
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator("robots")) {
        if (!entry.is_regular_file()) continue;

        std::string filename = entry.path().string();
        std::string basename = entry.path().filename().string();

        if (entry.path().extension() != ".cpp") continue;
        if (basename.rfind("Robot_", 0) != 0) continue;

        std::string shared_lib = filename + ".so";

        std::string compile_cmd =
            "g++ -shared -fPIC -o " + shared_lib + " " +
            filename + " RobotBase.o -I. -std=c++20";

        std::cout << "Compiling " << filename << "...\n";

        int compile_result = std::system(compile_cmd.c_str());

        if (compile_result != 0) {
            std::cerr << "Failed to compile " << filename << "\n";
            continue;
        }

        void* handle = dlopen(shared_lib.c_str(), RTLD_LAZY);

        if (!handle) {
            std::cerr << "Failed to load " << shared_lib << ": " << dlerror() << "\n";
            continue;
        }

        RobotFactory create_robot =
            reinterpret_cast<RobotFactory>(dlsym(handle, "create_robot"));

        if (!create_robot) {
            std::cerr << "Failed to find create_robot in " << shared_lib
                      << ": " << dlerror() << "\n";
            dlclose(handle);
            continue;
        }

        RobotBase* robot = create_robot();

        if (robot == nullptr) {
            std::cerr << "create_robot returned nullptr\n";
            dlclose(handle);
            continue;
        }

        char symbol = symbols[symbol_index % symbols.size()];
        symbol_index++;

        place_robot(robot, symbol);
    }
}

void Arena::place_robot(RobotBase* robot, char symbol) {
    while (true) {
        int row = random_int(0, m_height - 1);
        int col = random_int(0, m_width - 1);

        if (m_grid[row][col].type == CellType::Empty) {
            robot->m_character = symbol;
            robot->set_boundaries(m_height - 1, m_width - 1);
            robot->move_to(row, col);

            m_grid[row][col].type = CellType::Robot;
            m_grid[row][col].robot = robot;
            m_grid[row][col].symbol = symbol;

            RobotInfo info;
            info.robot = robot;
            info.row = row;
            info.col = col;
            info.symbol = symbol;

            m_robots.push_back(info);

            return;
        }
    }
}

void Arena::run() {
    while (m_round <= m_max_rounds) {
        std::cout << "\n=========== starting round " << m_round << " ===========\n\n";

        print_arena();

        if (only_one_living_robot()) {
            std::cout << "Game over. Winner found.\n";
            return;
        }

        for (RobotInfo& info : m_robots) {
            RobotBase* robot = info.robot;

            if (is_dead(robot)) {
                std::cout << robot->m_name << " " << info.symbol << " - is out\n";
                continue;
            }

            std::cout << robot->print_stats() << "\n";

            int radar_direction = 0;
            robot->get_radar_direction(radar_direction);

            std::vector<RadarObj> radar_results =
                perform_radar_scan(robot, radar_direction);

            robot->process_radar_results(radar_results);

            int shot_row = 0;
            int shot_col = 0;

            bool wants_to_shoot = robot->get_shot_location(shot_row, shot_col);

            if (wants_to_shoot) {
                handle_shot(robot, shot_row, shot_col);
            }
            else {
                int move_direction = 0;
                int distance = 0;

                robot->get_move_direction(move_direction, distance);
                handle_move(robot, move_direction, distance);
            }

            if (m_live_mode) {
                std::this_thread::sleep_for(
                    std::chrono::duration<double>(m_sleep_interval)
                );
            }
        }

        m_round++;
    }

    std::cout << "Max rounds reached. No winner.\n";
}

void Arena::print_arena() const {
    std::cout << "   ";

    for (int col = 0; col < m_width; col++) {
        std::cout << col << " ";
    }

    std::cout << "\n";

    for (int row = 0; row < m_height; row++) {
        std::cout << row << " ";

        if (row < 10) std::cout << " ";

        for (int col = 0; col < m_width; col++) {
            std::cout << m_grid[row][col].symbol << " ";
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

bool Arena::inside(int row, int col) const {
    return row >= 0 && row < m_height && col >= 0 && col < m_width;
}

bool Arena::is_dead(RobotBase* robot) const {
    return robot == nullptr || robot->get_health() <= 0;
}

bool Arena::only_one_living_robot() const {
    int living = 0;

    for (const RobotInfo& info : m_robots) {
        if (!is_dead(info.robot)) {
            living++;
        }
    }

    return living <= 1;
}

RobotInfo* Arena::find_robot_info(RobotBase* robot) {
    for (RobotInfo& info : m_robots) {
        if (info.robot == robot) {
            return &info;
        }
    }

    return nullptr;
}

std::vector<RadarObj> Arena::perform_radar_scan(RobotBase* robot, int direction) {
    std::vector<RadarObj> results;

    RobotInfo* info = find_robot_info(robot);

    if (info == nullptr) {
        return results;
    }

    int row = info->row;
    int col = info->col;

    if (direction == 0) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;

                scan_cell(results, row + dr, col + dc);
            }
        }

        return results;
    }

    if (direction < 1 || direction > 8) {
        return results;
    }

    int dr = directions[direction].first;
    int dc = directions[direction].second;

    int step = 1;

    while (true) {
        int center_row = row + dr * step;
        int center_col = col + dc * step;

        if (!inside(center_row, center_col)) {
            break;
        }

        scan_cell(results, center_row, center_col);

        /*
            Make radar 3 cells wide.

            For vertical scans, check left and right.
            For horizontal scans, check above and below.
            For diagonal scans, this checks nearby side cells.
        */
        if (dr != 0 && dc == 0) {
            scan_cell(results, center_row, center_col - 1);
            scan_cell(results, center_row, center_col + 1);
        }
        else if (dr == 0 && dc != 0) {
            scan_cell(results, center_row - 1, center_col);
            scan_cell(results, center_row + 1, center_col);
        }
        else {
            scan_cell(results, center_row - dr, center_col);
            scan_cell(results, center_row, center_col - dc);
        }

        step++;
    }

    return results;
}

void Arena::scan_cell(std::vector<RadarObj>& results, int row, int col) {
    if (!inside(row, col)) return;

    if (m_grid[row][col].type == CellType::Empty) return;

    char typeChar = m_grid[row][col].symbol;


    if (m_grid[row][col].type == CellType::Robot) {
        typeChar = 'R';
    }
    else if (m_grid[row][col].type == CellType::DeadRobot) {
        typeChar = 'X';
    }

    results.emplace_back(typeChar, row, col);
}

void Arena::handle_move(RobotBase* robot, int direction, int distance) {
    RobotInfo* info = find_robot_info(robot);

    if (info == nullptr) return;

    if (direction < 1 || direction > 8) return;

    int max_speed = robot->get_move_speed();

    if (distance > max_speed) {
        distance = max_speed;
    }

    if (distance < 0) {
        distance = 0;
    }

    int dr = directions[direction].first;
    int dc = directions[direction].second;

    for (int step = 0; step < distance; step++) {
        int next_row = info->row + dr;
        int next_col = info->col + dc;

        if (!inside(next_row, next_col)) {
            return;
        }

        Cell& next_cell = m_grid[next_row][next_col];

        if (next_cell.type == CellType::Mound ||
            next_cell.type == CellType::Robot ||
            next_cell.type == CellType::DeadRobot) {
            return;
        }

        m_grid[info->row][info->col].type = CellType::Empty;
        m_grid[info->row][info->col].robot = nullptr;
        m_grid[info->row][info->col].symbol = '.';

        info->row = next_row;
        info->col = next_col;

        robot->move_to(info->row, info->col);

        if (next_cell.type == CellType::Pit) {
            robot->disable_movement();

            next_cell.type = CellType::Robot;
            next_cell.robot = robot;
            next_cell.symbol = info->symbol;

            std::cout << robot->m_name << " fell into a pit at ("
                      << next_row << "," << next_col << ")\n";

            return;
        }

        if (next_cell.type == CellType::Flame) {
            std::cout << robot->m_name << " moved through fire at ("
                      << next_row << "," << next_col << ")\n";

            damage_robot(robot, 30, 50);

            if (is_dead(robot)) {
                next_cell.type = CellType::DeadRobot;
                next_cell.robot = robot;
                next_cell.symbol = 'X';
                return;
            }
        }

        next_cell.type = CellType::Robot;
        next_cell.robot = robot;
        next_cell.symbol = info->symbol;
    }
}

void Arena::handle_shot(RobotBase* robot, int shot_row, int shot_col) {
    RobotInfo* shooter = find_robot_info(robot);

    if (shooter == nullptr) return;

    if (!inside(shot_row, shot_col)) {
        return;
    }

    int dr = shot_row - shooter->row;
    int dc = shot_col - shooter->col;

    if (dr != 0) {
        dr = dr / std::abs(dr);
    }

    if (dc != 0) {
        dc = dc / std::abs(dc);
    }

    if (dr == 0 && dc == 0) {
        return;
    }

    WeaponType weapon = robot->get_weapon();

    if (weapon == railgun) {
        handle_railgun(robot, dr, dc);
    }
    else if (weapon == grenade) {
        handle_grenade(robot, shot_row, shot_col);
    }
    else if (weapon == flamethrower) {
        handle_flamethrower(robot, dr, dc);
    }
    else if (weapon == hammer) {
        handle_hammer(robot, dr, dc);
    }
}

void Arena::handle_railgun(RobotBase* robot, int dr, int dc) {
    RobotInfo* shooter = find_robot_info(robot);

    if (shooter == nullptr) return;

    int row = shooter->row + dr;
    int col = shooter->col + dc;

    while (inside(row, col)) {
        RobotBase* target = m_grid[row][col].robot;

        if (target != nullptr && target != robot && !is_dead(target)) {
            std::cout << robot->m_name << " hits "
                      << target->m_name << " with railgun\n";

            damage_robot(target, 10, 20);
        }

        row += dr;
        col += dc;
    }
}

void Arena::handle_grenade(RobotBase* robot, int shot_row, int shot_col) {
    if (robot->get_grenades() <= 0) {
        std::cout << robot->m_name << " tried to fire grenade but has none left\n";
        return;
    }

    robot->decrement_grenades();

    for (int row = shot_row - 1; row <= shot_row + 1; row++) {
        for (int col = shot_col - 1; col <= shot_col + 1; col++) {
            if (!inside(row, col)) continue;

            RobotBase* target = m_grid[row][col].robot;

            if (target != nullptr && target != robot && !is_dead(target)) {
                std::cout << robot->m_name << " hits "
                          << target->m_name << " with grenade\n";

                damage_robot(target, 10, 40);
            }
        }
    }
}

void Arena::handle_flamethrower(RobotBase* robot, int dr, int dc) {
    RobotInfo* shooter = find_robot_info(robot);

    if (shooter == nullptr) return;

    for (int step = 1; step <= 4; step++) {
        int center_row = shooter->row + dr * step;
        int center_col = shooter->col + dc * step;

        if (!inside(center_row, center_col)) break;

        for (int offset = -1; offset <= 1; offset++) {
            int row = center_row;
            int col = center_col;

            if (dr != 0 && dc == 0) {
                col += offset;
            }
            else if (dr == 0 && dc != 0) {
                row += offset;
            }
            else {
                row += offset;
                col -= offset;
            }

            if (!inside(row, col)) continue;

            RobotBase* target = m_grid[row][col].robot;

            if (target != nullptr && target != robot && !is_dead(target)) {
                std::cout << robot->m_name << " hits "
                          << target->m_name << " with flamethrower\n";

                damage_robot(target, 30, 50);
            }
        }
    }
}

void Arena::handle_hammer(RobotBase* robot, int dr, int dc) {
    RobotInfo* shooter = find_robot_info(robot);

    if (shooter == nullptr) return;

    int row = shooter->row + dr;
    int col = shooter->col + dc;

    if (!inside(row, col)) return;

    RobotBase* target = m_grid[row][col].robot;

    if (target != nullptr && target != robot && !is_dead(target)) {
        std::cout << robot->m_name << " hits "
                  << target->m_name << " with hammer\n";

        damage_robot(target, 50, 60);
    }
}

void Arena::damage_robot(RobotBase* target, int min_damage, int max_damage) {
    if (target == nullptr || is_dead(target)) return;

    int raw_damage = random_int(min_damage, max_damage);

    int armor = target->get_armor();

    double reduction = armor * 0.10;
    int final_damage = static_cast<int>(raw_damage * (1.0 - reduction));

    if (final_damage < 0) {
        final_damage = 0;
    }

    std::cout << target->m_name << " takes "
              << final_damage << " damage\n";

    target->take_damage(final_damage);

    if (armor > 0) {
        target->reduce_armor(1);
    }

    mark_dead_if_needed(target);
}

void Arena::mark_dead_if_needed(RobotBase* robot) {
    if (!is_dead(robot)) return;

    RobotInfo* info = find_robot_info(robot);

    if (info == nullptr) return;

    m_grid[info->row][info->col].type = CellType::DeadRobot;
    m_grid[info->row][info->col].robot = robot;
    m_grid[info->row][info->col].symbol = 'X';

    std::cout << robot->m_name << " has been destroyed\n";
}

int Arena::random_int(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(m_rng);
}