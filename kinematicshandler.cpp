#include "kinematicshandler.h"

KinematicsHandler::KinematicsHandler()
{
    FRBLSpeed = 0.0;
    FLBRSpeed = 0.0;
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
    // TODO fix turning, seems to be inaccurate or just straight up wrong.
    FRBLSpeed = (double)
        ((int)(calculateFRBLSpeed(dir, mag, z)*100000)/100000.0);
    FLBRSpeed = (double)
        ((int)(calculateFLBRSpeed(dir, mag, z)*100000)/100000.0);

    double scaleFactor = 0;
    if((abs(FRBLSpeed) >= abs(FLBRSpeed)) &&
       (!(FRBLSpeed == 0 && FLBRSpeed == 0))) {
        scaleFactor = abs(FRBLSpeed);
        FRBLSpeed = FRBLSpeed/scaleFactor;
        FLBRSpeed = FLBRSpeed/scaleFactor;
    } else if (abs(FRBLSpeed) < abs(FLBRSpeed)) {
        scaleFactor = abs(FLBRSpeed);
        FRBLSpeed = FRBLSpeed/scaleFactor;
        FLBRSpeed = FLBRSpeed/scaleFactor;
    }

//    qDebug() << "FRBL:" << FRBLSpeed << "FLBR:" << FLBRSpeed
//             << "Dir:" << dir << "Mag:" << mag;

    emit speedsChanged(FRBLSpeed, FLBRSpeed);
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
double KinematicsHandler::calculateFRBLSpeed(double direction,
                                             double magnitude,
                                             double z)
{
    return(
        (((double)sin(direction - (1.0/4.0*MathConstants::PI)))
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
double KinematicsHandler::calculateFLBRSpeed(double direction,
                                             double magnitude,
                                             double z)
{
    return(
        (((double)sin(direction + (1.0/4.0*MathConstants::PI)))
        * magnitude)
        + z);
}
