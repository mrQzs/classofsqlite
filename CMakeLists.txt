cmake_minimum_required(VERSION 3.20)
project(sqlite3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(sqlite3 main.cpp SqliteOperator.cpp SqliteOperator.h sqlite3.h sqlite3.c)
target_link_libraries(sqlite3
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        -lz
        -lm
        -ldl
        -lpthread
        )

