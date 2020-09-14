cmake_minimum_required(VERSION 3.14)
project(JloxPacket)

set(CMAKE_CXX_STANDARD 17)

include(cmake/third_party_import.cmake)


add_subdirectory(Src)
add_subdirectory(UniTests)
