#include "RobotBase.h"
#include <vector>
#include <cstdlib>

class Robot_BingusPrime : public RobotBase {
private:
    bool m_enemy_seen = false;
    int m_target_row = 0;
    int m_target_col = 0;

    int m_scan_dir = 1;
    int m_patrol_dir = 3;

public:
    Robot_BingusPrime()
        : RobotBase(4, 3, railgun)
    {
        m_name = "BingusPrime";
    }

    void get_radar_direction(int& radar_direction) override {
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
                int dist = abs(obj.m_row - my_row) + abs(obj.m_col - my_col);

                if (dist < best_distance) {
                    best_distance = dist;
                    m_enemy_seen = true;
                    m_target_row = obj.m_row;
                    m_target_col = obj.m_col;
                }
            }
        }
    }

    bool get_shot_location(int& shot_row, int& shot_col) override {
        if (m_enemy_seen) {
            shot_row = m_target_row;
            shot_col = m_target_col;
            return true;
        }

        return false;
    }

    void get_move_direction(int& direction, int& distance) override {
        int row;
        int col;
        get_current_location(row, col);

        // Avoid getting stuck in corners.
        if (col >= m_board_col_max - 1) {
            m_patrol_dir = 5; // down
        }
        else if (row >= m_board_row_max - 1) {
            m_patrol_dir = 7; // left
        }
        else if (col <= 0) {
            m_patrol_dir = 1; // up
        }
        else if (row <= 0) {
            m_patrol_dir = 3; // right
        }

        direction = m_patrol_dir;
        distance = get_move_speed();
    }
};

extern "C" RobotBase* create_robot() {
    return new Robot_BingusPrime();
}

extern "C" const char* robot_summary() {
    return "Rotates radar, railguns nearest target.";
}