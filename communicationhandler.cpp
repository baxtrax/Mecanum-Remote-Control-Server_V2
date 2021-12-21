#include "communicationhandler.h"

CommunicationHandler::CommunicationHandler(LoggerHandler *loggerRef, QSettings *settingsRef)
{
    logger = loggerRef;
    settings = settingsRef;

    lastConnectedPort = 0;
    enabled = false;

    initSocket();
    initTimer();
}

void CommunicationHandler::sendMovementData(double FL, double BR, double FR, double BL)
{
    if (!(lastConnectedPort == 0) && enabled) {
        qDebug() << "sending movements";
        QString concatData = 'm' + QString::number(FL) + ',' + QString::number(BR) + ','
                             + QString::number(FR) + ',' + QString::number(BL);
        commSocket->writeDatagram(QByteArray(concatData.toUtf8()),
                                  QHostAddress::LocalHost,
                                  lastConnectedPort);
    }
}

void CommunicationHandler::initSocket()
{
    commSocket = new QUdpSocket();
    connect(commSocket, &QUdpSocket::readyRead, this, &CommunicationHandler::readPendingDatagrams);
}

void CommunicationHandler::initTimer()
{
    timeoutTimer = new QTimer(this);
    connect(timeoutTimer,
            &QTimer::timeout,
            this,
            [this]() {
                emit connectionStatus(false);
                qDebug() << "timedout";
            });
    timeoutTimer->setSingleShot(true);
}

void CommunicationHandler::refreshConnection()
{
    timeoutTimer->stop();
    emit connectionStatus(false);
    updateWithSettings(); //Closes and rebinds to currently saved settings
}

void CommunicationHandler::readPendingDatagrams()
{
    while (commSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = commSocket->receiveDatagram();
        processDatagrams(datagram);
    }
}

void CommunicationHandler::processDatagrams(QNetworkDatagram datagram)
{
    // TODO Implement switch for incoming gyro etc.
    lastConnectedPort = datagram.senderPort();
    if(datagram.data() == "") {
        emit connectionStatus(true);
        timeoutTimer->start(500);
    }
    qDebug() << datagram.data() << '|' << datagram.senderAddress() << datagram.senderPort();
}

void CommunicationHandler::updateWithSettings()
{

    enabled = settings->value(SettingsConstants::CONN_COMM_EN, SettingsConstants::D_CONN_COMM_EN).toBool();

    QString savedAddress = settings->value(SettingsConstants::CONN_COMM_ADDRESS, SettingsConstants::D_CONN_COMM_ADDRESS).toString();
    int savedPort = settings->value(SettingsConstants::CONN_COMM_PORT, SettingsConstants::D_CONN_COMM_PORT).toInt();
    QHostAddress csavedAddress = QHostAddress(savedAddress);
    // Make sure closed before rebinding.
    if (!(commSocket->state() == QUdpSocket::UnconnectedState)) {
        commSocket->close();
    }
    if (enabled) {
        if (commSocket->bind(csavedAddress, savedPort)) {
            logger->write(LoggerConstants::INFO, QString("Communication binded to: ") + QString(savedAddress) + QString(":") + QString::number(savedPort));
        } else {
            logger->write(LoggerConstants::WARNING, QString("Communication failed to bind to: ") + QString(savedAddress) + QString(":") + QString::number(savedPort));
        }
    }
}
