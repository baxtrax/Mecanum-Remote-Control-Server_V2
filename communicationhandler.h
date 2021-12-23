#ifndef COMMUNICATIONHANDLER_H
#define COMMUNICATIONHANDLER_H

#include "loggerhandler.h"

#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>
#include <QSettings>
#include <QTimer>

class CommunicationHandler : public QObject
{
    Q_OBJECT
public:
    CommunicationHandler(LoggerHandler *loggerRef, QSettings *settingsRef);

public slots:
    void sendMovementData(double FL, double BR, double FR, double BL);
    void updateWithSettings();
    void refreshConnection();
signals:
    void connectionStatus(bool);

private:
    LoggerHandler *logger;
    QSettings *settings;

    QHostAddress sendAddress;

    void initSocket();
    void initTimer();
    void readPendingDatagrams();
    void processDatagrams(QNetworkDatagram datagram);

    QUdpSocket *commSocket;
    QTimer *timeoutTimer;
    int lastConnectedPort;
    bool enabled;
};

#endif // COMMUNICATIONHANDLER_H
