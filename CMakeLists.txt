cmake_minimum_required(VERSION 3.20)

project(mini_db VERSION 0.1.0 LANGUAGES CXX)

cmake_policy(SET CMP0167 OLD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED)

add_executable(mini_db
    src/main.cpp
)

target_include_directories(mini_db
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIRS}
)

if(MSVC)
    target_compile_options(mini_db PRIVATE /W4 /permissive-)
else()
    target_compile_options(mini_db PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
    )
endif()
