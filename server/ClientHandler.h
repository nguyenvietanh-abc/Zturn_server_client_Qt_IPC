// server/ClientHandler.h
#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <memory>
#include "SensorDataGenerator.h"

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandler(std::shared_ptr<SensorDataGenerator> generator,
                           QTcpSocket *socket,
                           QObject *parent = nullptr);
    ~ClientHandler();

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    void sendSensorData();

    QTcpSocket *const m_socket;
    std::shared_ptr<SensorDataGenerator> m_generator;
};

#endif // CLIENTHANDLER_H
