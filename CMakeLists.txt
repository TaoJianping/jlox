cmake_minimum_required(VERSION 3.14)
SET(CMAKE_TOOLCHAIN_FILE "/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake")


project(JloxPacket)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Src)
add_subdirectory(UniTests)
