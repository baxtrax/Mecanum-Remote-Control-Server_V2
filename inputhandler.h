#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "constants.h"
#include "loggerhandler.h"

#include <QDebug>
#include <QObject>
#include <QSlider>

class InputHandler : public QObject
{
    Q_OBJECT
public:
    InputHandler(LoggerHandler *loggerRef);

    double getX();
    double getY();
    double getZ();

public slots:
    void gamepad_axisLeftXSetter(double);
    void gamepad_axisLeftYSetter(double);
    void gamepad_axisRightXSetter(double);
    void keyboard_WSetter(bool);
    void keyboard_SSetter(bool);
    void keyboard_ASetter(bool);
    void keyboard_DSetter(bool);
    void keyboard_ESetter(bool);
    void keyboard_QSetter(bool);

signals:
    void inputsChanged(double, double, double);

    void x_topSlider_ValChanged(double);
    void x_botSlider_ValChanged(double);
    void y_topSlider_ValChanged(double);
    void y_botSlider_ValChanged(double);
    void z_topSlider_ValChanged(double);
    void z_botSlider_ValChanged(double);

private:
    LoggerHandler *logger;

    void setX(double value);
    void setY(double value);
    void setZ(double value);

    void updateSliders();
    void setXSlider(double value);
    void setYSlider(double value);
    void setZSlider(double value);

    double x;
    double y;
    double z;

    double kx_Right;
    double kx_Left;
    double ky_Up;
    double ky_Down;
    double kz_TRight;
    double kz_TLeft;

    double jx;
    double jy;
    double jz;
};

#endif // INPUTHANDLER_H
