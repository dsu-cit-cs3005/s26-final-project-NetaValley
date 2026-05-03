#include "RobotBase.h"
#include <vector>
#include <cstdlib>
#include <cmath>

class Robot_BingusUltima : public RobotBase {
private:
    bool m_enemy_seen = false;
    bool m_has_last_target = false;

    int m_target_row = 0;
    int m_target_col = 0;

    int m_last_target_row = 0;
    int m_last_target_col = 0;

    int m_scan_dir = 1;
    int m_move_dir = 3;

    int m_last_row = -1;
    int m_last_col = -1;
    int m_stuck_turns = 0;

    int m_turn = 0;

public:
    Robot_BingusUltima()
        : RobotBase(2, 5, railgun)
    {
        m_name = "BingusUltima";
    }

    void get_radar_direction(int& radar_direction) override {
        m_turn++;

        // Every few turns, check nearby danger.
        if (m_turn % 4 == 0) {
            radar_direction = 0;
            return;
        }

        // Otherwise rotate full-board radar.
        radar_direction = m_scan_dir;
        m_scan_dir++;

        if (m_scan_dir > 8) {
            m_scan_dir = 1;
        }
    }

    void process_radar_results(const std::vector<RadarObj>& radar_results) override {
        m_enemy_seen = false;

        int my_row;
        int my_col;
        get_current_location(my_row, my_col);

        int best_distance = 999999;

        for (const RadarObj& obj : radar_results) {
            if (obj.m_type == 'R') {
                int dist = std::abs(obj.m_row - my_row) + std::abs(obj.m_col - my_col);

                if (dist < best_distance) {
                    best_distance = dist;

                    m_enemy_seen = true;
                    m_target_row = obj.m_row;
                    m_target_col = obj.m_col;

                    m_last_target_row = obj.m_row;
                    m_last_target_col = obj.m_col;
                    m_has_last_target = true;
                }
            }
        }
    }

    bool get_shot_location(int& shot_row, int& shot_col) override {
        int my_row;
        int my_col;
        get_current_location(my_row, my_col);

        // Best case: shoot exactly where radar saw a robot.
        if (m_enemy_seen) {
            shot_row = m_target_row;
            shot_col = m_target_col;
            return true;
        }

        // If we remember a target, fire through that remembered position.
        if (m_has_last_target && m_turn % 2 == 0) {
            shot_row = m_last_target_row;
            shot_col = m_last_target_col;
            return true;
        }

        // Blind railgun firing pattern.
        // Railgun goes all the way to the edge, so these are useful guesses.
        int pattern = m_turn % 8;

        if (pattern == 0) {
            shot_row = my_row;
            shot_col = m_board_col_max;
            return true;
        }
        else if (pattern == 1) {
            shot_row = my_row;
            shot_col = 0;
            return true;
        }
        else if (pattern == 2) {
            shot_row = 0;
            shot_col = my_col;
            return true;
        }
        else if (pattern == 3) {
            shot_row = m_board_row_max;
            shot_col = my_col;
            return true;
        }
        else if (pattern == 4) {
            shot_row = 0;
            shot_col = 0;
            return true;
        }
        else if (pattern == 5) {
            shot_row = 0;
            shot_col = m_board_col_max;
            return true;
        }
        else if (pattern == 6) {
            shot_row = m_board_row_max;
            shot_col = 0;
            return true;
        }
        else {
            shot_row = m_board_row_max;
            shot_col = m_board_col_max;
            return true;
        }
    }

    void get_move_direction(int& direction, int& distance) override {
        int row;
        int col;
        get_current_location(row, col);

        // If movement is disabled, do nothing.
        if (get_move_speed() <= 0) {
            direction = 0;
            distance = 0;
            return;
        }

        // Detect if arena blocked us last time.
        if (row == m_last_row && col == m_last_col) {
            m_stuck_turns++;
        } else {
            m_stuck_turns = 0;
        }

        m_last_row = row;
        m_last_col = col;

        // If stuck, rotate direction aggressively.
        if (m_stuck_turns >= 1) {
            m_move_dir++;

            if (m_move_dir > 8) {
                m_move_dir = 1;
            }

            direction = m_move_dir;
            distance = 1;
            return;
        }

        // Stay away from edges/corners.
        if (row <= 1) {
            m_move_dir = 5; // down
        }
        else if (row >= m_board_row_max - 1) {
            m_move_dir = 1; // up
        }
        else if (col <= 1) {
            m_move_dir = 3; // right
        }
        else if (col >= m_board_col_max - 1) {
            m_move_dir = 7; // left
        }
        else {
            // Slowly rotate movement to avoid becoming predictable.
            if (m_turn % 3 == 0) {
                m_move_dir++;

                if (m_move_dir > 8) {
                    m_move_dir = 1;
                }
            }
        }

        direction = m_move_dir;

        // Move cautiously. Full speed causes more pit/flame deaths.
        distance = 1;
    }
};

extern "C" RobotBase* create_robot() {
    return new Robot_BingusUltima();
}

extern "C" const char* robot_summary() {
    return "Tank railgun sniper with blind fire.";
}