cmake_minimum_required(VERSION 4.4)

project(Desxercise VERSION 1.0 LANGUAGES CXX)

find_package(SQLite3 REQUIRED)

add_executable(Desxercise src/main.cpp)

target_link_libraries(Desxercise PRIVATE SQLite3::SQLite3)

