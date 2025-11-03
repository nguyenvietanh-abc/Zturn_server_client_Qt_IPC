// main.cpp
#include <QCoreApplication>
#include <QCommandLineParser>
#include "server/TcpServer.h"
#include "client/TcpClient.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("TCP Sensor System");
    app.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("TCP Server-Client 600Hz Sensor Data");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption serverMode("server", "Run as server (default port 5000)");
    QCommandLineOption clientMode("client", "Run as client", "host:port", "127.0.0.1:5000");
    parser.addOption(serverMode);
    parser.addOption(clientMode);
    parser.process(app);

    if (parser.isSet(serverMode)) {
        TcpServer server;
        if (!server.startServer(5000)) {
            return -1;
        }
    } else if (parser.isSet(clientMode)) {
        QStringList parts = parser.value(clientMode).split(':');
        QString host = parts.value(0, "127.0.0.1");
        quint16 port = parts.value(1, "5000").toUShort();

        TcpClient client(host, port);
        QObject::connect(&client, &TcpClient::dataReceived, [&](const SensorData &data) {
            qInfo().noquote() << QString("P:%1° Y:%2° T:%3°C H:%4%%")
                                     .arg(data.pitch, 6, 'f', 2)
                                     .arg(data.yaw, 6, 'f', 2)
                                     .arg(data.temperature, 5, 'f', 1)
                                     .arg(data.humidity, 5, 'f', 1);
        });
        client.start();
    } else {
        parser.showHelp(1);
    }

    return app.exec();
}
