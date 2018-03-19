# CMake generated Testfile for 
# Source directory: /home/jordan/espaces/Travail/L2/Semestre/Projet/workspace
# Build directory: /home/jordan/espaces/Travail/L2/Semestre/Projet/workspace/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_output "test_exec" "COMMAND" "valgrind" "--tool=memcheck" "--log-file=log.txt" "--leak-check=full" "--show-reachable=yes" "--error-exitcode=2" "$<TARGET_FILE:test_exec>")
