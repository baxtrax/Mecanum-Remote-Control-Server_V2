#ifndef LOGGERHANDLER_H
#define LOGGERHANDLER_H

#include "constants.h"

#include <QDateTime>
#include <QString>
#include <QTextEdit>

class LoggerHandler : public QObject
{
    Q_OBJECT
public:
    LoggerHandler();
    void write(int level, QString text);
    void write(QString text);

    void setLevel(int level);
    void enableColorify(bool status);
    void enableShowTime(bool status);

    int getLevel();
    bool isShowTime();
    bool isColorify();

public slots:
    void clear();

signals:
    void appendingText(QString);
    void clearingText();

private:
    int currentLevel;
    bool showTime;
    bool colorify;
};

#endif // LOGGERHANDLER_H
