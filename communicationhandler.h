#ifndef COMMUNICATIONHANDLER_H
#define COMMUNICATIONHANDLER_H

#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>

class CommunicationHandler : public QObject
{
    Q_OBJECT
public:
    CommunicationHandler();

public slots:
    void sendMovementData(double FL, double BR, double FR, double BL);
signals:

private:
    void initSocket();
    void readPendingDatagrams();
    void processDatagrams(QNetworkDatagram datagram);

    QUdpSocket *commSocket;
    int lastConnectedPort;
};

#endif // COMMUNICATIONHANDLER_H
