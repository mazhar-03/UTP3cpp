cmake_minimum_required(VERSION 3.27)
project(utp3_3)

set(CMAKE_CXX_STANDARD 20)

add_library(utp3_3 SHARED library.cpp)

target_link_options(utp3_3 PRIVATE "-static")

target_include_directories(utp3_3 PRIVATE "C:\\Program Files\\Java\\jdk-22\\include")
target_include_directories(utp3_3 PRIVATE "C:\\Program Files\\Java\\jdk-22\\include\\win32")