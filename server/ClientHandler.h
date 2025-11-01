#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include "SensorDataGenerator.h"

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandler(QTcpSocket *socket, QObject *parent = nullptr);
    ~ClientHandler();

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *socket;
    SensorDataGenerator generator;
};

#endif // CLIENTHANDLER_H
