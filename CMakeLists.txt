#indique quel minimum de version a prendre pour realiser l executable
cmake_minimum_required(VERSION 2.8)

#nom projet
project(undead_text)


#initialisation variable -> parametre de compilation
set(CMAKE_C_FLAGS "-std=c99 -g -Wall -Werror")


#ajout de la librairie
add_library(libgame game.o game_io.o)


#creation de l executable nom + fichiers dependants
add_executable(undead_text undead_text.c)


#lien entre executable et la bibliotheque
target_link_libraries(undead_text libgame)


#activation des tests
enable_testing()


#ajout des tests
add_test(test test.c)


#permet de lancer la commande ctest -> realise les tests
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})


#definit le succes du test : le test reussi si test affiche "INFO:  All tests successsfull"
set_tests_properties (test
	PROPERTIES PASS_REGULAR_EXPRESSION "INFO:  All tests successsfull")

