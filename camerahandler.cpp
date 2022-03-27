#include "camerahandler.h"

CameraHandler::CameraHandler(LoggerHandler *loggerRef, QSettings *settingsRef)
{
    logger = loggerRef;
    settings = settingsRef;
    vw = new QVideoWidget();
    mp = new QMediaPlayer(this);
    mp->setVideoOutput(vw);

    connect(mp, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(reportErrors(QMediaPlayer::Error)));
}

void CameraHandler::connectCamera(QNetworkRequest networkRequest) {
    mp->stop();
    mp->setMedia(networkRequest);
    mp->play();
}

void CameraHandler::reportErrors(QMediaPlayer::Error e) {
    int lastLevel = logger->getLevel();
    logger->setLevel(LoggerConstants::ERR);
    switch(e) {
    case QMediaPlayer::Error::NoError:
        break;
    case QMediaPlayer::Error::ResourceError:
        logger->write("Camera Error: The address could not be resolved.");
        break;
    case QMediaPlayer::Error::FormatError:
        logger->write("Camera Error: Media format is not (fully) supported! Playback may still be possible but features may be missing.");
        break;
    case QMediaPlayer::Error::NetworkError:
        logger->write("Camera Error: A network error occured.");
        break;
    case QMediaPlayer::Error::AccessDeniedError:
        logger->write("Camera Error: Access to media resource was denied.");
        break;
    case QMediaPlayer::Error::ServiceMissingError:
        logger->write("Camera Error: Playback service was not found.");
    case QMediaPlayer::Error::MediaIsPlaylist:
        logger->write("Camera Error: Media is a playlist not a single source.");
    }

    logger->setLevel(lastLevel);
}

void CameraHandler::updateWithSettings()
{
    if (vw->parentWidget() != NULL) {
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
