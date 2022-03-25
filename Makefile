all:  runner branch
	clang -c src/read_exec_dir.c -g -O3 -o bin/read_exec_dir.o
	clang src/main.c bin/runner.o bin/read_exec_dir.o -g -O3 -o bin/main

reduce: runner
	clang -c src/ddmin/reduce.c -g -O3 -o bin/reduce.o

runner:
	clang -c src/runner.c -g -O3  -o bin/runner.o

ddmin: runner
	clang -c src/ddmin/ddmin.c -g -O3  -o bin/ddmin.o
	clang -c src/ddmin/reduce_to_substring.c bin/runner.o -g -O3 -o bin/reduce_to_substring.o -lm
	clang -c src/ddmin/reduce_to_complement.c bin/runner.o -g -O3 -o bin/reduce_to_complement.o -lm
	clang src/ddmin/ddmin_main.c bin/ddmin.o bin/runner.o bin/reduce_to_substring.o bin/reduce_to_complement.o -g -O3  -o bin/ddmin -lm

reduce_to_substring: runner split substring
	clang src/ddmin/substring_main.c bin/runner.o bin/split.o bin/substring.o -g -O3  -o bin/substring -lm

substring:
	clang -c src/ddmin/reduce_to_substring.c -g -O3 -o bin/substring.o
	
split:
	clang -c src/ddmin/split.c -g -O3 -o bin/split.o 

reduce_to_complement: runner split complement
	clang src/ddmin/complement_main.c bin/runner.o bin/split.o bin/complement.o -g -O3  -o bin/complement -lm

complement:
	clang -c src/ddmin/reduce_to_complement.c -g -O3 -o bin/complement.o

exec_all_dir: runner
	clang src/exec_test.c bin/runner.o -g -O3  -o bin/exec_test

testcase: runner
	clang src/testcase.c bin/runner.o -g -O3 --coverage -o bin/testcase
	clang test/pass.c -g -O3 -o test/input/pass
	clang test/fail.c -g -O3 -o test/input/fail
	clang test/timeout.c -g -O3 -o test/input/timeout

branch:
	clang -fsanitize=address -c src/trace-pc-guard.c -o bin/trace-pc-guard.o
	clang -g -fsanitize=address -fsanitize-coverage=trace-pc-guard -o bin/branch src/branch.c bin/trace-pc-guard.o

clean:
	rm bin/*

