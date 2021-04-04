#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

namespace MathConstants {
    const static double PI = 3.14159265;
}

namespace IOConstants {
    const static double MAX = 1.0;
    const static double MIN = -1.0;
    const static double MIN_SLIDER = 12.0;
    const static double MIN_XCHART = 1;
    const static double MAX_XCHART = 25;
}

namespace SettingsConstants {
    const static int BASIC_INFO = 0;
    const static int DETAILED_INFO = 1;

}

namespace LoggerConstants {
    const static int DEBUG = 0;
    const static int INFO = 1;
    const static int WARNING = 2;
    const static int ERR = 3;
    const static int FATAL = 4;
}


#endif // CONSTANTS_H
