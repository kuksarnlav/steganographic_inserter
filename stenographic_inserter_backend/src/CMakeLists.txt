cmake_minimum_required(VERSION 3.23)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
add_executable(Stenographic_Tool_Backend
        ${INCLUDE_DIR}/InserterBMP.h
        ${INCLUDE_DIR}/EasyBMP/EasyBMP.h
        ${INCLUDE_DIR}/EasyBMP/EasyBMP.cpp
        InserterBMP.cpp
        main.cpp)
target_include_directories(Stenographic_Tool_Backend PUBLIC ${INCLUDE_DIR} ${INCLUDE_DIR}/EasyBMP)