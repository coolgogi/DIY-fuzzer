CC=clang
INCLDIR = include/
BINDIR = bin/
SRCDIR = src/
CFLAGS = -g -O0

SRC = $(wildcard src/*.c)
INCL = $(wildcard include/*.o)

all:  runner trace calculate sorting
	$(CC) -c src/read_exec_dir.c $(CFLAGS) -o bin/read_exec_dir.o
	$(CC) src/main.c bin/runner.o bin/read_exec_dir.o bin/calculate_con.o bin/calculate_sus.o bin/sorting_statement.o $(CFLAGS) -o bin/main -lm

runner:
	$(CC) -c src/runner.c $(CFLAGS)  -o bin/runner.o
	$(CC) -c src/rm_runner.c $(CFLAGS)  -o bin/rm_runner.o
	$(CC) -c src/sancov_runner.c $(CFLAGS)  -o bin/sancov_runner.o

trace:
	$(CC) -fsanitize=address -c src/trace-pc-guard.c -o bin/trace-pc-guard.o

calculate:
	$(CC) -c src/calculate_con.c $(CFLAGS) -o bin/calculate_con.o
	$(CC) -c src/calculate_sus.c $(CFLAGS) -o bin/calculate_sus.o

sorting:
	$(CC) -c src/sorting_statement.c $(CFLAGS) -o bin/sorting_statement.o

sancov: runner trace
	$(CC) -c src/exec_sancov_dir.c $(CFLAGS) -o bin/exec_sancov_dir.o
	$(CC) src/sancov_main.c bin/runner.o bin/sancov_runner.o bin/rm_runner.o bin/exec_sancov_dir.o bin/calculate_sus.o bin/calculate_con.o bin/sorting_statement.o $(CFLAGS) -o bin/sancov_main -lm

reduction:
	$(CC) -fsanitize=address src/test-case_reduction.c $(CFLAGS) -o bin/test-case_reduction

ddmin: runner
	$(CC) -c src/ddmin/ddmin.c $(CFLAGS)  -o bin/ddmin.o
	$(CC) -c src/ddmin/reduce_to_substring.c bin/runner.o $(CFLAGS) -o bin/reduce_to_substring.o -lm
	$(CC) -c src/ddmin/reduce_to_complement.c bin/runner.o $(CFLAGS) -o bin/reduce_to_complement.o -lm
	$(CC) src/ddmin/ddmin_main.c bin/ddmin.o bin/runner.o bin/reduce_to_substring.o bin/reduce_to_complement.o $(CFLAGS)  -o bin/ddmin -lm

reduce: runner
	$(CC) -c src/ddmin/reduce.c $(CFLAGS) -o bin/reduce.o

reduce_to_substring: runner split substring
	$(CC) src/ddmin/substring_main.c bin/runner.o bin/split.o bin/substring.o $(CFLAGS)  -o bin/substring -lm

substring:
	$(CC) -c src/ddmin/reduce_to_substring.c $(CFLAGS) -o bin/substring.o
	
split:
	$(CC) -c src/ddmin/split.c $(CFLAGS) -o bin/split.o 

reduce_to_complement: runner split complement
	$(CC) src/ddmin/complement_main.c bin/runner.o bin/split.o bin/complement.o $(CFLAGS)  -o bin/complement -lm

complement:
	$(CC) -c src/ddmin/reduce_to_complement.c $(CFLAGS) -o bin/complement.o

exec_all_dir: runner
	$(CC) src/exec_test.c bin/runner.o $(CFLAGS)  -o bin/exec_test

testcase: runner
	$(CC) src/testcase.c bin/runner.o $(CFLAGS) --coverage -o bin/testcase
	$(CC) test/pass.c $(CFLAGS) -o test/input/pass
	$(CC) test/fail.c $(CFLAGS) -o test/input/fail
	$(CC) test/timeout.c $(CFLAGS) -o test/input/timeout

branch: trace
	$(CC) -g -fsanitize=address -fsanitize-coverage=trace-pc-guard -o bin/branch src/branch.c bin/trace-pc-guard.o

clean:
	rm bin/*

