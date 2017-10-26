valgrind --log-file=log0.txt --leak-check=full --error-exitcode=2 ./test1
valgrind --log-file=log0.txt --leak-check=full --error-exitcode=2 ./test2
valgrind --log-file=log0.txt --leak-check=full --error-exitcode=2 ./test3
valgrind --log-file=log0.txt --leak-check=full --error-exitcode=2 ./test0
echo "TEST OK"