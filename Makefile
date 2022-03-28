CC=clang
INCLDIR = include/
BINDIR = bin/
SRCDIR = src/


SRC = $(wildcard src/*.c)
INCL = $(wildcard include/*.o)

all:  runner trace
	$(CC) -c src/read_exec_dir.c -g -O0 -o bin/read_exec_dir.o
	$(CC) src/main.c bin/runner.o bin/read_exec_dir.o -g -O0 -o bin/main

runner:
	$(CC) -c src/runner.c -g -O0  -o bin/runner.o

trace:
	$(CC) -fsanitize=address -c src/trace-pc-guard.c -o bin/trace-pc-guard.o

ddmin: runner
	$(CC) -c src/ddmin/ddmin.c -g -O3  -o bin/ddmin.o
	$(CC) -c src/ddmin/reduce_to_substring.c bin/runner.o -g -O3 -o bin/reduce_to_substring.o -lm
	$(CC) -c src/ddmin/reduce_to_complement.c bin/runner.o -g -O3 -o bin/reduce_to_complement.o -lm
	$(CC) src/ddmin/ddmin_main.c bin/ddmin.o bin/runner.o bin/reduce_to_substring.o bin/reduce_to_complement.o -g -O3  -o bin/ddmin -lm

reduce: runner
	$(CC) -c src/ddmin/reduce.c -g -O3 -o bin/reduce.o

reduce_to_substring: runner split substring
	$(CC) src/ddmin/substring_main.c bin/runner.o bin/split.o bin/substring.o -g -O3  -o bin/substring -lm

substring:
	$(CC) -c src/ddmin/reduce_to_substring.c -g -O3 -o bin/substring.o
	
split:
	$(CC) -c src/ddmin/split.c -g -O3 -o bin/split.o 

reduce_to_complement: runner split complement
	$(CC) src/ddmin/complement_main.c bin/runner.o bin/split.o bin/complement.o -g -O3  -o bin/complement -lm

complement:
	$(CC) -c src/ddmin/reduce_to_complement.c -g -O3 -o bin/complement.o

exec_all_dir: runner
	$(CC) src/exec_test.c bin/runner.o -g -O3  -o bin/exec_test

testcase: runner
	$(CC) src/testcase.c bin/runner.o -g -O3 --coverage -o bin/testcase
	$(CC) test/pass.c -g -O3 -o test/input/pass
	$(CC) test/fail.c -g -O3 -o test/input/fail
	$(CC) test/timeout.c -g -O3 -o test/input/timeout

branch: trace
	$(CC) -g -fsanitize=address -fsanitize-coverage=trace-pc-guard -o bin/branch src/branch.c bin/trace-pc-guard.o

clean:
	rm bin/*

