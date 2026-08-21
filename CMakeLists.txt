cmake_minimum_required(VERSION 3.28)

project(Pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 3 COMPONENTS Graphics CONFIG REQUIRED)

add_executable(Pong pong.cpp)

target_link_libraries(Pong PRIVATE SFML::Graphics)
