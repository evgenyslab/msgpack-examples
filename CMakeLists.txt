cmake_minimum_required(VERSION 3.15)
project(msgpakc-examples)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${PROJECT_SOURCE_DIR}
  )

add_executable(read_write_io src/read_write_io.cpp)
add_executable(classPacker src/classPacker.cpp)
