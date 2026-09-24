cmake_minimum_required(VERSION 4.4)

project(Desxercise VERSION 1.0 LANGUAGES CXX)

find_package(SQLite3 REQUIRED)

add_executable(Desxercise src/main.cpp
    src/database/Database.cpp
    src/models/Date.cpp
    src/models/Time.cpp
    src/models/Training.cpp
    src/models/Status.hpp
)

target_include_directories(Desxercise PRIVATE
    src/database
    src/models
)

target_link_libraries(Desxercise PRIVATE SQLite3::SQLite3)

