#pragma once

#include <vector>
#include <string>
#include <random>

#include "RobotBase.h"
#include "RadarObj.h"

enum class CellType {
    Empty,
    Mound,
    Pit,
    Flame,
    Robot,
    DeadRobot
};

struct Cell {
    CellType type = CellType::Empty;
    RobotBase* robot = nullptr;
    char symbol = '.';
};

struct RobotInfo {
    RobotBase* robot = nullptr;
    int row = 0;
    int col = 0;
    char symbol = '?';
};

class Arena {
public:
    Arena();

    bool load_config(const std::string& filename);
    void setup();
    void run();

private:
    int m_height;
    int m_width;
    int m_max_rounds;
    double m_sleep_interval;
    bool m_live_mode;

    int m_num_flamethrowers;
    int m_num_pits;
    int m_num_mounds;

    int m_round;

    std::vector<std::vector<Cell>> m_grid;
    std::vector<RobotInfo> m_robots;

    std::mt19937 m_rng;

    void initialize_grid();
    void place_obstacles();
    void place_random_obstacle(CellType type, char symbol);

    void load_robots();
    void place_robot(RobotBase* robot, char symbol);

    void print_arena() const;

    bool inside(int row, int col) const;
    bool is_dead(RobotBase* robot) const;
    bool only_one_living_robot() const;

    RobotInfo* find_robot_info(RobotBase* robot);

    std::vector<RadarObj> perform_radar_scan(RobotBase* robot, int direction);
    void scan_cell(std::vector<RadarObj>& results, int row, int col);

    void handle_move(RobotBase* robot, int direction, int distance);
    void handle_shot(RobotBase* robot, int shot_row, int shot_col);

    void handle_railgun(RobotBase* robot, int dr, int dc);
    void handle_grenade(RobotBase* robot, int shot_row, int shot_col);
    void handle_flamethrower(RobotBase* robot, int dr, int dc);
    void handle_hammer(RobotBase* robot, int dr, int dc);

    void damage_robot(RobotBase* target, int min_damage, int max_damage);
    void mark_dead_if_needed(RobotBase* robot);

    int random_int(int low, int high);
};