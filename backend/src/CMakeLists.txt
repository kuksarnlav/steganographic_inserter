cmake_minimum_required(VERSION 3.23)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
add_executable(Stenographic_Tool_Backend
        ${INCLUDE_DIR}/EasyBMP/EasyBMP.h
        ${INCLUDE_DIR}/EasyBMP/EasyBMP.cpp
        ${INCLUDE_DIR}/MethodLSB.h
        ${INCLUDE_DIR}/MethodKutter.h
        ${INCLUDE_DIR}/MethodZhaoKoch.h
        ${INCLUDE_DIR}/types.h
        main.cpp
        Method.cpp
        MethodLSB.cpp
        MethodKutter.cpp
        MethodZhaoKoch.cpp
)
target_include_directories(Stenographic_Tool_Backend PUBLIC ${INCLUDE_DIR} ${INCLUDE_DIR}/EasyBMP)