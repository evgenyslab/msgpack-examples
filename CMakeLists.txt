cmake_minimum_required(VERSION 3.15)
project(msgpakc-examples)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}
  )

add_executable(read_write_io src/read_write_io.cpp include/header.h)
add_executable(classPacker src/classPacker.cpp include/header.h)
add_executable(sbuffer_to_fbuffer src/sbuffer_to_fbuffer.cpp include/header.h)
