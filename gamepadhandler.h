#ifndef GAMEPADHANDLER_H
#define GAMEPADHANDLER_H

#include <QObject>
#include <QGamepad>
#include <QGamepadManager>
#include <QtDebug>

class GamepadHandler : public QObject
{
    Q_OBJECT
public:
    GamepadHandler();
    QGamepad *getCurrentGamepad();
    int getTotalConnected();
    bool setCurrentGamepad(int deviceIDPos);

public slots:
    bool refreshGamepad();

private:
    QGamepad *currentGamepad;
    QGamepadManager *gamepadManager;
    QList<int> *gamepadList;
    int currentGamepadIDPos;

    bool updateGamepadList();
    void configureConnections();
};

#endif // GAMEPADHANDLER_H
