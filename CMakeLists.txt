cmake_minimum_required(VERSION 3.8)
project(computer_graphics)

set(CG_SOURCE ${CMAKE_SOURCE_DIR}/cg-sources)
set(PROJ_INCLUDES ${CMAKE_SOURCE_DIR}/include/win)
set(SDL2_INCLUDE ${CMAKE_SOURCE_DIR}/include/win/SDL2)
set(MY_INCLUDES ${CMAKE_SOURCE_DIR}/Mycode/include)
set(MY_SOURCE ${CMAKE_SOURCE_DIR}/Mycode/src)
set(LIBRARIES ${CMAKE_SOURCE_DIR}/lib)

set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(${MY_SOURCE})

