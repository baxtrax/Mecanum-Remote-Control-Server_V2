#ifndef COMMUNICATIONHANDLER_H
#define COMMUNICATIONHANDLER_H

#include "loggerhandler.h"

#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>
#include <QSettings>

class CommunicationHandler : public QObject
{
    Q_OBJECT
public:
    CommunicationHandler(LoggerHandler *loggerRef, QSettings *settingsRef);

public slots:
    void sendMovementData(double FL, double BR, double FR, double BL);
    void updateWithSettings();
signals:

private:
    LoggerHandler *logger;
    QSettings *settings;

    void initSocket();
    void readPendingDatagrams();
    void processDatagrams(QNetworkDatagram datagram);

    QUdpSocket *commSocket;
    int lastConnectedPort;
};

#endif // COMMUNICATIONHANDLER_H
