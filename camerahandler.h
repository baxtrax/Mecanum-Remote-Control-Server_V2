#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include "loggerhandler.h"

#include <QMediaPlayer>
#include <QNetworkRequest>
#include <QObject>
#include <QSettings>
#include <QVideoWidget>

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

private slots:
    void reportErrors(QMediaPlayer::Error e);
};

#endif // CAMERAHANDLER_H
