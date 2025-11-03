// server/TcpServer.h
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <memory>
#include "SensorDataGenerator.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();

    bool startServer(quint16 port = 5000);

private:
    void incomingConnection(qintptr socketDescriptor) override;

    std::shared_ptr<SensorDataGenerator> m_generator;
};

#endif // TCPSERVER_H
