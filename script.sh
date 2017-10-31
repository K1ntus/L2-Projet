#!/bin/sh
# A simple script with a function...

#COMPILATION
i="0"
count=`ls -d *game*.o* | wc -l`
count=$((count-1))
#game_io.o
for j in `seq 1 $((count-1))`;
do
  printf "Compilation file $j\n"
  gcc -Wall -std=c99 -g -o test$j test.o game$j.o 
  count=$((count-1))
done

printf "\033[31m
  ::::::::::::::::::::::::::::::::::::::::::::
  :'########:'##::::'##::'#######:::##::::'##:
  :... ##..:: ###::'###:'##:::::##::##:::::##:
  :::: ##:::: ####'####: ##::::..:::##:::::##:
  :::: ##:::: ## ### ##: ########:::#########:
  :::: ##:::: ##. #: ##: ##:::::##::##:::::##:
  :::: ##:::: ##:.:: ##: ##:::::##::##:::::##:
  :::: ##:::: ##:::: ##:. #######:::##:::::##:
  ::::..:::::..:::::..:::.......:::..:::::..::
\033[0m\n"


#Lancement des tests
i="0"
count=`ls -d *test* | wc -l`
count=$((count-2))

valgrind --tool=memcheck --log-file=log$j.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test0
VAL="$?"
for j in `seq 1 $((count-1))`;
do
  printf "\033[31mTest number $j :\033[0m\n"
  valgrind --tool=memcheck --log-file=log$j.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test$j
  VAL="${VAL} $?"
  count=$((count-1))
done

printf "Recap :"
for VAL in $VAL
do
  i=$((i+1))
    if [ $VAL -eq 0 ];then
      printf "\n   Test number $i :\n"
      printf " \033[32mNo memory leak nor error with code test !\033[0m\n"
    elif [ $VAL -eq 1 ];then
         printf "\n   Test number $i :\n"
         printf "\033[31m No memory leak but code test failure !\033[0m\n"
    else
         printf "\n   Test number $i :\n"
         printf " \033[31;1;4;5mMemory leak on this program\033[0m\n"
    fi
done
printf "\n\n"
