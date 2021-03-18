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
    void speedsChanged(double, double);
    void functionChanged(double, double, double, double, double);
private:
    double FRBLSpeed;
    double FLBRSpeed;
    double calculateMagnitude(double x, double y);
    double calculateDirection(double x, double y);
    double calculateFRBLSpeed(double direction, double magnitude, double z);
    double calculateFLBRSpeed(double direction, double magnitude, double z);
};

#endif // KINEMATICSHANDLER_H
