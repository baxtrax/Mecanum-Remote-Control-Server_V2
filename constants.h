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
}

namespace SettingsConstants {
    inline constexpr int BASIC_INFO = 0;
    inline constexpr int DETAILED_INFO = 1;

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
