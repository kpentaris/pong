cmake_minimum_required(VERSION 3.9)
project(Pong C)
SET(CMAKE_C_STANDARD 11)

SET(SDL2 e:/C_Projects/Libraries/SDL2/x86_64-w64-mingw32)
SET(SDL2_INCLUDE_DIR ${SDL2}/include/SDL2)
SET(SDL2_LIBS ${SDL2}/lib)

SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
FIND_LIBRARY(SDL2MAIN_LIBRARY
        NAMES SDL2main
        HINTS ${SDL2_LIBS})
FIND_LIBRARY(SDL2CORE_LIBRARY
        NAMES SDL2
        HINTS ${SDL2_LIBS})
message(${SDL2CORE_LIBRARY})
SET(COMPILE_LIBRARIES ${MINGW32_LIBRARY} ${SDL2MAIN_LIBRARY} ${SDL2CORE_LIBRARY})

include_directories(${SDL2_INCLUDE_DIR})

add_executable(Pong
        main.c
        main.h
        game/GameLoop.c
        game/GameLoop.h
        game/Input.c
        game/Input.h
        paddle/Paddle.c
        paddle/Paddle.h
        ball/Ball.c
        ball/Ball.h main.h)

target_link_libraries(Pong ${COMPILE_LIBRARIES})