#include "loggerhandler.h"

// Constructor
LoggerHandler::LoggerHandler()
{
    currentLevel = LoggerConstants::DEBUG;
    showTime = true;
}

/**
 * @brief Will write the the specified message text to the logger output, with
 * the currently set default level of information.
 * @param Text to be sent.
 */
void LoggerHandler::write(QString text)
{
    QString time = "";
    if (isShowTime()) {
        time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    }

    if (isColorify()) {
        // TODO: move colors so they can be swapped between dark and light mode
        switch (getLevel()) {
        case LoggerConstants::DEBUG:
            text = "<font color=\"#9F9F9F\">" + time + " [D]: " + text + "</font>";
            emit appendingText(text);
            break;
        case LoggerConstants::INFO:
            text = "<font color=\"#FFFFFF\">" + time + " [I]: " + text + "</font>";
            emit appendingText(text);
            break;
        case LoggerConstants::WARNING:
            text = "<font color=\"#FFEA95\">" + time + " [W]: " + text + "</font>";
            emit appendingText(text);
            break;
        case LoggerConstants::ERR:
            text = "<font color=\"#FE6E7C\">" + time + " [E]: " + text + "</font>";
            emit appendingText(text);
            break;
        case LoggerConstants::FATAL:
            text = "<font color=\"#FF0505\">" + time + " [F]: " + text + "</font>";
            emit appendingText(text);
            break;
        }
    } else {
        switch (getLevel()) {
        case LoggerConstants::DEBUG:
            text = "<font color=\"#FFFFFF\">" + time + " [D]: " + text + "</font>";
            emit appendingText(text);
            break;
        case LoggerConstants::INFO:
            text = "<font color=\"#FFFFFF\">" + time + " [I]: " + text + "</font>";
            emit appendingText(text);
            break;
        case LoggerConstants::WARNING:
            text = "<font color=\"#FFFFFF\">" + time + " [W]: " + text + "</font>";
            emit appendingText(text);
            break;
        case LoggerConstants::ERR:
            text = "<font color=\"#FFFFFF\">" + time + " [E]: " + text + "</font>";
            emit appendingText(text);
            break;
        case LoggerConstants::FATAL:
            text = "<font color=\"#FFFFFF\">" + time + " [F]: " + text + "</font>";
            emit appendingText(text);
            break;
        }
    }
}

/**
 * @brief Will write the the specified message text to the logger output, with
 * the desired level of information.
 * @param Level as a constant from LoggerConstants choices.
 * @param Text to be sent.
 */
void LoggerHandler::write(int level, QString text)
{
    int prevLevel = getLevel();
    setLevel(level);
    write(text);
    setLevel(prevLevel);
}

/**
 * @brief Clears the logger output.
 */
void LoggerHandler::clear()
{
    emit clearingText();
}

// Setters
/**
 * @brief Sets level of logging for sending messages to logger output.
 * @param Level as a constant from LoggerConstants choices.
 */
void LoggerHandler::setLevel(int level)
{
    currentLevel = level;
}

/**
 * @brief Sets if time should be displayed next to the logger inputs or not.
 * @param boolean status of time being shown.
 */
void LoggerHandler::enableShowTime(bool status)
{
    showTime = status;
}

/**
 * @brief Sets if text on the logger output should be colored or not.
 * @param boolean status of colored text.
 */
void LoggerHandler::enableColorify(bool status)
{
    colorify = status;
}

// Getters
/**
 * @brief Gets the current level for messages that are sent without a level
 * descriptor.
 * @return int level as a constant from LoggerConstants choices.
 */
int LoggerHandler::getLevel()
{
    return currentLevel;
}

/**
 * @brief Gets if time should be displayed next to the logger inputs or not.
 * @return boolean current status.
 */
bool LoggerHandler::isShowTime()
{
    return showTime;
}

/**
 * @brief Gets if text on the logger output should be colored or not.
 * @return boolean current status.
 */
bool LoggerHandler::isColorify()
{
    return colorify;
}
