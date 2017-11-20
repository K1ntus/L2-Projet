cmake_minimum_required(VERSION 2.8)
project(undead-tm6h)

enable_testing()

#indique a Cmake que compilateur du langage de base est celui du standard C99
add_definitions(-std=c99)

#parametre de compilation
set(CMAKE_C_FLAGS "-g -Wall -Werror")

#creation de la lib
add_library(game game.o game_io.o undead_text.c)
SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE C)

#specifie le nom et fichiers sources Ã  compiler
add_executable(undead_text undead_text.c )

#definit les bibliotheques use par le fichier <exe>
target_link_libraries(undead_text game)