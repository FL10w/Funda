cmake_minimum_required(VERSION 3.10)
project(task4)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=maybe-uninitialized")

add_library(${CMAKE_PROJECT_NAME}_lib func.c)
target_link_libraries(${CMAKE_PROJECT_NAME}_lib PUBLIC m) 

add_executable(${CMAKE_PROJECT_NAME}_exe main.c)
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib m)
