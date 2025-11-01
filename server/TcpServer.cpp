#include "TcpServer.h"
#include <QTcpSocket>
#include <QDebug>

TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
{
}

bool TcpServer::start(quint16 port)
{
    if (!listen(QHostAddress::Any, port))
    {
        qCritical() << "Server failed to start on port" << port;
        return false;
    }
    qInfo() << "Server listening on port" << port;
    return true;
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);
    qInfo() << "New client connected from" << clientSocket->peerAddress().toString();

    ClientHandler *handler = new ClientHandler(clientSocket, this);
    connect(clientSocket, &QTcpSocket::disconnected, handler, &ClientHandler::deleteLater);
}
