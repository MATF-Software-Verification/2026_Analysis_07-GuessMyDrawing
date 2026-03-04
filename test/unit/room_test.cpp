// Seminar tests – Room (jedinični). Tag: [seminar][unit]
#include <catch2/catch_test_macros.hpp>
#define private public
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/Server/room.h"
#include "../../07-GuessMyDrawing-master/07-GuessMyDrawing/Server/thread.h"
#undef private

TEST_CASE("Room setDuration updates duration", "[seminar][unit]") {
    Room room("host", "room1", 60);
    REQUIRE(room.duration == 60);
    room.setDuration(90);
    REQUIRE(room.duration == 90);
}
