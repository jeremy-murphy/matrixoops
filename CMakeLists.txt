cmake_minimum_required(VERSION 3.0)

project(matrixoops)

add_executable(matrixoops main.cpp)

install(TARGETS matrixoops RUNTIME DESTINATION bin)
