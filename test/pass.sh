echo "passing case test"
gcc -c ../src/runner.c -o ../bin/runner.o
gcc ../src/main.c ../bin/runner.o -o ../bin/main
gcc pass.c -o ../bin/pass
./../bin/main ../bin/pass input/input.txt
rm ../bin/*