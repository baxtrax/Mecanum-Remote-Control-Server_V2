#include "kinematicshandler.h"

KinematicsHandler::KinematicsHandler()
{
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
    // This is done because they are compared later in the program.
    speeds[0] = (double) // FR
        ((int)(calculateFRSpeed(dir, mag, z)*100000)/100000.0);
    speeds[1] = (double) // BL
        ((int)(-calculateBLSpeed(dir, mag, z)*100000)/100000.0);
    speeds[2] = (double) // FL
        ((int)(-calculateFLSpeed(dir, mag, z)*100000)/100000.0);
    speeds[3] = (double) // BR
        ((int)(calculateBRSpeed(dir, mag, z)*100000)/100000.0);

    qDebug() << "B" << "FR:" << speeds[0] << "BL:" << speeds[1]
             << "FL:" << speeds[2] << "BR:" << speeds[3]
             << "Dir:" << dir << "Mag:" << mag << "Z:" << z;

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

//    qDebug() << "A" << "FRBL:" << FRBLSpeed << "FLBR:" << FLBRSpeed
//             << "Dir:" << dir << "Mag:" << mag << "Z:" << z;

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
        ((double)sqrt(
            pow(y, 2) +pow(x, 2))),
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


/**
 * @brief Calculates the moving speed of the Front Right speeds and Back Left
 * speeds. Turns out the kinematics of the FR and BL speeds are the same.
 * @param double direction of force.
 * @param double magnitude of force (how fast).
 * @param double z coordinate of input.
 * @return double speed of Front Right and Back Left.
 */
double KinematicsHandler::calculateFRSpeed(double direction,
                                             double magnitude,
                                             double z)
{
    return(
        (((double)sin(direction - (1.0/4.0*MathConstants::PI)))
        * magnitude)
        + z);
}

double KinematicsHandler::calculateBLSpeed(double direction,
                                             double magnitude,
                                             double z)
{
    return(
        (((double)-sin(direction - (1.0/4.0*MathConstants::PI)))
         * magnitude)
        + z);
}


/**
 * @brief Calculates the moving speed of the Front Left speeds and Back Right
 * speeds. Turns out the kinematics of the FL and BR speeds are the same.
 * @param double direction of force.
 * @param double magnitude of force (how fast).
 * @param double z coordinate of input.
 * @return double speed of Front Left and Back Right.
 */
double KinematicsHandler::calculateFLSpeed(double direction,
                                             double magnitude,
                                             double z)
{
    return(
        (((double)-sin(direction + (1.0/4.0*MathConstants::PI)))
        * magnitude)
        + z);
}

double KinematicsHandler::calculateBRSpeed(double direction,
                                             double magnitude,
                                             double z)
{
    return(
        (((double)sin(direction + (1.0/4.0*MathConstants::PI)))
         * magnitude)
        + z);
}
