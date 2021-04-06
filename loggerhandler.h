#ifndef LOGGERHANDLER_H
#define LOGGERHANDLER_H

#include <QTextEdit>
#include <QString>
#include <QDateTime>
#include "constants.h"


class LoggerHandler
{
public:
    LoggerHandler(QTextEdit *logTextEditRef);
    void clear();
    void write(int level, QString text);
    void write(QString text);

    void setLevel(int level);
    void enableColorify(bool status);
    void enableShowTime(bool status);

    int getLevel();
    bool isShowTime();
    bool isColorify();

private:
    QTextEdit *logTextEdit;
    int currentLevel;
    bool showTime;
    bool colorify;
};

#endif // LOGGERHANDLER_H
