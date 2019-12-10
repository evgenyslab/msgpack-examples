cmake_minimum_required(VERSION 3.15)
project(msgpakc-examples)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${PROJECT_SOURCE_DIR}
  )

add_executable(example_01 src/example_01.cpp)
