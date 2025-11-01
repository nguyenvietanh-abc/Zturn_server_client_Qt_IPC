#include <QCoreApplication>
#include <QCommandLineParser>
#include "server/TcpServer.h"
#include "client/TcpClient.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption serverOpt({"s", "server"}, "Run as server");
    QCommandLineOption clientOpt({"c", "client"}, "Run as client");
    parser.addOption(serverOpt);
    parser.addOption(clientOpt);

    parser.process(app);

    if (parser.isSet(serverOpt))
    {
        TcpServer server;
        if (!server.start(5000))
            return -1;
        return app.exec();
    }
    else if (parser.isSet(clientOpt))
    {
        TcpClient client("127.0.0.1", 5000);
        client.start();
        return app.exec();
    }
    else
    {
        qCritical() << "Please specify --server or --client";
        return 1;
    }
}
