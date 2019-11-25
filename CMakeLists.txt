cmake_minimum_required(VERSION 3.15)
project(ass1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ass1 src/main.cpp src/Session.cpp include/Session.h include/Action.h include/Watchable.h include/User.h include/json.hpp src/Watchable.cpp src/User.cpp)