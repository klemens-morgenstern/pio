cmake_minimum_required(VERSION 3.23)
project(te_asio)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
find_package(Boost REQUIRED system container)

add_subdirectory(test)