cmake_minimum_required(VERSION 3.14)
SET(CMAKE_TOOLCHAIN_FILE "/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(jloxTests)

# install google test
message(STATUS "Start Install GoogleTest")
find_package(GTest CONFIG REQUIRED)
if (GTest_FOUND)
    message(Fount GTest !)
endif ()

# install google log
message(STATUS "Start Install glog")
find_package(glog CONFIG REQUIRED)
if (glog_FOUND)
    message(Fount glog !)
endif ()


include_directories(../Src)

set(
        Headers
        TestBasic.h
        TestScanner.h
)

set(
        Sources
        TestBasic.cpp
        TestScanner.cpp
)


ADD_EXECUTABLE(DSACPP_Test ${Headers} ${Sources})
target_link_libraries(DSACPP_Test GTest::gtest GTest::gtest_main Scanner)