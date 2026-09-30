cmake_minimum_required(VERSION 4.4)

project(Desxercise VERSION 1.0 LANGUAGES CXX)

find_package(SQLite3 REQUIRED)

add_executable(Desxercise src/main.cpp
    src/database/Database.cpp
    src/models/Date.cpp
    src/models/Time.cpp
    src/models/Training.cpp
    src/models/Status.hpp
    src/utils/Converters.hpp
)

target_include_directories(Desxercise PRIVATE
    src/database
    src/models
    src/utils
)

target_link_libraries(Desxercise PRIVATE SQLite3::SQLite3)

#testing

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(DatabaseIntegrationTest
    tests/DatabaseIntegrationTest.cpp
    src/database/Database.cpp
    src/models/Date.cpp
    src/models/Time.cpp
    src/models/Training.cpp
    src/models/Status.hpp
    src/utils/Converters.hpp
)

target_include_directories(DatabaseIntegrationTest PRIVATE
    src/database
    src/models
    src/utils
)

target_link_libraries(DatabaseIntegrationTest PRIVATE
    SQLite3::SQLite3
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(DatabaseIntegrationTest)
