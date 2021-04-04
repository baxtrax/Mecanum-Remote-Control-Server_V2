#include "loggerhandler.h"

LoggerHandler::LoggerHandler(QTextEdit *logTextEditRef)
{
    logTextEdit = logTextEditRef;
    currentLevel = LoggerConstants::DEBUG;
    showTime = true;
}


void LoggerHandler::write(QString text)
{
    QString time = "";
    if (isShowTime()) {
        time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    }

    if (isColorify()) {
        switch (getLevel()) {
        case LoggerConstants::DEBUG:
            text = time + " [D]: " + text;
            logTextEdit->setTextColor(QColor(QRgb(0x9F9F9F)));
            logTextEdit->append(text);
            break;
        case LoggerConstants::INFO:
            text = time + " [I]: " + text;
            logTextEdit->setTextColor(QColor(QRgb(0xFFFFFF)));
            logTextEdit->append(text);
            break;
        case LoggerConstants::WARNING:
            text = time + " [W]: " + text;
            logTextEdit->setTextColor(QColor(QRgb(0xFFEA95)));
            logTextEdit->append(text);
            break;
        case LoggerConstants::ERR:
            text = time + " [E]: " + text;
            logTextEdit->setTextColor(QColor(QRgb(0xFE6E7C)));
            logTextEdit->append(text);
            break;
        case LoggerConstants::FATAL:
            text = time + " [F]: " + text;
            logTextEdit->setTextColor(QColor(QRgb(0xFF0505)));
            logTextEdit->append(text);
            break;
        }
    } else {
        switch (getLevel()) {
        case LoggerConstants::DEBUG:
            text = time + " [D]: " + text;
            logTextEdit->append(text);
            break;
        case LoggerConstants::INFO:
            text = time + " [I:] " + text;
            logTextEdit->append(text);
            break;
        case LoggerConstants::WARNING:
            text = time + " [W]: " + text;
            logTextEdit->append(text);
            break;
        case LoggerConstants::ERR:
            text = time + " [E]: " + text;
            logTextEdit->append(text);
            break;
        case LoggerConstants::FATAL:
            text = time + " [F]: " + text;
            logTextEdit->append(text);
            break;
        }
    }
}

void LoggerHandler::write(int level, QString text)
{
    int prevLevel = getLevel();
    setLevel(level);
    write(text);
    setLevel(prevLevel);
}

void LoggerHandler::clear()
{
    logTextEdit->clear();
}

// Setters

// TODO add input validation
void LoggerHandler::setLevel(int level)
{
    currentLevel = level;
}


void LoggerHandler::enableShowTime(bool status)
{
    showTime = status;
}


void LoggerHandler::enableColorify(bool status)
{
    colorify = status;
}


// Getters

int LoggerHandler::getLevel()
{
    return currentLevel;
}


bool LoggerHandler::isShowTime()
{
    return showTime;
}


bool LoggerHandler::isColorify()
{
    return colorify;
}
