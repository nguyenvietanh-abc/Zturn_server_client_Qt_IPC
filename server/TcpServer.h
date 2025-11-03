// server/TcpServer.h
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>   // include explicit QTcpServer
#include <memory>       // Cho std::shared_ptr
#include <QHostAddress>  // Cho listen()
#include "SensorDataGenerator.h"

class TcpServer : public QTcpServer // Đảm bảo public inheritance
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);  // Explicit constructor
    ~TcpServer();

    bool startServer(quint16 port = 5000);  // Getter/setter style

private:
    void incomingConnection(qintptr socketDescriptor) override;     // Override explicit

    std::shared_ptr<SensorDataGenerator> m_generator;             // Member private
};

#endif // TCPSERVER_H
