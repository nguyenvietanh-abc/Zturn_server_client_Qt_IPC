#include "ClientHandler.h"
#include <QJsonDocument>

ClientHandler::ClientHandler(std::shared_ptr<SensorDataGenerator> generator,
                             QTcpSocket *socket,
                             QObject *parent)
    : QObject(static_cast<QObject*>(parent))  // Sửa: cast explicit parent → tránh pass socket nhầm vào QObject
    , m_socket(socket)
    , m_generator(std::move(generator))  // Move để tránh copy
{
    if (m_socket) {
        m_socket->setParent(this);  // RAII: set parent sau base init
    }

    connect(m_socket, &QTcpSocket::readyRead, this, &ClientHandler::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientHandler::onDisconnected);
}

ClientHandler::~ClientHandler() = default;

void ClientHandler::onReadyRead()
{
    while (m_socket->bytesAvailable()) {
        QByteArray request = m_socket->readLine().trimmed();
        if (request == "GET_DATA") {
            sendSensorData();
        }
    }
}

void ClientHandler::sendSensorData()
{
    const SensorData data = m_generator->currentData();
    QJsonDocument doc(data.toJson());
    QByteArray response = doc.toJson(QJsonDocument::Compact) + '\n';
    m_socket->write(response);
    m_socket->flush();
}

void ClientHandler::onDisconnected()
{
    m_socket->deleteLater();
    deleteLater();
}
