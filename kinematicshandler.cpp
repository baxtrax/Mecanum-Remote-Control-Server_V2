#include "kinematicshandler.h"

KinematicsHandler::KinematicsHandler()
{
    FRBLSpeed = 0.0;
    FLBRSpeed = 0.0;
}

void KinematicsHandler::updateSpeeds(double x, double y, double z)
{
    double dir = calculateDirection(x, y);
    double mag = calculateMagnitude(x, y);
    FRBLSpeed = calculateFRBLSpeed(dir, mag, z);
    FLBRSpeed = calculateFLBRSpeed(dir, mag, z);
    // speedsChanged is accessed by outputHandler for slider updates and by
    // socket for sending new speeds to the robot.
    emit speedsChanged(FRBLSpeed, FLBRSpeed);

    // functionChanged is accessed by outputHandler for updating sin graphs
    emit functionChanged(dir, mag, z);
}

double KinematicsHandler::calculateMagnitude(double x, double y)
{
    return (std::clamp(
        ((double)sqrt(
            pow(y, 2) +pow(x, 2))),
        IOConstants::MIN,
        IOConstants::MAX));
}

double KinematicsHandler::calculateDirection(double x, double y)
{
    double value = atan2(y, x);
    if (value < 0) {
        value = value + (2*PI);
    }
    return value;
}

double KinematicsHandler::calculateFRBLSpeed(double direction, double magnitude, double z)
{
    return((((double)sin(direction - (1.0/4.0*PI))) * magnitude) + z);
}

double KinematicsHandler::calculateFLBRSpeed(double direction, double magnitude, double z)
{
    return((((double)sin(direction + (1.0/4.0*PI))) * magnitude) + z);
}
