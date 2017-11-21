#indique quel minimum de version a prendre pour realiser l executable
cmake_minimum_required(VERSION 2.8)

#nom projet
project(undead_game_text)

#activation des tests
enable_testing()

#initialisation variable -> parametre de compilation
set(CMAKE_C_FLAGS "-std=c99 -g -Wall -Werror")


#ajout de la librairie et indique qu on utilise des fichiers .o
add_library(libgame game.o game_io.o)
SET_TARGET_PROPERTIES(libgame PROPERTIES LINKER_LANGUAGE C)

#creation de l executable nom + fichiers dependants
add_executable(undead_text undead_text.c)


#lien entre executable et la bibliotheque
target_link_libraries(undead_text libgame)


#creation executable test
add_executable(test test.c)


#lien entre executable test et librairie
target_link_libraries(test libgame)



#ajout des test memoire avec valgrind depuis le fichier script
#add_custom_target(memory_test COMMAND ${CMAKE_CTEST_COMMAND} script.sh)


add_test(NAME test0 COMMAND valgrind --tool=memcheck --log-file=log.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test0)

add_test(NAME test1 COMMAND  valgrind --tool=memcheck --log-file=log.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test)
