#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QLinearGradient>
#include <QString>

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
} // namespace IOConstants

namespace SettingsConstants {
inline constexpr int DISABLED_INFO = 0; // Generates a straight line
inline constexpr int BASIC_INFO = 1;    // Mag and scale - 2 speed lines
inline constexpr int DETAILED_INFO = 2; // Mag scale and z - 2 speed lines
inline constexpr int ADVANCED_INFO = 3; // Mag scale and z - 4 speed lines

//strings are not literal types so need to use char array
inline constexpr auto CONN_CAM_ADDRESS = "connection/camera/address";
inline constexpr auto CONN_CAM_PORT = "connection/camera/port";
inline constexpr auto CONN_CAM_EN = "connection/camera/en";

inline constexpr auto CONN_COMM_ADDRESS = "connection/communication/address";
inline constexpr auto CONN_COMM_PORT = "connection/communication/port";
inline constexpr auto CONN_COMM_EN = "connection/communication/en";

inline constexpr auto GRAPH_PERF_EN = "graph/performance/en";
inline constexpr auto GRAPH_PERF_QUAL = "graph/performance/qual";
inline constexpr auto GRAPH_PERF_POINTS = "graph/performance/points";
inline constexpr auto GRAPH_PERF_ACCEL = "graph/performance/accel";

inline constexpr auto RENDER_PERF_FPS_EN = "render/performance/FPS_en";
inline constexpr auto RENDER_PERF_QUAL = "render/performance/qual";
inline constexpr auto RENDER_PERF_FPS_LIM = "render/performance/FPS_lim";

inline constexpr auto RENDER_VIEW_EN = "render/view/en";
inline constexpr auto RENDER_VIEW_COUNT_EN = "render/view/count_en";
inline constexpr auto RENDER_VIEW_DEBUG_EN = "render/view/debug_en";

inline constexpr auto APPEAR_THEME_DARK_EN = "appear/theme/dark_en";

//Defaults
inline constexpr auto D_CONN_CAM_ADDRESS = "123.123.123.123";
inline constexpr auto D_CONN_CAM_PORT = "12345";
inline constexpr bool D_CONN_CAM_EN = false;

inline constexpr auto D_CONN_COMM_ADDRESS = "123.123.123.123";
inline constexpr auto D_CONN_COMM_PORT = "12345";
inline constexpr bool D_CONN_COMM_EN = false;

inline constexpr bool D_GRAPH_PERF_EN = true;
inline constexpr int D_GRAPH_PERF_QUAL = 2;
inline constexpr int D_GRAPH_PERF_POINTS = 15;

inline constexpr int D_RENDER_PERF_QUAL = 0;
inline constexpr bool D_GRAPH_PERF_ACCEL = true;

inline constexpr bool D_RENDER_VIEW_EN = true;
inline constexpr bool D_RENDER_VIEW_COUNT_EN = false;
inline constexpr bool D_RENDER_VIEW_DEBUG_EN = true;

inline constexpr bool D_APPEAR_THEME_DARK_EN = true;
} // namespace SettingsConstants

namespace LoggerConstants {
inline constexpr int DEBUG = 0;
inline constexpr int INFO = 1;
inline constexpr int WARNING = 2;
inline constexpr int ERR = 3;
inline constexpr int FATAL = 4;
} // namespace LoggerConstants

namespace SimulationConstants {
inline constexpr float GRID_WIDTH = 10.0f;
inline constexpr float GRID_PAD = 0.2f;
inline constexpr float GRID_THICKNESS = 0.02f;
inline constexpr float INBASE_WIDTH = 2.5f;
inline constexpr float INBASE_LENGTH = 3.8f;
inline constexpr float WHEEL_DIAMETER = 1.5f;
inline constexpr float WHEEL_WIDTH = 1.0f;
inline constexpr float FRAME_THICKNESS = 0.025f;
inline constexpr int WHEEL_RIGHT = false;
inline constexpr int WHEEL_LEFT = true;
inline constexpr double MIN_WHEEL_ROT_DURATION = 25000;
inline constexpr double MAX_WHEEL_ROT_DURATION = 2000;
} // namespace SimulationConstants

#endif // CONSTANTS_H
