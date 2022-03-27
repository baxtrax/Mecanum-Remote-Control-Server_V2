#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include "loggerhandler.h"

#include <QObject>
#include <QSettings>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QNetworkRequest>

class CameraHandler : public QObject
{
    Q_OBJECT
public:
    CameraHandler(LoggerHandler *loggerRef, QSettings *settingsRef);
    QVideoWidget *getWidget();

public slots:
    void updateWithSettings();

private:
    LoggerHandler *logger;
    QSettings *settings;
    QVideoWidget *vw;
    QMediaPlayer *mp;

    void connectCamera(QNetworkRequest networkRequest);

};

#endif // CAMERAHANDLER_H
