#ifndef LOGGERHANDLER_H
#define LOGGERHANDLER_H

#include "constants.h"

#include <QDateTime>
#include <QSettings>
#include <QString>
#include <QTextEdit>

class LoggerHandler : public QObject
{
    Q_OBJECT
public:
    LoggerHandler(QSettings *settingsRef);
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
    void updateWithSettings();

signals:
    void appendingText(QString);
    void clearingText();

private:
    QSettings *settings;
    int currentLevel;
    bool showTime;
    bool colorify;
};

#endif // LOGGERHANDLER_H
