cmake_minimum_required(VERSION 3.10)
project(lab4)

set(CMAKE_C_STANDARD 11)

add_library(first SHARED first.c)
add_library(second SHARED second.c)

target_link_libraries(first m)
target_link_libraries(second m)

add_executable(test_dynamic test_dynamic.c)
target_link_libraries(test_dynamic dl)

add_executable(test_static test_static.c first.c)
target_link_libraries(test_static m) 

install(TARGETS first second test_dynamic DESTINATION bin)
