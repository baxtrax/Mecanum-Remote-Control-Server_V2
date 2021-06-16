#include "inputhandler.h"

// Constructor
InputHandler::InputHandler(LoggerHandler *loggerRef)
{
    logger = loggerRef;
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

/**
 * @brief Updates sliders on GUI to repersent x, y, and z values. Function is
 * called any time an input is updated or changed.
 */
void InputHandler::updateSliders()
{
    emit inputsChanged(x, y, z);
    setXSlider(x);
    setYSlider(y);
    setZSlider(z);
}


// Setters
/**
 * @brief Sets value of x slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX
 */
void InputHandler::setXSlider(double value)
{
    double amplifiedX = value * 100.0;
    if (amplifiedX > 0.0) { // positive
        emit x_botSlider_ValChanged(0.0);
        if (amplifiedX <= IOConstants::MIN_SLIDER) {
            emit x_topSlider_ValChanged(IOConstants::MIN_SLIDER);
        } else {
            emit x_topSlider_ValChanged(amplifiedX);
        }
    } else if (amplifiedX < 0.0) { // negative
        emit x_topSlider_ValChanged(0.0);
        if (amplifiedX >= -IOConstants::MIN_SLIDER+1) {
            emit x_botSlider_ValChanged(-IOConstants::MIN_SLIDER+1);
        } else {
            emit x_botSlider_ValChanged(amplifiedX);
        }
    } else { // zero
        emit x_botSlider_ValChanged(0.0);
        emit x_topSlider_ValChanged(0.0);
    }
}


/**
 * @brief Sets value of y slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX
 */
void InputHandler::setYSlider(double value)
{
    double amplifiedY = value * 100.0;
    if (amplifiedY > 0.0) { // positive
        emit y_botSlider_ValChanged(0.0);
        if (amplifiedY <= IOConstants::MIN_SLIDER) {
            emit y_topSlider_ValChanged(IOConstants::MIN_SLIDER);
        }  else {
            emit y_topSlider_ValChanged(amplifiedY);
        }
    } else if (amplifiedY < 0.0) { // negative
        emit y_topSlider_ValChanged(0.0);
        if (amplifiedY >= -IOConstants::MIN_SLIDER+1) {
            emit y_botSlider_ValChanged(-IOConstants::MIN_SLIDER+1);
        }  else {
            emit y_botSlider_ValChanged(amplifiedY);
        }
    } else { // zero
        emit y_botSlider_ValChanged(0.0);
        emit y_topSlider_ValChanged(0.0);
    }
}


/**
 * @brief Sets value of z slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX
 */
void InputHandler::setZSlider(double value)
{
    double amplifiedZ = value * 100.0;
    if (amplifiedZ > 0.0) { // positive
        emit z_botSlider_ValChanged(0.0);
        if (amplifiedZ <= IOConstants::MIN_SLIDER) {
            emit z_topSlider_ValChanged(IOConstants::MIN_SLIDER);
        }  else {
            emit z_topSlider_ValChanged(amplifiedZ);
        }
    } else if (amplifiedZ < 0.0) { // negative
        emit z_topSlider_ValChanged(0.0);
        if (amplifiedZ >= -IOConstants::MIN_SLIDER+1) {
            emit z_botSlider_ValChanged(-IOConstants::MIN_SLIDER+1);
        }  else {
            emit z_botSlider_ValChanged(amplifiedZ);
        }
    } else { // zero
        emit z_botSlider_ValChanged(0.0);
        emit z_topSlider_ValChanged(0.0);
    }
}


/**
 * @brief Sets jx calculation for up and down translate, combining gamepad
 * control and keyboard control so they work together.
 * @param bool value
 */
void InputHandler::gamepad_axisLeftXSetter(double value)
{
    jx = value;
    setX((kx_Right+kx_Left)+jx);
}


/**
 * @brief Sets jy calulation for up and down translate, combining gamepad
 * control and keyboard control so they work together.
 * @param bool value
 */
void InputHandler::gamepad_axisLeftYSetter(double value)
{
    jy = value;
    setY((ky_Up+ky_Down)+jy);
}


/**
 * @brief Sets jz calulation for left and right turn, combining gamepad
 * control and keyboard control so they work together.
 * @param bool value
 */
void InputHandler::gamepad_axisRightXSetter(double value)
{
    jz = value;
    setZ((kz_TRight+kz_TLeft)+jz);
}


/**
 * @brief Sets ky calulation for up translate, combining gamepad control
 * and keyboard control so they work together.
 * @param bool value
 */
void InputHandler::keyboard_WSetter(bool value)
{
    if(value) { ky_Up = 1.0; } else { ky_Up = 0.0; }
    setY((ky_Up+ky_Down)+jy);
}


/**
 * @brief Sets ky calulation for down translate, combining gamepad control
 * and keyboard control so they work together.
 * @param bool value
 */
void InputHandler::keyboard_SSetter(bool value)
{
    if(value) { ky_Down = -1.0; } else { ky_Down = 0.0; }
    setY((ky_Up+ky_Down)+jy);
}


/**
 * @brief Sets kx calulation for left translate, combining gamepad control
 * and keyboard control so they work together.
 * @param bool value
 */
void InputHandler::keyboard_ASetter(bool value)
{
    if(value) { kx_Left = -1.0; } else { kx_Left = 0.0; }
    setX((kx_Right+kx_Left)+jx);
}


/**
 * @brief Sets kx calulation for right translate, combining gamepad control
 * and keyboard control so they work together.
 * @param bool value
 */
void InputHandler::keyboard_DSetter(bool value)
{
    if(value) { kx_Right = 1.0; } else { kx_Right = 0.0; }
    setX((kx_Right+kx_Left)+jx);
}


/**
 * @brief Sets kz calulation for right turn, combining gamepad control and
 * keyboard control so they work together.
 * @param bool value
 */
void InputHandler::keyboard_ESetter(bool value)
{
    if(value) { kz_TRight = 1.0; } else { kz_TRight = 0.0; }
    setZ((kz_TRight+kz_TLeft)+jz);
}


/**
 * @brief Sets kz calulation for left turn, combining gamepad control and
 * keyboard control so they work together.
 * @param bool value
 */
void InputHandler::keyboard_QSetter(bool value)
{
    if(value) { kz_TLeft = -1.0; } else { kz_TLeft = 0.0; }
    setZ((kz_TRight+kz_TLeft)+jz);
}


/**
 * @brief Sets current x value and clamps x between min and max
 * @return double x value
 */
void InputHandler::setX(double value)
{
    x = std::clamp(value, IOConstants::MIN, IOConstants::MAX);
    updateSliders();
}


/**
 * @brief Sets current y value and clamps x between min and max
 * @return double y value
 */
void InputHandler::setY(double value)
{
    y = std::clamp((value), IOConstants::MIN, IOConstants::MAX);
    updateSliders();
}


/**
 * @brief Sets current z value and clamps x between min and max
 * @return double z value
 */
void InputHandler::setZ(double value)
{
    z = std::clamp((value), IOConstants::MIN, IOConstants::MAX);
    updateSliders();
}


// Getters
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
