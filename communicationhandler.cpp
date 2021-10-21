#include "communicationhandler.h"

CommunicationHandler::CommunicationHandler()
{
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
    commSocket->bind(QHostAddress::LocalHost, 30020);

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
