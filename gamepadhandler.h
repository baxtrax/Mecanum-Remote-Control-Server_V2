#ifndef GAMEPADHANDLER_H
#define GAMEPADHANDLER_H

#include <QObject>
#include <QtDebug>
#include <QGamepad>
#include <QGamepadManager>
#include "loggerhandler.h"

class GamepadHandler : public QObject
{
    Q_OBJECT
public:
    GamepadHandler(LoggerHandler *loggerRef);

    //Setters
    bool setCurrentGamepad(int deviceIDPos);

    //Getters
    QGamepad *getCurrentGamepad();
    int getTotalConnected();

public slots:
    bool refreshGamepad();

signals:
    void gamepad_axisLeftXChanged(double);
    void gamepad_axisLeftYChanged(double);
    void gamepad_axisRightXChanged(double);
    void gamepad_axisRightYChanged(double);
    void gamepad_buttonAChanged(bool);
    void gamepad_buttonBChanged(bool);
    void gamepad_buttonXChanged(bool);
    void gamepad_buttonYChanged(bool);
    void gamepad_buttonL1Changed(bool);
    void gamepad_buttonR1Changed(bool);
    void gamepad_buttonL2Changed(double);
    void gamepad_buttonR2Changed(double);
    void gamepad_buttonL3Changed(bool);
    void gamepad_buttonR3Changed(bool);
    void gamepad_buttonSelectChanged(bool);
    void gamepad_buttonStartChanged(bool);
    void gamepad_buttonGuideChanged(bool);
    void gamepad_buttonCenterChanged(bool);
    void gamepad_buttonUpChanged(bool);
    void gamepad_buttonDownChanged(bool);
    void gamepad_buttonLeftChanged(bool);
    void gamepad_buttonRightChanged(bool);

private:
    QGamepad *currentGamepad;
    QGamepadManager *gamepadManager;
    LoggerHandler *logger;
    QList<int> *gamepadList;
    int currentGamepadIDPos;

    bool updateGamepadList();
    void configureConnections();
};

#endif // GAMEPADHANDLER_H
