// Seminar tests – Client (jedinični). Tag: [seminar][unit]
#include <catch2/catch_test_macros.hpp>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QApplication>
#include <QString>
#define private public
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/Application/client.h"
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/MessageType.h"
#undef private

TEST_CASE("Client connectToServer sets address and port", "[seminar][unit]") {
    Client client("testuser");
    QHostAddress addr = QHostAddress::LocalHost;
    quint16 port = 54321u;
    client.connectToServer(addr, port);
    REQUIRE(client.adress == addr);
    REQUIRE(client.port == port);
}

TEST_CASE("Client disconnectFromHost keeps address/port", "[seminar][unit]") {
    Client client("testuser");
    client.connectToServer(QHostAddress::LocalHost, 54321u);
    QHostAddress beforeAddr = client.adress;
    quint16 beforePort = client.port;
    client.disconnectFromHost();
    REQUIRE(client.adress == beforeAddr);
    REQUIRE(client.port == beforePort);
}

TEST_CASE("Client send", "[seminar][unit]") {
    SECTION("send does not change username and keeps parser") {
        Client client("testuser");
        REQUIRE(client.parser != nullptr);
        REQUIRE(client.mName == QString("testuser"));
        client.send("hello");
        REQUIRE(client.mName == QString("testuser"));
        REQUIRE(client.parser != nullptr);
    }
    SECTION("send does not change address/port") {
        Client client("testuser");
        client.connectToServer(QHostAddress::LocalHost, 5000u);
        client.send("hello");
        REQUIRE(client.adress == QHostAddress::LocalHost);
        REQUIRE(client.port == 5000u);
    }
}

TEST_CASE("Client createRoom sets mName to username", "[seminar][unit]") {
    Client client("initial");
    REQUIRE(client.mName == QString("initial"));
    client.createRoom("username", "MyRoom", 60);
    REQUIRE(client.mName == QString("username"));
}

TEST_CASE("Client chooseWord and getRooms can be called", "[seminar][unit]") {
    Client client("testuser");
    REQUIRE_NOTHROW(client.chooseWord("hat"));
    REQUIRE_NOTHROW(client.getRooms());
}

TEST_CASE("Client sendCanvas can be called", "[seminar][unit]") {
    Client client("testuser");
    QString canvasData("canvas");
    REQUIRE_NOTHROW(client.sendCanvas(canvasData));
}

TEST_CASE("Client reconnect calls", "[seminar][unit]") {
    Client client("testuser");
    client.connectToServer(QHostAddress::LocalHost, 54321u);
    QHostAddress beforeAddr = client.adress;
    quint16 beforePort = client.port;
    client.reconnect();
    REQUIRE(client.adress == beforeAddr);
    REQUIRE(client.port == beforePort);
}

TEST_CASE("Client connectedMessage and disconnectedMessage can be called", "[seminar][unit]") {
    Client client("testuser");
    REQUIRE_NOTHROW(client.connectedMessage());
    REQUIRE_NOTHROW(client.disconnectedMessage());
}

TEST_CASE("Client error emits errorConnecting", "[seminar][unit]") {
    Client client("testuser");
    bool emitted = false;
    QObject::connect(&client, &Client::errorConnecting, [&]() { emitted = true; });
    client.error(QAbstractSocket::UnknownSocketError);
    REQUIRE(emitted);
}
