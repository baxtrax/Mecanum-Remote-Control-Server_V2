#include "inputhandler.h"

InputHandler::InputHandler()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
    kx_Right = 0.0;
    kx_Left = 0.0;
    ky_Up = 0.0;
    ky_Down = 0.0;
    kz_TRight = 0.0;
    kz_TLeft = 0.0;
    jx = 0.0;
    jy = 0.0;
    jz = 0.0;
}

void InputHandler::updateSliders()
{
    qDebug() << "Inputs changed" << x << y << z;
    emit inputsChanged(x, y, z);
}

//Setters

void InputHandler::gamepad_axisLeftXSetter(double value)
{
    jx = value;
    setX((kx_Right+kx_Left)+jx);
}


void InputHandler::gamepad_axisLeftYSetter(double value)
{
    jy = value;
    setY((ky_Up+ky_Down)+jy);
}


void InputHandler::gamepad_axisRightXSetter(double value)
{
    jz = value;
    setZ((kz_TRight+kz_TLeft)+jz);
}


void InputHandler::keyboard_WSetter(bool value)
{
    if(value) {
        ky_Up = 1.0;
    } else {
        ky_Up = 0.0;
    }
    setY((ky_Up+ky_Down)+jy);
}


void InputHandler::keyboard_SSetter(bool value)
{
    if(value) {
        ky_Down = -1.0;
    } else {
        ky_Down = 0.0;
    }
    setY((ky_Up+ky_Down)+jy);
}


void InputHandler::keyboard_ASetter(bool value)
{
    if(value) {
        kx_Left = -1.0;
    } else {
        kx_Left = 0.0;
    }
    setX((kx_Right+kx_Left)+jx);
}


void InputHandler::keyboard_DSetter(bool value)
{
    if(value) {
        kx_Right = 1.0;
    } else {
        kx_Right = 0.0;
    }
    setX((kx_Right+kx_Left)+jx);
}


void InputHandler::keyboard_ESetter(bool value)
{
    if(value) {
        kz_TRight = 1.0;
    } else {
        kz_TRight = 0.0;
    }
    setZ((kz_TRight+kz_TLeft)+jz);
}


void InputHandler::keyboard_QSetter(bool value)
{
    if(value) {
        kz_TLeft = -1.0;
    } else {
        kz_TLeft = 0.0;
    }
    setZ((kz_TRight+kz_TLeft)+jz);
}


/**
 * @brief Sets current x value
 * @return double x value
 */
void InputHandler::setX(double value)
{
    x = std::clamp(value, IOConstants::MIN, IOConstants::MAX);
    updateSliders();
}

/**
 * @brief Sets current y value
 * @return double y value
 */
void InputHandler::setY(double value)
{
    y = std::clamp((value), IOConstants::MIN, IOConstants::MAX);
    updateSliders();
}

/**
 * @brief Sets current z value
 * @return double z value
 */
void InputHandler::setZ(double value)
{
    z = std::clamp((value), IOConstants::MIN, IOConstants::MAX);
    updateSliders();
}


//Getters
/**
 * @brief Gets current x value
 * @return double x value
 */
double InputHandler::getX()
{
    return x;
}


/**
 * @brief Gets current y value
 * @return double y value
 */
double InputHandler::getY()
{
    return y;
}


/**
 * @brief Gets current z value
 * @return double z value
 */
double InputHandler::getZ()
{
    return z;
}
