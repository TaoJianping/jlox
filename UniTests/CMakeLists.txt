cmake_minimum_required(VERSION 3.14)
project(jloxTests)

include_directories(../Src)

set(
        Headers
        TestBasic.h
)

set(
        Sources
        TestBasic.cpp
)



ADD_EXECUTABLE(DSACPP_Test ${Headers} ${Sources})
target_link_libraries(DSACPP_Test gtest gtest_main)