// server/TcpServer.cpp
#include "TcpServer.h"
#include "ClientHandler.h"
#include <QTcpSocket>

TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
{
    m_generator = std::make_shared<SensorDataGenerator>(this);
    m_generator->startGenerating(1); // 1000Hz
}

TcpServer::~TcpServer() = default;

bool TcpServer::startServer(quint16 port)
{
    if (!this->listen(QHostAddress::Any, port)) {
        qCritical() << "Server failed:" << this->errorString();
        return false;
    }
    qInfo() << "Server started on port" << port;
    return true;
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (!clientSocket->setSocketDescriptor(socketDescriptor)) {
        qWarning() << "Invalid socket descriptor";
        clientSocket->deleteLater();
        return;
    }

    new ClientHandler(m_generator, clientSocket, this);
    qInfo() << "Client connected:" << clientSocket->peerAddress().toString();
}
