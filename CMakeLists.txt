cmake_minimum_required (VERSION 2.6)

project (HelloWorld)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

set(SRC_FILES	
src/main.c
src/bar.c
src/bar.h
src/foo.c
src/foo.h
)

add_executable(helloWorld ${SRC_FILES})

#add_librairy(stdio.h)
