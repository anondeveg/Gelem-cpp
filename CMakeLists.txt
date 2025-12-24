
cmake_minimum_required(VERSION 3.10)
project(tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Main   "main.cpp")

if(MSVC)
    target_compile_options(Main PRIVATE /W4)
else()
    target_compile_options(Main PRIVATE -Wall -Wextra)
endif()

