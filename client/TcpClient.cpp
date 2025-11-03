// client/TcpClient.cpp
#include "TcpClient.h"
#include <QJsonDocument>
#include <QDebug>

TcpClient::TcpClient(const QString &host, quint16 port, QObject *parent)
    : QObject(parent)
    , m_host(host)
    , m_port(port)
{
    connect(&m_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&m_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(&m_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
                this, &TcpClient::onError);
    connect(&m_timer, &QTimer::timeout, this, &TcpClient::sendRequest);
}

void TcpClient::start()
{
    m_socket.connectToHost(m_host, m_port);
}

void TcpClient::onConnected()
{
    qInfo() << "Connected to server.";
    m_timer.start(1000 / 600); // ~1.666ms → 600Hz
}

void TcpClient::sendRequest()
{
    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write("GET_DATA\n");
    }
}

void TcpClient::onReadyRead()
{
    while (m_socket.canReadLine()) {
        QByteArray line = m_socket.readLine();
        QJsonDocument doc = QJsonDocument::fromJson(line);
        if (!doc.isNull() && doc.isObject()) {
            SensorData data = SensorData::fromJson(doc.object());
            emit dataReceived(data);
        }
    }
}

void TcpClient::onError(QAbstractSocket::SocketError socketError)
{
    qCritical() << "Client error (code:" << static_cast<int>(socketError) << "):" << m_socket.errorString();
        m_timer.stop();  // Dừng timer nếu lỗi, tránh spam request
        // Optional: reconnect logic (senior style)
        // QTimer::singleShot(5000, this, &TcpClient::start);  // Retry sau 5s
}
