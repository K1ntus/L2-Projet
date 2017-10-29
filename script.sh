printf "\033[31m
:::::::::::::::::::::::::::::::::::::::::::
'########:'##::::'##::'#######:::##::::'##:
... ##..:: ###::'###:'##:::::##::##:::::##:
::: ##:::: ####'####: ##::::..:::##:::::##:
::: ##:::: ## ### ##: ########:::#########:
::: ##:::: ##. #: ##: ##:::::##::##:::::##:
::: ##:::: ##:.:: ##: ##:::::##::##:::::##:
::: ##:::: ##:::: ##:. #######:::##:::::##:
:::..:::::..:::::..:::.......:::..:::::..::
   \033[0m\n"

i="0"
valgrind --tool=memcheck --log-file=log0.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test0
VAL="$?"
valgrind --tool=memcheck --log-file=log1.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test1
VAL="${VAL} $?"
valgrind --tool=memcheck --log-file=log2.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test2
VAL="${VAL} $?"
valgrind --tool=memcheck --log-file=log3.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test3
VAL="${VAL} $?"



printf "Recap :"
for VAL in $VAL
do
	i=$((i+1))

    if [ $VAL -eq 0 ];then
       printf "\n 	Test number $i :\n"
       printf "	\033[32mNo memory leak nor error with code test !\033[0m\n"
    elif [ $VAL -eq 1 ];then
       printf "\n 	Test number $i :\n"
       printf "\033[31m	No memory leak but code test failure !\033[0m\n"
    else
       printf "\n 	Test number $i :\n"
       printf "\033[31;1;4;5m	Memory leak on this program\033[0m\n"
    fi
done
printf "\n\n"