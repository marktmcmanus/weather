cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(weather LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WEATHER_BUILD_TESTS "Build tests" OFF)

add_subdirectory(sources)