#include "camerahandler.h"

CameraHandler::CameraHandler(LoggerHandler *loggerRef, QSettings *settingsRef)
{
    logger = loggerRef;
    settings = settingsRef;
    vw = new QVideoWidget();
    mp = new QMediaPlayer();
    mp->setVideoOutput(vw);

}

void CameraHandler::connectCamera(QNetworkRequest networkRequest) {
    mp->stop();
    mp->setMedia(networkRequest);
    mp->play();
}

void CameraHandler::updateWithSettings()
{
    if (vw->parentWidget() != NULL) {
        qDebug() << "Valid";
        if (settings->value(SettingsConstants::CONN_CAM_EN, SettingsConstants::D_CONN_CAM_EN).toBool()) {
            vw->show();
        } else {
            vw->hide();
        }
    }

    QString url = settings->value(SettingsConstants::CONN_CAM_ADDRESS, SettingsConstants::D_CONN_CAM_ADDRESS).toString();
    qDebug() << url;
    connectCamera(QNetworkRequest(QUrl(url)));
}

QVideoWidget *CameraHandler::getWidget() {
    return vw;
}
