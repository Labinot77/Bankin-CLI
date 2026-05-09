cmake_minimum_required(VERSION 3.15)

project(BankingSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE
    src
)

target_link_libraries(main PRIVATE SQLite::SQLite3)