valgrind --tool=memcheck --log-file=log0.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test0
VAL="$?"
valgrind --tool=memcheck --log-file=log1.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test1
VAL="${VAL} $?"
valgrind --tool=memcheck --log-file=log2.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test2
VAL="${VAL} $?"
valgrind --tool=memcheck --log-file=log3.txt --leak-check=full --show-reachable=yes --error-exitcode=2 ./test3
VAL="${VAL} $?"


i="0"

for VAL in $VAL
do
	i=$((i+1))

    if [ $VAL -eq 0 ];then
       printf "\n 	Test number $i :\n"
       printf "	No memory leak nor error with code test !\n"
    elif [ $VAL -eq 1 ];then
       printf "\n 	Test number $i :\n"
       printf "	No memory leak but code test failure !\n"
    else
       printf "\n 	Test number $i :\n"
       printf "	Memory leak on this program\n"
    fi
done
printf "\n"