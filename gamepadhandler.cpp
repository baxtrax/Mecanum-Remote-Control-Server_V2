#include "gamepadhandler.h"

// Constructor
GamepadHandler::GamepadHandler(LoggerHandler *loggerRef)
{
    logger = loggerRef;
    gamepadManager = QGamepadManager::instance();
    gamepadList = new QList<int>;
    // Set gamepad as first gamepad in the list at startup (if it exists)
    if (updateGamepadList()) {
        setCurrentGamepad(0);
    } else {
        currentGamepad = NULL;
        currentGamepadIDPos = NULL;
    }
    connect(gamepadManager, SIGNAL(connectedGamepadsChanged()), this, SLOT(refreshGamepad()));
}

// Methods
/**
 * @brief Updates the gamepad list with currently connected devices.
 * @return True if list contains gamepads, otherwise false.
 */
bool GamepadHandler::updateGamepadList()

{
    // Grab connected gamepads
    logger->write(LoggerConstants::INFO, "Fetching gamepads ...");
    *gamepadList = gamepadManager->connectedGamepads();
    logger->write(LoggerConstants::INFO, "Gamepads found: " + QString::number(getTotalConnected()));

    if (gamepadList->isEmpty()) {
        return false;
    } else {
        return true;
    }
}

/**
 * @brief Updates the gamepad list, and reset current gamepad to
 * desired position. Will also configure slots and connections.
 * @return True if all operations were successful, otherwise false.
 */
bool GamepadHandler::refreshGamepad()
{
    if (updateGamepadList()) {
        if (setCurrentGamepad(currentGamepadIDPos)) {
            configureConnections();
            return true;
        }
    }
    return false;
}

/**
 * @brief Configures connections of slots and signals of a gamepad object.
 */
void GamepadHandler::configureConnections()
{
    //TODO add inverts for controllers in settings
    connect(currentGamepad, &QGamepad::axisLeftXChanged, this, [this](double value) {
        emit gamepad_axisLeftXChanged(value);
    });
    connect(currentGamepad, &QGamepad::axisLeftYChanged, this, [this](double value) {
        emit gamepad_axisLeftYChanged(-value);
    });
    connect(currentGamepad, &QGamepad::axisRightXChanged, this, [this](double value) {
        emit gamepad_axisRightXChanged(value);
    });
    connect(currentGamepad, &QGamepad::axisRightYChanged, this, [this](double value) {
        emit gamepad_axisRightYChanged(value);
    });
    connect(currentGamepad, &QGamepad::buttonAChanged, this, [this](bool pressed) {
        emit gamepad_buttonAChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonBChanged, this, [this](bool pressed) {
        emit gamepad_buttonBChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonXChanged, this, [this](bool pressed) {
        emit gamepad_buttonXChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonYChanged, this, [this](bool pressed) {
        emit gamepad_buttonYChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonL1Changed, this, [this](bool pressed) {
        emit gamepad_buttonL1Changed(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonR1Changed, this, [this](bool pressed) {
        emit gamepad_buttonR1Changed(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonL2Changed, this, [this](double value) {
        emit gamepad_buttonL2Changed(value);
    });
    connect(currentGamepad, &QGamepad::buttonR2Changed, this, [this](double value) {
        emit gamepad_buttonR2Changed(value);
    });
    connect(currentGamepad, &QGamepad::buttonL3Changed, this, [this](bool pressed) {
        emit gamepad_buttonL3Changed(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonR3Changed, this, [this](bool pressed) {
        emit gamepad_buttonR3Changed(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonSelectChanged, this, [this](bool pressed) {
        emit gamepad_buttonSelectChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonStartChanged, this, [this](bool pressed) {
        emit gamepad_buttonStartChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonGuideChanged, this, [this](bool pressed) {
        emit gamepad_buttonGuideChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonCenterChanged, this, [this](bool pressed) {
        emit gamepad_buttonCenterChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonUpChanged, this, [this](bool pressed) {
        emit gamepad_buttonUpChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonDownChanged, this, [this](bool pressed) {
        emit gamepad_buttonDownChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonLeftChanged, this, [this](bool pressed) {
        emit gamepad_buttonLeftChanged(pressed);
    });
    connect(currentGamepad, &QGamepad::buttonRightChanged, this, [this](bool pressed) {
        emit gamepad_buttonRightChanged(pressed);
    });
}

// Setters
/**
 * @brief Sets current gamepad to desired position.
 * @param Starts at 0; 0 being 1st device in list, etc.
 * @return True if gamepad was successfully set, otherwise false.
 */
bool GamepadHandler::setCurrentGamepad(int deviceIDPos)
{
    if (!(gamepadList->isEmpty()) && (getTotalConnected() == deviceIDPos + 1)) {
        currentGamepad = new QGamepad(gamepadList->at(deviceIDPos));
        currentGamepadIDPos = deviceIDPos;
        logger->write(LoggerConstants::INFO,
                      "Successfully set gamepad to device ID: " + QString::number(deviceIDPos));
        logger->write(LoggerConstants::INFO,
                      "Current gamepad is " + QString::number(currentGamepadIDPos + 1)
                          + " with device ID: " + QString::number(currentGamepadIDPos));
        return true;
    } else {
        logger->write(LoggerConstants::WARNING,
                      "Failed to set gamepad to device ID: " + QString::number(deviceIDPos));
        return false;
    }
}

// Getters
/**
 * @brief Gets current gamepad instance.
 * @return gamepad.
 */
QGamepad *GamepadHandler::getCurrentGamepad()
{
    return currentGamepad;
}

/**
 * @brief Gets total of connected devices.
 * @return Number of connected devices.
 */
int GamepadHandler::getTotalConnected()
{
    return gamepadList->length();
}
