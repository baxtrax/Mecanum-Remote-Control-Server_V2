#ifndef KINEMATICSHANDLER_H
#define KINEMATICSHANDLER_H

#include <QObject>
#include <QDebug>
#include <math.h>
#include "constants.h"

class KinematicsHandler :  public QObject
{
    Q_OBJECT
public:
    KinematicsHandler();

public slots:
    void updateSpeeds(double, double, double);
signals:
    void speedsChanged(double, double, double, double);
    void functionChanged(double, double, double, double);
private:
    double speeds[4];
    double calculateMagnitude(double x, double y);
    double calculateDirection(double x, double y);
    double calculateFRSpeed(double direction, double magnitude, double z);
    double calculateBLSpeed(double direction, double magnitude, double z);
    double calculateFLSpeed(double direction, double magnitude, double z);
    double calculateBRSpeed(double direction, double magnitude, double z);
};

#endif // KINEMATICSHANDLER_H
