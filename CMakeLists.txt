cmake_minimum_required(VERSION 3.10)
project(cmd_eq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

add_executable(cmd_eq
    src/main.cpp
    src/renderer.cpp
    src/audio.cpp
    src/coordinator.cpp
    
)

target_include_directories(cmd_eq
    PRIVATE
        ${CURSES_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        ${CMAKE_CURRENT_SOURCE_DIR}/src/src

)

target_link_libraries(cmd_eq
    PRIVATE
        ${CURSES_LIBRARIES}
)
