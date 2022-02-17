echo "failing case test"
gcc -c ../src/runner.c -o ../bin/runner.o
gcc ../src/main.c ../bin/runner.o -o ../bin/main
gcc fail.c -o ../bin/fail
./../bin/main ../bin/fail input/input.txt
rm ../bin/*