valgrind --log-file=log0.txt --leak-check=full --error-exitcode=2 ./test0
valgrind --log-file=log1.txt --leak-check=full --error-exitcode=2 ./test1
valgrind --log-file=log2.txt --leak-check=full --error-exitcode=2 ./test2
valgrind --log-file=log3.txt --leak-check=full --error-exitcode=2 ./test3
echo "TEST OK"