// Seminar tests – Server (jedinični). Tag: [seminar][unit]
#include <catch2/catch_test_macros.hpp>
#define private public
#define protected public
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/Server/server.h"
#undef private
#undef protected

TEST_CASE("Server startServer", "[seminar][unit]") {
    SECTION("when port is free – server is listening") {
        Server server;
        server.startServer();
        REQUIRE(server.isListening());
    }
    SECTION("when port is busy – second server cannot listen") {
        Server server1;
        server1.startServer();
        REQUIRE(server1.isListening());
        Server server2;
        server2.startServer();
        REQUIRE(!server2.isListening());
    }
}
