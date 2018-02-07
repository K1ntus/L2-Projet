#in#indique quel minimum de version a prendre pour realiser l executable
cmake_minimum_required(VERSION 2.8)

###########################################################################
# Options
###########################################################################


#nom projet
project(undead_game_text)

include(CTest)

option(BUILD_QTAPPS "Build Qt based application." OFF)
option(BUILD_OPTIMIZED_DEBUG "Set optimization level -O1 or -Og for debug build" OFF)
option(BUILD_COVERAGE_REPORT "Build code coverage report" OFF)
option(BUILD_WITH_OPENMP "Build with OpenMP support" OFF)
option(BUILD_DEBIAN "Build debian .deb packages" OFF)
option(BUILD_GSL "Build GSL external dependency" OFF)
option(NSX_BUILD_STATIC "Link nsxlib statically" OFF)
option(NSX_VALGRIND "Run tests with valgrind" ON)
option(NSX_SANITIZE "Compile with clang's -fsanitize (must also set NSX_SANITIZER variable)" OFF)
option(NSX_TIDY "Add clang-tidy custom target" OFF)

#activation des tests
enable_testing()

#Mode debug
option(ENABLE_DEBUG ON)

#initialisation variable -> parametre de compilation
set(CMAKE_C_FLAGS "-std=c99 -g -Wall -Werror")


###########################################################################
# Executable + lib
###########################################################################


#ajout de la librairie et indique qu on utilise des fichiers .o
add_library(game game.c game_io.o)
SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE C)

#creation de l executable nom + fichiers dependants
add_executable(undead_text undead_text.c)


#lien entre executable et la bibliotheque
target_link_libraries(undead_text game)


###########################################################################
# Tests
###########################################################################


#creation executable test
add_executable(test_exec solver.c)
target_link_libraries(test_exec game)
add_test(test_output test_exec COMMAND valgrind --tool=memcheck --log-file=log.txt --leak-check=full --show-reachable=yes --error-exitcode=2  $<TARGET_FILE:test_exec>)



#ajout des test memoire avec valgrind depuis le fichier script
#add_custom_target(memory_test COMMAND ${CMAKE_CTEST_COMMAND} script.sh)

#add_test(NAME test_output COMMAND valgrind --tool=memcheck --log-file=log.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test0)
