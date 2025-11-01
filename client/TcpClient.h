#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(const QString &host, quint16 port, QObject *parent = nullptr);
    void start();

private slots:
    void onConnected();
    void onReadyRead();
    void sendRequest();

private:
    QTcpSocket socket;
    QTimer timer;
    QString host;
    quint16 port;
};

#endif // TCPCLIENT_H
