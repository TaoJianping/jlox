# cmake/third_party_import.cmake
include(FetchContent)

# install google test
message(STATUS "Start Install GoogleTest")
FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest"
        GIT_TAG        master
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    message(STATUS "GoogleTest Source Dir -> ${googletest_SOURCE_DIR}")
    message(STATUS "GoogleTest Binary Dir -> ${googletest_BINARY_DIR}")
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()