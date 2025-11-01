#include "TcpClient.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

TcpClient::TcpClient(const QString &host, quint16 port, QObject *parent)
    : QObject(parent), host(host), port(port)
{
    connect(&socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(&timer, &QTimer::timeout, this, &TcpClient::sendRequest);
}

void TcpClient::start()
{
    socket.connectToHost(host, port);
}

void TcpClient::onConnected()
{
    qInfo() << "Connected to server.";
    timer.start(1000 / 600); // 600Hz
}

void TcpClient::sendRequest()
{
    socket.write("GET_DATA\n");
    socket.flush();
}

void TcpClient::onReadyRead()
{
    QByteArray data = socket.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();

    qInfo().noquote() << QString("Pitch: %1 | Yaw: %2 | Temp: %3°C | Hum: %4%%")
                             .arg(json["pitch"].toDouble(), 0, 'f', 2)
                             .arg(json["yaw"].toDouble(), 0, 'f', 2)
                             .arg(json["temperature"].toDouble(), 0, 'f', 2)
                             .arg(json["humidity"].toDouble(), 0, 'f', 2);
}
