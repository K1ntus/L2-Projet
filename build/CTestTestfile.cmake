# CMake generated Testfile for 
# Source directory: /autofs/netapp/travail/jmasson/Année/L2/Semestre 4/workspace/Undead-V2
# Build directory: /autofs/netapp/travail/jmasson/Année/L2/Semestre 4/workspace/Undead-V2/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_output "test_exec" "COMMAND" "valgrind" "--tool=memcheck" "--log-file=log.txt" "--leak-check=full" "--show-reachable=yes" "--error-exitcode=2" "$<TARGET_FILE:test_exec>")
