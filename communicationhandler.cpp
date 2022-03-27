#include "communicationhandler.h"

CommunicationHandler::CommunicationHandler(LoggerHandler *loggerRef, QSettings *settingsRef)
{
    logger = loggerRef;
    settings = settingsRef;

    lastConnectedPort = 0;
    sendAddress = QHostAddress::LocalHost;
    enabled = false;

    initSocket();
    initTimer();
}

void CommunicationHandler::sendMovementData(double FL, double BR, double FR, double BL)
{
    if (!(lastConnectedPort == 0) && enabled) {
        QString concatData = QString("m,") + QString::number(FL) + ',' + QString::number(BR) + ','
                             + QString::number(FR) + ',' + QString::number(BL);
        commSocket->writeDatagram(QByteArray(concatData.toUtf8()), sendAddress, lastConnectedPort);
        qDebug() << "S" << sendAddress.toString() << QString::number(lastConnectedPort) << "<-"
                 << concatData;
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
    connect(timeoutTimer, &QTimer::timeout, this, [this]() {
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
    if (datagram.data() == "") {
        emit connectionStatus(true);
        timeoutTimer->start(500);
    }
    qDebug() << "R" << datagram.senderAddress() << datagram.senderPort() << "->" << datagram.data();
}

void CommunicationHandler::updateWithSettings()
{
    enabled = settings->value(SettingsConstants::CONN_COMM_EN, SettingsConstants::D_CONN_COMM_EN)
                  .toBool();

    //Update sending address and port
    lastConnectedPort = settings
                            ->value(SettingsConstants::CONN_COMM_PORT,
                                    SettingsConstants::D_CONN_COMM_PORT)
                            .toInt();
    sendAddress = QHostAddress(
        settings->value(SettingsConstants::CONN_COMM_ADDRESS, SettingsConstants::D_CONN_COMM_ADDRESS)
            .toString());

    // Make sure closed before rebinding.
    if (!(commSocket->state() == QUdpSocket::UnconnectedState)) {
        commSocket->close();
    }
    //Bind to local ip to see if any data is being sent over.
    if (enabled) {
        // TODO: FIX THIS TO BE MORE DYNAMIC
        // Just assume first address is what we are looking for.
        QHostAddress recvaddress = QHostAddress(QHostAddress::LocalHost);
        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
        for (auto &address : QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
                qDebug() << address.toString();
                recvaddress = address;
                break; // Will break after the first IPv4 found.
            }
        }

        if (recvaddress == localhost) {
            logger->write(LoggerConstants::WARNING,
                          "Could not find other IPv4 Addresses! Using Local Host instead.");
        }

        //if (commSocket->bind(QHostAddress::LocalHost, lastConnectedPort)) {
        if (commSocket->bind(QHostAddress("192.168.1.140"), lastConnectedPort)) {
            logger->write(LoggerConstants::INFO,
                          QString("Communication listening on: ") + recvaddress.toString()
                              + QString(":") + QString::number(lastConnectedPort));
        } else {
            logger->write(LoggerConstants::WARNING,
                          QString("Communication failed to bind to: ") + recvaddress.toString()
                              + QString(":") + QString::number(lastConnectedPort) + ": "
                              + commSocket->errorString() + ".");
        }
        logger->write(LoggerConstants::INFO,
                      QString("Communication sending on: ") + sendAddress.toString() + QString(":")
                          + QString::number(lastConnectedPort));
    }
}
