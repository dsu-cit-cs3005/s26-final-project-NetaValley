#include "RobotBase.h"
#include <vector>

class Robot_MyBot : public RobotBase {
private:
    bool saw_robot = false;
    int target_row = 0;
    int target_col = 0;

public:
    Robot_MyBot()
        : RobotBase(4, 3, railgun)   // move, armor, weapon
    {
        m_name = "BINGUS";
    }

    void get_radar_direction(int& radar_direction) override {
        radar_direction = 0; // scan surrounding 8 cells
    }

    void process_radar_results(const std::vector<RadarObj>& radar_results) override {
        saw_robot = false;

        for (const RadarObj& obj : radar_results) {
            if (obj.m_type == 'R') {
                saw_robot = true;
                target_row = obj.m_row;
                target_col = obj.m_col;
                return;
            }
        }
    }

    bool get_shot_location(int& shot_row, int& shot_col) override {
        if (saw_robot) {
            shot_row = target_row;
            shot_col = target_col;
            return true;
        }

        return false;
    }

    void get_move_direction(int& direction, int& distance) override {
        direction = 3; // right
        distance = 1;
    }
};

extern "C" RobotBase* create_robot() {
    return new Robot_MyBot();
}

extern "C" const char* robot_summary() {
    return "Scans nearby, shoots robots, moves right.";
}