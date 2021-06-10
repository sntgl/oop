set(CMAKE_PREFIX_PATH "//Users//sntgl//Qt//6.1.0//clang_64//lib//cmake")

cmake_minimum_required(VERSION 3.1.0)

project(lab_01 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(lab_01
        frontend/main.cpp
        backend/backend.cpp
        frontend/error_handler.cpp
        frontend/plot_widget.cpp
        frontend/window.cpp
        backend/with_file.cpp
        backend/with_matrix.cpp
        backend/with_memory.cpp
        backend/with_points.cpp
        backend/with_projection.cpp
        backend/types.cpp
        )

target_link_libraries(lab_01 Qt6::Widgets)