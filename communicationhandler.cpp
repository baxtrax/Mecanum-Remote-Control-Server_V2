#include "communicationhandler.h"

CommunicationHandler::CommunicationHandler(LoggerHandler *loggerRef, QSettings *settingsRef)
{
    logger = loggerRef;
    settings = settingsRef;

    initSocket();
    lastConnectedPort = 0;
}

void CommunicationHandler::sendMovementData(double FL, double BR, double FR, double BL)
{
    if (!(lastConnectedPort == 0)) {
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
    commSocket->bind(QHostAddress::LocalHost, 30020); // Default to localhost

    connect(commSocket, &QUdpSocket::readyRead, this, &CommunicationHandler::readPendingDatagrams);
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
    qDebug() << datagram.data() << '|' << datagram.senderAddress() << datagram.senderPort();
}

void CommunicationHandler::updateWithSettings()
{
    QString savedAddress = settings->value(SettingsConstants::CONN_COMM_ADDRESS, SettingsConstants::D_CONN_COMM_ADDRESS).toString();
    int savedPort = settings->value(SettingsConstants::CONN_COMM_PORT, SettingsConstants::D_CONN_COMM_PORT).toInt();
    QHostAddress csavedAddress = QHostAddress(savedAddress);

    commSocket->close();
    if (commSocket->bind(csavedAddress, savedPort)) {
        logger->write(LoggerConstants::INFO, QString("Communication binded to: ") + QString(savedAddress) + QString(":") + QString::number(savedPort));
    } else {
        logger->write(LoggerConstants::WARNING, QString("Communication failed to bind to: ") + QString(savedAddress) + QString(":") + QString::number(savedPort));
    }
}
