// client/TcpClient.h
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QAbstractSocket>          // Bổ sung: SocketError
#include "../server/SensorData.h"    // Đường dẫn tương đối

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(const QString &host, quint16 port, QObject *parent = nullptr);
    void start();

signals:
    void dataReceived(const SensorData &data);

private slots:
    void onConnected();
    void sendRequest();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError); //: explicit param

private:
    QTcpSocket m_socket;
    QTimer m_timer;
    QString m_host;
    quint16 m_port;
};

#endif // TCPCLIENT_H
