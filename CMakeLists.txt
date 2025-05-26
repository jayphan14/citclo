cmake_minimum_required(VERSION 3.14)
project(citclo VERSION 1.0 LANGUAGES CXX)

# 1) Default to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build: Debug/Release" FORCE)
endif()

# 2) C++20 and explicitly set debug/release flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# (Optional) override flags if you want custom ones
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# 3) Gather sources
file(GLOB_RECURSE SRC_FILES   src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h)

# 4) Include headers
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/citclo
    ${CMAKE_SOURCE_DIR}/external/eigen-3.4.0
)

# 5) Main executable
add_executable(citclo ${SRC_FILES})

# 6) Tests
# enable_testing()
# add_executable(tests tests/test_main.cpp)
# add_test(NAME unit_tests COMMAND tests)
