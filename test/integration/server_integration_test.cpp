// Seminar tests – Server (integracioni testovi). Tag: [seminar][integration]

#include <catch2/catch_test_macros.hpp>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QApplication>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>

#define private public
#define protected public
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/Server/server.h"
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/MessageType.h"
#undef private
#undef protected

TEST_CASE("Server parseMessage – client sends create_room, receives join_room", "[seminar][integration]") {
    QTcpSocket socket;
    {
        Server server;
        server.startServer();
        REQUIRE(server.isListening());

        socket.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socket.waitForConnected(3000));
        for (int i = 0; i < 120; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject msg;
        msg[MessageType::TYPE] = MessageType::CREATE_ROOM;
        msg[MessageType::USERNAME] = "ana";
        msg[MessageType::ROOM_NAME] = "r1";
        msg[MessageType::DURATION] = 60;
        socket.write(QJsonDocument(msg).toJson(QJsonDocument::Compact));
        socket.flush();

        for (int i = 0; i < 150; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socket.bytesAvailable() > 0) break;
        }
        REQUIRE(socket.bytesAvailable() > 0);
        QByteArray received = socket.readAll();
        REQUIRE(received.contains("join_room"));
        REQUIRE(received.contains("r1"));

        QJsonObject leave;
        leave[MessageType::TYPE] = MessageType::LEAVE_ROOM;
        socket.write(QJsonDocument(leave).toJson(QJsonDocument::Compact));
        socket.flush();
        for (int i = 0; i < 80; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);
    }
    for (int i = 0; i < 30; ++i)
        qApp->processEvents(QEventLoop::AllEvents, 50);
}

TEST_CASE("Server parseMessage – client sends get_rooms after create, receives room name", "[seminar][integration]") {
    QTcpSocket socketA, socketB;
    {
        Server server;
        server.startServer();
        REQUIRE(server.isListening());

        socketA.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socketA.waitForConnected(3000));
        for (int i = 0; i < 120; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject createMsg;
        createMsg[MessageType::TYPE] = MessageType::CREATE_ROOM;
        createMsg[MessageType::USERNAME] = "alice";
        createMsg[MessageType::ROOM_NAME] = "r1";
        createMsg[MessageType::DURATION] = 60;
        socketA.write(QJsonDocument(createMsg).toJson(QJsonDocument::Compact));
        socketA.flush();
        for (int i = 0; i < 150; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketA.bytesAvailable() > 0) break;
        }
        (void)socketA.readAll();

        socketB.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socketB.waitForConnected(3000));
        for (int i = 0; i < 120; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject getMsg;
        getMsg[MessageType::TYPE] = MessageType::GET_ROOMS;
        socketB.write(QJsonDocument(getMsg).toJson(QJsonDocument::Compact));
        socketB.flush();
        for (int i = 0; i < 150; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketB.bytesAvailable() > 0) break;
        }
        QByteArray received = socketB.readAll();
        REQUIRE(received.contains("get_rooms"));
        REQUIRE(received.contains("r1"));

        QJsonObject leave;
        leave[MessageType::TYPE] = MessageType::LEAVE_ROOM;
        socketA.write(QJsonDocument(leave).toJson(QJsonDocument::Compact));
        socketA.flush();
        for (int i = 0; i < 60; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);
    }
    for (int i = 0; i < 20; ++i)
        qApp->processEvents(QEventLoop::AllEvents, 50);
}

TEST_CASE("Server parseMessage – client sends text_message, other client receives", "[seminar][integration]") {
    QTcpSocket socketA, socketB;
    {
        Server server;
        server.startServer();
        REQUIRE(server.isListening());

        socketA.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socketA.waitForConnected(3000));
        for (int i = 0; i < 120; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject createMsg;
        createMsg[MessageType::TYPE] = MessageType::CREATE_ROOM;
        createMsg[MessageType::USERNAME] = "alice";
        createMsg[MessageType::ROOM_NAME] = "r1";
        createMsg[MessageType::DURATION] = 60;
        socketA.write(QJsonDocument(createMsg).toJson(QJsonDocument::Compact));
        socketA.flush();
        for (int i = 0; i < 150; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketA.bytesAvailable() > 0) break;
        }
        (void)socketA.readAll();

        socketB.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socketB.waitForConnected(3000));
        for (int i = 0; i < 120; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject joinMsg;
        joinMsg[MessageType::TYPE] = MessageType::JOIN_ROOM;
        joinMsg[MessageType::USERNAME] = "bob";
        joinMsg[MessageType::ROOM_NAME] = "r1";
        socketB.write(QJsonDocument(joinMsg).toJson(QJsonDocument::Compact));
        socketB.flush();
        for (int i = 0; i < 150; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketB.bytesAvailable() > 0) break;
        }
        (void)socketB.readAll();

        QJsonObject textMsg;
        textMsg[MessageType::TYPE] = MessageType::TEXT_MESSAGE;
        textMsg[MessageType::CONTENT] = "hello_chat";
        socketA.write(QJsonDocument(textMsg).toJson(QJsonDocument::Compact));
        socketA.flush();
        for (int i = 0; i < 180; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketB.bytesAvailable() > 0) break;
        }
        REQUIRE(socketB.bytesAvailable() > 0);
        QByteArray received = socketB.readAll();
        REQUIRE(received.contains("text_message"));
        REQUIRE(received.contains("hello_chat"));

        QJsonObject leave;
        leave[MessageType::TYPE] = MessageType::LEAVE_ROOM;
        socketA.write(QJsonDocument(leave).toJson(QJsonDocument::Compact));
        socketA.flush();
        socketB.write(QJsonDocument(leave).toJson(QJsonDocument::Compact));
        socketB.flush();
        for (int i = 0; i < 60; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);
    }
    for (int i = 0; i < 20; ++i)
        qApp->processEvents(QEventLoop::AllEvents, 50);
}

TEST_CASE("Server parseMessage – client sends choose_word in room", "[seminar][integration]") {
    QTcpSocket socketA, socketB;
    {
        Server server;
        server.startServer();
        REQUIRE(server.isListening());

        socketA.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socketA.waitForConnected(3000));
        for (int i = 0; i < 120; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject createMsg;
        createMsg[MessageType::TYPE] = MessageType::CREATE_ROOM;
        createMsg[MessageType::USERNAME] = "alice";
        createMsg[MessageType::ROOM_NAME] = "r1";
        createMsg[MessageType::DURATION] = 60;
        socketA.write(QJsonDocument(createMsg).toJson(QJsonDocument::Compact));
        socketA.flush();
        for (int i = 0; i < 150; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketA.bytesAvailable() > 0) break;
        }
        (void)socketA.readAll();

        socketB.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socketB.waitForConnected(3000));
        for (int i = 0; i < 120; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject joinMsg;
        joinMsg[MessageType::TYPE] = MessageType::JOIN_ROOM;
        joinMsg[MessageType::USERNAME] = "bob";
        joinMsg[MessageType::ROOM_NAME] = "r1";
        socketB.write(QJsonDocument(joinMsg).toJson(QJsonDocument::Compact));
        socketB.flush();
        for (int i = 0; i < 150; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketB.bytesAvailable() > 0) break;
        }
        (void)socketB.readAll();

        QJsonObject chooseMsg;
        chooseMsg[MessageType::TYPE] = MessageType::CHOOSE_WORD;
        chooseMsg[MessageType::CONTENT] = "secret";
        socketA.write(QJsonDocument(chooseMsg).toJson(QJsonDocument::Compact));
        socketA.flush();
        for (int i = 0; i < 80; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject leave;
        leave[MessageType::TYPE] = MessageType::LEAVE_ROOM;
        socketA.write(QJsonDocument(leave).toJson(QJsonDocument::Compact));
        socketA.flush();
        socketB.write(QJsonDocument(leave).toJson(QJsonDocument::Compact));
        socketB.flush();
        for (int i = 0; i < 60; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);
    }
    for (int i = 0; i < 20; ++i)
        qApp->processEvents(QEventLoop::AllEvents, 50);
}

TEST_CASE("Server parseMessage – unknown type (ERROR branch)", "[seminar][integration]") {
    QTcpSocket socket;
    {
        Server server;
        server.startServer();
        REQUIRE(server.isListening());

        socket.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socket.waitForConnected(3000));
        for (int i = 0; i < 80; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject msg;
        msg[MessageType::TYPE] = "unknown_type";
        socket.write(QJsonDocument(msg).toJson(QJsonDocument::Compact));
        socket.flush();
        for (int i = 0; i < 50; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        REQUIRE(socket.state() == QAbstractSocket::ConnectedState);
    }
    for (int i = 0; i < 20; ++i)
        qApp->processEvents(QEventLoop::AllEvents, 50);
}

TEST_CASE("Server broadcastCanvas – client sends canvas, other client receives", "[seminar][integration]") {
    QTcpSocket socketA, socketB;
    {
        Server server;
        server.startServer();
        REQUIRE(server.isListening());

        socketA.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socketA.waitForConnected(3000));
        for (int i = 0; i < 120; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject createMsg;
        createMsg[MessageType::TYPE] = MessageType::CREATE_ROOM;
        createMsg[MessageType::USERNAME] = "alice";
        createMsg[MessageType::ROOM_NAME] = "r1";
        createMsg[MessageType::DURATION] = 60;
        socketA.write(QJsonDocument(createMsg).toJson(QJsonDocument::Compact));
        socketA.flush();
        for (int i = 0; i < 150; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketA.bytesAvailable() > 0) break;
        }
        REQUIRE(socketA.bytesAvailable() > 0);
        (void)socketA.readAll();

        socketB.connectToHost(QHostAddress::LocalHost, 1234);
        REQUIRE(socketB.waitForConnected(3000));
        for (int i = 0; i < 120; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);

        QJsonObject joinMsg;
        joinMsg[MessageType::TYPE] = MessageType::JOIN_ROOM;
        joinMsg[MessageType::USERNAME] = "bob";
        joinMsg[MessageType::ROOM_NAME] = "r1";
        socketB.write(QJsonDocument(joinMsg).toJson(QJsonDocument::Compact));
        socketB.flush();
        for (int i = 0; i < 150; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketB.bytesAvailable() > 0) break;
        }
        REQUIRE(socketB.bytesAvailable() > 0);
        (void)socketB.readAll();

        QJsonObject canvasMsg;
        canvasMsg[MessageType::TYPE] = MessageType::CANVAS_MESSAGE;
        canvasMsg[MessageType::CONTENT] = "pixelDataXYZ";
        socketA.write(QJsonDocument(canvasMsg).toJson(QJsonDocument::Compact));
        socketA.flush();
        for (int i = 0; i < 180; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (socketB.bytesAvailable() > 0) break;
        }
        REQUIRE(socketB.bytesAvailable() > 0);
        QByteArray received = socketB.readAll();
        REQUIRE(received.contains("canvas_message"));
        REQUIRE(received.contains("pixelDataXYZ"));

        QJsonObject leave;
        leave[MessageType::TYPE] = MessageType::LEAVE_ROOM;
        socketA.write(QJsonDocument(leave).toJson(QJsonDocument::Compact));
        socketA.flush();
        socketB.write(QJsonDocument(leave).toJson(QJsonDocument::Compact));
        socketB.flush();
        for (int i = 0; i < 80; ++i)
            qApp->processEvents(QEventLoop::AllEvents, 40);
    }
    for (int i = 0; i < 30; ++i)
        qApp->processEvents(QEventLoop::AllEvents, 50);
}

