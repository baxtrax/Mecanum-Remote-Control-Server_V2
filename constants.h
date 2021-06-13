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

    //strings are not literal types so need to use char array
    inline constexpr auto CONN_CAM_ADDRESS = "connection/camera/address";
    inline constexpr auto CONN_CAM_PORT = "connection/camera/port";
    inline constexpr auto CONN_CAM_EN = "connection/camera/en";

    inline constexpr auto CONN_SOCK_ADDRESS = "connection/socket/address";
    inline constexpr auto CONN_SOCK_PORT = "connection/socket/port";
    inline constexpr auto CONN_SOCK_EN = "connection/socket/en";

    inline constexpr auto GRAPH_PERF_EN = "graph/performance/en";
    inline constexpr auto GRAPH_PERF_QUAL = "graph/performance/qual";
    inline constexpr auto GRAPH_PERF_POINTS = "graph/performance/points";

    inline constexpr auto RENDER_PERF_FPS_EN = "render/performance/FPS_en";
    inline constexpr auto RENDER_PERF_QUAL = "render/performance/qual";
    inline constexpr auto RENDER_PERF_FPS_LIM = "render/performance/FPS_lim";

    inline constexpr auto RENDER_VIEW_EN = "render/view/en";
    inline constexpr auto RENDER_VIEW_COUNT_EN = "render/view/count_en";
    inline constexpr auto RENDER_VIEW_DEBUG_EN = "render/view/debug_en";

    inline constexpr auto APPEAR_THEME_DARK_EN = "appear/theme/dark_en";







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
