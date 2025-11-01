#include "ClientHandler.h"
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>

ClientHandler::ClientHandler(QTcpSocket *socket, QObject *parent)
    : QObject(parent), socket(socket)
{
    connect(socket, &QTcpSocket::readyRead, this, &ClientHandler::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ClientHandler::onDisconnected);
}

ClientHandler::~ClientHandler()
{
    socket->deleteLater();
}

void ClientHandler::onReadyRead()
{
    QByteArray request = socket->readAll();
    if (request.trimmed() == "GET_DATA")
    {
        QJsonObject json;
        json["pitch"] = generator.getPitch();
        json["yaw"] = generator.getYaw();
        json["temperature"] = generator.getTemperature();
        json["humidity"] = generator.getHumidity();

        QJsonDocument doc(json);
        socket->write(doc.toJson(QJsonDocument::Compact) + '\n');
        socket->flush();
    }
}

void ClientHandler::onDisconnected()
{
    socket->close();
    deleteLater();
}
