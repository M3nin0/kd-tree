cmake_minimum_required(VERSION 2.8.12)
     
project(exe10)
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++14" CACHE STRING "compile flags" FORCE)
 
file(GLOB SRC_FILES "*.cpp")
file(GLOB HDR_FILES "*.hpp")

add_executable(exe10 ${SRC_FILES} ${HDR_FILES})
