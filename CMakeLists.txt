cmake_minimum_required(VERSION 3.23)
project(mygame C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(mygame
        include/character.h
        include/game.h
        include/input.h
        include/render.h
        include/utils.h
        src/character.c
        src/game.c
        src/input.c
        src/main.c
        src/render.c
        src/utils.c)
