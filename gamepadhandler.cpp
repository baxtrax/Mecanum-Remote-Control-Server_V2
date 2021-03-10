#include "gamepadhandler.h"


// Constructor
GamepadHandler::GamepadHandler()
{
    gamepadManager = QGamepadManager::instance();
    gamepadList = new QList<int>;
    // Set gamepad as first gamepad in the list at startup (if it exists)
    if (updateGamepadList()) {
        setCurrentGamepad(0);
    } else {
        currentGamepad = NULL;
        currentGamepadIDPos = NULL;
    }
    connect(gamepadManager, SIGNAL(connectedGamepadsChanged()),
            this, SLOT(refreshGamepad()));
}


/**
 * @brief Updates the gamepad list with currently connected devices.
 * @return True if list contains gamepads, otherwise false.
 */
bool GamepadHandler::updateGamepadList()
{
    qDebug() << "Updating gamepad list...";
    // Grab connected gamepads
    *gamepadList = gamepadManager->connectedGamepads();
    qDebug() << getTotalConnected() << "IDs:";
    if (!(gamepadList->isEmpty())) {
        for (QList<int>::Iterator i = gamepadList->begin();
                                  i != gamepadList->end(); ++i) {
            qDebug() << *i << "-" << gamepadManager->gamepadName(*i);
        }
    }

    // Return if true if there are gamepads
    if (gamepadList->isEmpty()){ return false; } else { return true; }
}


/**
 * @brief Updates the gamepad list, and reset current gamepad to desired position.
 * Will also configure slots and connections.
 * @return True if all operations were successful, otherwise false.
 */
bool GamepadHandler::refreshGamepad()
{
    if(updateGamepadList()){
        if(setCurrentGamepad(currentGamepadIDPos)) {
            configureConnections();
            return true;
        }
    }
    return false;
}


/**
 * @brief Configures connections of slots and signals of a gamepad object
 */
void GamepadHandler::configureConnections()
{
    connect(currentGamepad, &QGamepad::axisLeftXChanged, this, [](double value){
        qDebug() << "Left X" << value;
    });
    connect(currentGamepad, &QGamepad::axisLeftYChanged, this, [](double value){
        qDebug() << "Left Y" << value;
    });
    connect(currentGamepad, &QGamepad::axisRightXChanged, this, [](double value){
        qDebug() << "Right X" << value;
    });
    connect(currentGamepad, &QGamepad::axisRightYChanged, this, [](double value){
        qDebug() << "Right Y" << value;
    });
    connect(currentGamepad, &QGamepad::buttonAChanged, this, [](bool pressed){
        qDebug() << "Button A" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonBChanged, this, [](bool pressed){
        qDebug() << "Button B" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonXChanged, this, [](bool pressed){
        qDebug() << "Button X" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonYChanged, this, [](bool pressed){
        qDebug() << "Button Y" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonL1Changed, this, [](bool pressed){
        qDebug() << "Button L1" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonR1Changed, this, [](bool pressed){
        qDebug() << "Button R1" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonL2Changed, this, [](double value){
        qDebug() << "Button L2: " << value;
    });
    connect(currentGamepad, &QGamepad::buttonR2Changed, this, [](double value){
        qDebug() << "Button R2: " << value;
    });
    connect(currentGamepad, &QGamepad::buttonL3Changed, this, [](double value){
        qDebug() << "Button L3: " << value;
    });
    connect(currentGamepad, &QGamepad::buttonR3Changed, this, [](double value){
        qDebug() << "Button R3: " << value;
    });
    connect(currentGamepad, &QGamepad::buttonSelectChanged, this, [](bool pressed){
        qDebug() << "Button Select" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonStartChanged, this, [](bool pressed){
        qDebug() << "Button Start" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonGuideChanged, this, [](bool pressed){
        qDebug() << "Button Guide" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonCenterChanged, this, [](bool pressed){
        qDebug() << "Button Center" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonUpChanged, this, [](bool pressed){
        qDebug() << "Button Up" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonDownChanged, this, [](bool pressed){
        qDebug() << "Button Down" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonLeftChanged, this, [](bool pressed){
        qDebug() << "Button Left" << pressed;
    });
    connect(currentGamepad, &QGamepad::buttonRightChanged, this, [](bool pressed){
        qDebug() << "Button Right" << pressed;
    });
}


// Setters
/**
 * @brief Sets current gamepad to desired position
 * @param Starts at 0; 0 being 1st device in list, etc.
 * @return True if gamepad was successfully set, otherwise false.
 */
bool GamepadHandler::setCurrentGamepad(int deviceIDPos)
{
    qDebug() << "Attemping to set gamepad to device #:" << deviceIDPos << "...";
    if (!(gamepadList->isEmpty()) && (getTotalConnected() == deviceIDPos + 1)) {
        currentGamepad = new QGamepad(gamepadList->at(deviceIDPos));
        currentGamepadIDPos = deviceIDPos;
        qDebug() << "Successfully set gamepad to device #:"<< deviceIDPos << "!";
        qDebug() << "Current gamepad ID position:" << currentGamepadIDPos;
        return true;
    } else {
        qDebug() << "Failed to set gamepad to device #:"<< deviceIDPos << "!";
        qDebug() << "Current gamepad ID positon:" << currentGamepadIDPos;
        return false;
    }
}

// Getters
/**
 * @brief Gets current gamepad instance.
 * @return QGamepad instance.
 */
QGamepad* GamepadHandler::getCurrentGamepad()
{
    return currentGamepad;
}

/**
 * @brief Gets total of connected devices
 * @return Number of connected devices
 */
int GamepadHandler::getTotalConnected()
{
    return gamepadList->length();
}



