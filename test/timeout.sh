echo "timeout case test"
gcc -c ../src/runner.c -o ../bin/runner.o
gcc ../src/main.c ../bin/runner.o -o ../bin/main
gcc timeout.c -o ../bin/timeout
./../bin/main ../bin/timeout input/input.txt
rm ../bin/*