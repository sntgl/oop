set(CMAKE_PREFIX_PATH "//Users//sntgl//Qt//6.1.0//clang_64//lib//cmake")

cmake_minimum_required(VERSION 3.1.0)

project(lab_04 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOUIC OFF)
#set(UI ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt6 COMPONENTS Widgets REQUIRED)

cmake_minimum_required(VERSION 3.19)
project(lab_04)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_04
        Button.cpp
        Button.h
        Controller.cpp
        Controller.h
        Door.cpp
        Door.h
        Lift.cpp
        Lift.h
        Cabin.cpp
        Cabin.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        direction_t.h)

target_link_libraries(lab_04 Qt6::Widgets)