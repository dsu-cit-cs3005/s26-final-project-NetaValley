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

    int m_last_row = -1;
    int m_last_col = -1;
    int m_stuck_turns = 0;
    int m_wander_dir = 3;    
public:
    Robot_BingusPrime()
        : RobotBase(2, 5, grenade)
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

    // Blind grenade shots toward common enemy zones.
    if (get_grenades() > 0) {
        int row;
        int col;
        get_current_location(row, col);

        static int target_index = 0;

        int targets[4][2] = {
            {m_board_row_max / 2, m_board_col_max / 2},
            {0, 0},
            {0, m_board_col_max},
            {m_board_row_max, 0}
        };

        shot_row = targets[target_index][0];
        shot_col = targets[target_index][1];

        target_index++;
        if (target_index >= 4) {
            target_index = 0;
        }

        return true;
    }

    return false;
}

void get_move_direction(int& direction, int& distance) override {
    static int dir = 1;

    direction = dir;
    distance = 1; // safer than full speed

    dir++;
    if (dir > 8) {
        dir = 1;
    }
}
};

extern "C" RobotBase* create_robot() {
    return new Robot_BingusPrime();
}

extern "C" const char* robot_summary() {
    return "Rotates radar, railguns nearest target.";
}