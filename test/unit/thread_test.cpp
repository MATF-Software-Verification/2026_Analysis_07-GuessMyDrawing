// Seminar tests – Thread (jedinični). Tag: [seminar][unit]
#include <catch2/catch_test_macros.hpp>
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/Server/thread.h"

TEST_CASE("Thread getSocketDescriptor returns ID", "[seminar][unit]") {
    Thread thread(qintptr(42));
    REQUIRE(thread.getSocketDescriptor() == quintptr(42));
}

TEST_CASE("Thread disconnect can be called", "[seminar][unit]") {
    Thread thread(qintptr(1001));
    REQUIRE_NOTHROW(thread.disconnect());
}

TEST_CASE("Thread onDisconnectedMessage can be called", "[seminar][unit]") {
    Thread thread(qintptr(1001));
    REQUIRE_NOTHROW(thread.onDisconnectedMessage());
}
