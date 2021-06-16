#include "kinematicshandler.h"

// Constructor
KinematicsHandler::KinematicsHandler(LoggerHandler *loggerRef)
{
    logger = loggerRef;
    for (int i=0; i < 4; i++) {
        speeds[i] = 0.0;
    }
}


/**
 * @brief Calls methods needed to update speeds FRBL and FLBR. Also emits
 * signals to help notify liseners of the respective changes.
 * @param double x coordinate of input.
 * @param double y coordinate of input.
 * @param double z coordinate of input.
 */
void KinematicsHandler::updateSpeeds(double x, double y, double z)
{
    double dir = calculateDirection(x, y);
    double mag = calculateMagnitude(x, y);

    // Truncate floating points to get rid of unessary points of uncertainty
    // This is done because they are compared later in the program, and helps
    // avoid floating point rounding errors by dropping them.
    speeds[0] = (double) // FR
        ((int)(calculateFRSpeed(dir, mag, z)*100000)/100000.0);
    speeds[1] = (double) // BL
        ((int)(-calculateBLSpeed(dir, mag, z)*100000)/100000.0);
    speeds[2] = (double) // FL
        ((int)(-calculateFLSpeed(dir, mag, z)*100000)/100000.0);
    speeds[3] = (double) // BR
        ((int)(calculateBRSpeed(dir, mag, z)*100000)/100000.0);

    double scaleFactor = 0.0;

    // Find highest
    for (int i=0; i < 4; i++) {
        if (scaleFactor < abs(speeds[i])) {
            scaleFactor = abs(speeds[i]);
        }
    }

    // Scale all non-zero numbers
    for (int i=0; i < 4; i++) {
        if (speeds[i] != 0) {
            speeds[i] = speeds[i]/scaleFactor;
        }
    }

    emit speedsChanged(speeds[0], speeds[1], speeds[2], speeds[3]);
    emit functionChanged(dir, mag, z, scaleFactor);
}


/**
 * @brief Calculates the magnituide or speed of the force in the applied
 * direction.
 * @param double x coordinate of input.
 * @param double y coordinate of input.
 * @return double magnitude of force.
 */
double KinematicsHandler::calculateMagnitude(double x, double y)
{
    return (std::clamp(
        ((double)sqrt(pow(y, 2) + pow(x, 2))),
        IOConstants::MIN,
        IOConstants::MAX));
}


/**
 * @brief Calculates the direction of force the speeds need to end up pointing
 * to.
 * @param double x coordinate of input.
 * @param double y coordinate of input.
 * @return double direction of force.
 */
double KinematicsHandler::calculateDirection(double x, double y)
{
    return atan2(y, x);;
}


// Below are the core equations of the kinematics, understanding the math
// behind them can greatly help anyone understand how speeds values are
// calculated in a mechanum based system. Implementing z is a little confusing
// and might be hard to understand when first being looked at.

/**
 * @brief Calculates the moving speed of the Front Right.
 * @param double direction of force.
 * @param double magnitude of force (how fast).
 * @param double z coordinate of input (rotation around the center).
 * @return double speed of Front Right
 */
double KinematicsHandler::calculateFRSpeed(double direction,
                                           double magnitude,
                                           double z)
{
    return((((double)sin(direction - (1.0/4.0*MathConstants::PI)))
             * magnitude) + z);
}


/**
 * @brief Calculates the moving speed of the Back Left.
 * @param double direction of force.
 * @param double magnitude of force (how fast).
 * @param double z coordinate of input.
 * @return double speed of Back Left.
 */
double KinematicsHandler::calculateBLSpeed(double direction,
                                           double magnitude,
                                           double z)
{
    return((((double)-sin(direction - (1.0/4.0*MathConstants::PI)))
             * magnitude) + z);
}


/**
 * @brief Calculates the moving speed of the Front Left.
 * @param double direction of force.
 * @param double magnitude of force (how fast).
 * @param double z coordinate of input.
 * @return double speed of Front Left
 */
double KinematicsHandler::calculateFLSpeed(double direction,
                                             double magnitude,
                                             double z)
{
    return((((double)-sin(direction + (1.0/4.0*MathConstants::PI)))
             * magnitude) + z);
}


/**
 * @brief Calculates the moving speed of the Back Right.
 * @param double direction of force.
 * @param double magnitude of force (how fast).
 * @param double z coordinate of input.
 * @return double speed of Back Right.
 */
double KinematicsHandler::calculateBRSpeed(double direction,
                                             double magnitude,
                                             double z)
{
    return((((double)sin(direction + (1.0/4.0*MathConstants::PI)))
             * magnitude) + z);
}
