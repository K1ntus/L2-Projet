#in#indique quel minimum de version a prendre pour realiser l executable
cmake_minimum_required(VERSION 2.8)

###########################################################################
# Options
###########################################################################


#nom projet
project(undead_game_text)

include(CTest)

# pkg-config --list-all  | grep -i sdl2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMG REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
set(SDL2_ALL_LIBS ${SDL2_LIBRARIES} ${SDL2_IMG_LIBRARIES} ${SDL2_TTF_LIBRARIES})
set(SDL2_ALL_INC ${SDL2_INCLUDE_DIRS} ${SDL2_IMG_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

include_directories(./header)



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


option(ENABLE_DEBUG "debug options" ON)


#activation des tests
enable_testing()

#Mode debug

if(ENABLE_DEBUG)
	set(CMAKE_C_FLAGS "-std=c99 -g -fprofile-arcs -ftest-coverage -Wall")
	set(CMAKE_LD_FLAGS "-fprofile-arcs -ftest-coverage")
else()
	set(CMAKE_C_FLAGS "-std=c99 -03 -Wall -Werror")
endif()

#initialisation variable -> parametre de compilation


###########################################################################
# Executable + lib
###########################################################################


#ajout de la librairie et indique qu on utilise des fichiers .o
option(LIBGAME_TEACHER "teacher version of libgame" ON)
if(LIBGAME_TEACHER)
	add_library(game src/teacher/game.o src/teacher/game_io.o src/game_display.c src/game_util.c src/game_solver_lib.c src/game_io_util.c src/game_generation.c)
else()
	add_library(game src/game.c src/game_io.c src/game_display.c src/game_util.c src/game_solver_lib.c src/game_io_util.c)
endif()
SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE C)



#creation de l executable nom + fichiers dependants
add_executable(undead_text src/undead_text.c)
add_executable(undead_solve src/undead_solve.c)

#lien entre executable et la bibliotheque
target_link_libraries(undead_text game)
target_link_libraries(undead_solve game)




include_directories(${SDL2_ALL_INC})
add_executable(undead_sdl src/main_sdl.c src/undead_sdl_jojo.c)
target_link_libraries(undead_sdl ${SDL2_ALL_LIBS} m)
target_link_libraries(undead_sdl game)


###########################################################################
# Tests
###########################################################################


#creation executable test
add_executable(test_exec src/test.c)
target_link_libraries(test_exec game)
#add_test(test_output test_exec COMMAND valgrind --tool=memcheck --log-file=log.txt --leak-check=full --show-reachable=yes --error-exitcode=2  $<TARGET_FILE:test_exec>)
add_test(test_output0 test_exec COMMAND gcov  $<TARGET_FILE:test_exec>)
add_test(test_output1 undead_text COMMAND gcov  $<TARGET_FILE:undead_text>)
add_test(test_output2 undead_solve COMMAND gcov  $<TARGET_FILE:undead_solve>)



#ajout des test memoire avec valgrind depuis le fichier script
#add_custom_target(memory_test COMMAND ${CMAKE_CTEST_COMMAND} script.sh)

#add_test(NAME test_output COMMAND valgrind --tool=memcheck --log-file=log.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test0)
