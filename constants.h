#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>
#include <QLinearGradient>

namespace MathConstants {
    inline constexpr double PI = 3.14159265;
}

namespace IOConstants {
    inline constexpr double MAX = 1.0;
    inline constexpr double MIN = -1.0;
    inline constexpr double MIN_SLIDER = 12.0;
    inline constexpr double MIN_XCHART = 1;
    inline constexpr double MAX_XCHART = 25;
    inline constexpr int FR_GRAPH = 0;
    inline constexpr int BL_GRAPH = 1;
    inline constexpr int FL_GRAPH = 2;
    inline constexpr int BR_GRAPH = 3;
}

namespace SettingsConstants {
    inline constexpr int DISABLED_INFO = 0; // Generates a straight line
    inline constexpr int BASIC_INFO = 1;    // Mag and scale - 2 speed lines
    inline constexpr int DETAILED_INFO = 2; // Mag scale and z - 2 speed lines
    inline constexpr int ADVANCED_INFO = 3; // Mag scale and z - 4 speed lines

}

namespace LoggerConstants {
    inline constexpr int DEBUG = 0;
    inline constexpr int INFO = 1;
    inline constexpr int WARNING = 2;
    inline constexpr int ERR = 3;
    inline constexpr int FATAL = 4;
}

namespace SimulationConstants {
    inline constexpr double BASE_WIDTH = 0.5f;
    inline constexpr double BASE_LENGTH = 0.75f;
    inline constexpr double WHEEL_HEIGHT = 0.5f;
    inline constexpr double FRAME_THICKNESS = 0.025f;
    inline constexpr double MAX_GRAPH_SIZE = 1.0f;
    inline constexpr double MIN_WHEEL_ROT_DURATION = 25000;
    inline constexpr double MAX_WHEEL_ROT_DURATION = 2000;
}

#endif // CONSTANTS_H
