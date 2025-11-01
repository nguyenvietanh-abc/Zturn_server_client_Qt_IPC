QT += core network
CONFIG += console c++17
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += \
    main.cpp \
    server/TcpServer.cpp \
    server/ClientHandler.cpp \
    server/SensorDataGenerator.cpp \
    client/TcpClient.cpp

HEADERS += \
    server/TcpServer.h \
    server/ClientHandler.h \
    server/SensorDataGenerator.h \
    client/TcpClient.h
