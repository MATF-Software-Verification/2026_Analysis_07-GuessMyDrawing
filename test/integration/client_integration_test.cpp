// Seminar tests – Client (integracioni testovi). Tag: [seminar][integration]

#include <catch2/catch_test_macros.hpp>
#include <QHostAddress>
#include <QApplication>
#include <QEventLoop>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>

#define private public
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/Application/client.h"
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/Server/server.h"
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/MessageType.h"
#undef private

TEST_CASE("Client connectToServer and createRoom with real server – receives joinedRoom", "[seminar][integration]") {
    Server server;
    server.startServer();
    REQUIRE(server.isListening());

    Client client("testuser");
    bool joinedEmitted = false;
    QObject::connect(&client, &Client::joinedRoom, [&joinedEmitted](bool) { joinedEmitted = true; });

    client.connectToServer(QHostAddress::LocalHost, 1234);
    for (int i = 0; i < 120; ++i)
        qApp->processEvents(QEventLoop::AllEvents, 40);

    client.createRoom("alice", "r1", 60);
    for (int i = 0; i < 200; ++i) {
        qApp->processEvents(QEventLoop::AllEvents, 10);
        if (joinedEmitted) break;
    }
    REQUIRE(joinedEmitted);

    client.leaveRoom();
    for (int i = 0; i < 50; ++i) qApp->processEvents(QEventLoop::AllEvents, 10);
}

TEST_CASE("Client MessageReadyRead – minimal server sends join_room", "[seminar][integration]") {
    QTcpServer miniServer;
    REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
    const quint16 port = miniServer.serverPort();
    QObject::connect(&miniServer, &QTcpServer::newConnection, [&miniServer]() {
        QTcpSocket* s = miniServer.nextPendingConnection();
        QJsonObject obj;
        obj["type"] = QStringLiteral("join_room");
        obj["room_name"] = QStringLiteral("r1");
        s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
        s->flush();
    });

    Client client("testuser");
    bool joinedEmitted = false;
    QObject::connect(&client, &Client::joinedRoom, [&joinedEmitted](bool) { joinedEmitted = true; });
    client.connectToServer(QHostAddress::LocalHost, port);
    for (int i = 0; i < 150; ++i) {
        qApp->processEvents(QEventLoop::AllEvents, 40);
        if (joinedEmitted) break;
    }
    REQUIRE(joinedEmitted);
}

TEST_CASE("Client jsonReceived – all message types via minimal server", "[seminar][integration]") {
    SECTION("TEXT_MESSAGE – messageReceived") {
        QJsonObject obj;
        obj["type"] = QStringLiteral("text_message");
        obj["content"] = QStringLiteral("hello");
        obj["sender"] = QStringLiteral("bob");
        QString receivedSender, receivedText;
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        QObject::connect(&client, &Client::messageReceived, [&](QString s, QString t) { receivedSender = s; receivedText = t; });
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (!receivedSender.isEmpty()) break;
        }
        REQUIRE(receivedSender == QStringLiteral("bob"));
        REQUIRE(receivedText == QStringLiteral("hello"));
    }

    SECTION("USER_JOINED – userJoined") {
        QJsonObject obj;
        obj["type"] = QStringLiteral("user_joined");
        obj["username"] = QStringLiteral("alice");
        QString received;
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        QObject::connect(&client, &Client::userJoined, [&](QString u) { received = u; });
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (!received.isEmpty()) break;
        }
        REQUIRE(received == QStringLiteral("alice"));
    }

    SECTION("USER_LEFT – userLeft") {
        QJsonObject obj;
        obj["type"] = QStringLiteral("user_left");
        obj["username"] = QStringLiteral("bob");
        QString received;
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        QObject::connect(&client, &Client::userLeft, [&](QString u) { received = u; });
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (!received.isEmpty()) break;
        }
        REQUIRE(received == QStringLiteral("bob"));
    }

    SECTION("GET_ROOMS – roomList") {
        QJsonObject obj;
        obj["type"] = QStringLiteral("get_rooms");
        obj["content"] = QStringLiteral("r1,r2");
        const QVector<QString>* received = nullptr;
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        QObject::connect(&client, &Client::roomList, [&](const QVector<QString>* list) { received = list; });
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (received != nullptr) break;
        }
        REQUIRE(received != nullptr);
        REQUIRE(received->size() >= 2);
        REQUIRE((*received)[0] == QStringLiteral("r1"));
        REQUIRE((*received)[1] == QStringLiteral("r2"));
        delete received;
    }

    SECTION("NEW_HOST – youAreNewHost") {
        QJsonObject obj;
        obj["type"] = QStringLiteral("new_host");
        bool emitted = false;
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        QObject::connect(&client, &Client::youAreNewHost, [&]() { emitted = true; });
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (emitted) break;
        }
        REQUIRE(emitted);
    }

    SECTION("GAME_OVER – gameOver") {
        QJsonObject obj;
        obj["type"] = QStringLiteral("game_over");
        bool emitted = false;
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        QObject::connect(&client, &Client::gameOver, [&]() { emitted = true; });
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (emitted) break;
        }
        REQUIRE(emitted);
    }

    SECTION("GAME_START – startGame") {
        QJsonObject obj;
        obj["type"] = QStringLiteral("start");
        bool emitted = false;
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        QObject::connect(&client, &Client::startGame, [&]() { emitted = true; });
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (emitted) break;
        }
        REQUIRE(emitted);
    }

    SECTION("GAME_START with shouldBecomeHost – imHost and shouldBecomeHost branch") {
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            QJsonObject o1;
            o1["type"] = QStringLiteral("new_host");
            QJsonObject o2;
            o2["type"] = QStringLiteral("start");
            s->write(QJsonDocument(o1).toJson(QJsonDocument::Compact));
            s->write(QJsonDocument(o2).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        bool startEmitted = false;
        QObject::connect(&client, &Client::startGame, [&]() { startEmitted = true; });
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (startEmitted) break;
        }
        REQUIRE(startEmitted);
        REQUIRE(client.imHost == true);
        REQUIRE(client.shouldBecomeHost == false);
    }

    SECTION("CANVAS_MESSAGE – canvasReceived") {
        QJsonObject obj;
        obj["type"] = QStringLiteral("canvas_message");
        obj["content"] = QStringLiteral("canvasdata");
        QString received;
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        QObject::connect(&client, &Client::canvasReceived, [&](QString c) { received = c; });
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) {
            qApp->processEvents(QEventLoop::AllEvents, 40);
            if (!received.isEmpty()) break;
        }
        REQUIRE(received == QStringLiteral("canvasdata"));
    }

    SECTION("ERROR – unknown type (no crash)") {
        QJsonObject obj;
        obj["type"] = QStringLiteral("unknown_type");
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            s->flush();
        });
        Client client("testuser");
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) qApp->processEvents(QEventLoop::AllEvents, 40);
        REQUIRE(true);
    }

    SECTION("MessageReadyRead – invalid JSON triggers PARSING JSON ERR (std::cerr)") {
        QTcpServer miniServer;
        REQUIRE(miniServer.listen(QHostAddress::LocalHost, 0));
        QObject::connect(&miniServer, &QTcpServer::newConnection, [&]() {
            QTcpSocket* s = miniServer.nextPendingConnection();
            s->write("{invalid}");
            s->flush();
        });
        Client client("testuser");
        client.connectToServer(QHostAddress::LocalHost, miniServer.serverPort());
        for (int i = 0; i < 200; ++i) qApp->processEvents(QEventLoop::AllEvents, 40);
        REQUIRE(true);
    }
}
