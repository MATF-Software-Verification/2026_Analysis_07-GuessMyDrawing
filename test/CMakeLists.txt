# Seminar testovi: test/ + unit/ + integration/ + skripte
cmake_minimum_required(VERSION 3.14)
project(seminar_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../07-GuessMyDrawing-master/07-GuessMyDrawing")
set(APP_DIR "${PROJECT_SOURCE_DIR}/Application")
set(SERVER_DIR "${PROJECT_SOURCE_DIR}/Server")

find_package(Qt5 5.7 COMPONENTS Core Gui Widgets Network REQUIRED)

find_package(Catch2 3 QUIET)
if(NOT Catch2_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
  )
  FetchContent_MakeAvailable(Catch2)
endif()

# Izvori potrebni za testove. Ne uključujemo ceo Application GUI (mainwindow, game, ...)
# jer u jednom targetu dolazi do sukoba MOC imena (npr. MainWindow u aplikaciji i serveru).
add_executable(seminar_tests
  test_main.cpp
  unit/room_test.cpp
  unit/client_test.cpp
  unit/server_test.cpp
  unit/thread_test.cpp
  integration/client_integration_test.cpp
  integration/server_integration_test.cpp
  ${APP_DIR}/client.cpp
  ${APP_DIR}/messageparser.cpp
  ${SERVER_DIR}/server.cpp
  ${SERVER_DIR}/thread.cpp
  ${SERVER_DIR}/room.cpp
  ${SERVER_DIR}/servermainwindow.cpp
  ${SERVER_DIR}/servermessageparser.cpp
  ${SERVER_DIR}/servermainwindow.ui
)

target_include_directories(seminar_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/unit
  ${CMAKE_CURRENT_SOURCE_DIR}/integration
  ${APP_DIR}
  ${SERVER_DIR}
  ${PROJECT_SOURCE_DIR}
)

target_link_libraries(seminar_tests PRIVATE
  Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network
  Catch2::Catch2
)

set_target_properties(seminar_tests PROPERTIES
  AUTOMOC ON
  AUTOUIC ON
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
)

# Opciono: pokrivenost koda (gcov). cmake -DCOVERAGE=ON ..
if(COVERAGE)
  target_compile_options(seminar_tests PRIVATE --coverage)
  target_link_options(seminar_tests PRIVATE --coverage)
endif()

# Uključuje ga vs/CMakeLists.txt (add_subdirectory(test))
