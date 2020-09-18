# cmake/third_party_import.cmake
include(FetchContent)

# install google test
message(STATUS "Start Install GoogleTest")
find_package(GTest CONFIG REQUIRED)
if (NOT GTest_FOUND)
    message(gtest_include_dir=${GTEST_INCLUDE_DIR})
    message(gtest_library=${GTEST_LIBRARY})
    include_directories(${GTEST_INCLUDE_DIRS})
endif ()

## install google log
#message(STATUS "Start Install unwind")
#FetchContent_Declare(
#        unwind
#        GIT_REPOSITORY "https://github.com/fwilliams/unwind"
#        GIT_TAG        master
#)
#
#FetchContent_GetProperties(unwind)
#if (NOT unwind_POPULATED)
#    FetchContent_Populate(unwind)
#    message(STATUS "unwind Source Dir -> ${unwind_SOURCE_DIR}")
#    message(STATUS "unwind Binary Dir -> ${unwind_BINARY_DIR}")
#    add_subdirectory(${unwind_SOURCE_DIR} ${unwind_BINARY_DIR})
#endif ()
#
#
#
## install google log
#message(STATUS "Start Install Glog")
#FetchContent_Declare(
#        glog
#        GIT_REPOSITORY "https://github.com/google/glog"
#        GIT_TAG        master
#)
#
#FetchContent_GetProperties(glog)
#if (NOT glog_POPULATED)
#    FetchContent_Populate(glog)
#    message(STATUS "glog Source Dir -> ${glog_SOURCE_DIR}")
#    message(STATUS "glog Binary Dir -> ${glog_BINARY_DIR}")
#    add_subdirectory(${glog_SOURCE_DIR} ${glog_BINARY_DIR})
#endif ()