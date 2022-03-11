all:
	clang -c src/runner.c -g -O3  -o bin/runner.o
	clang -c src/split.c -g -O3  -o bin/split.o
	clang -c src/reduce_to_substring.c -g -O3  -o bin/substring.o
	clang -c src/reduce_to_complement.c -g -O3  -o bin/complement.o
	clang -c src/ddmin.c -g -O3  -o bin/ddmin.o
	clang -c src/read_exec_dir.c -g -O3  -o bin/read_exec_dir.o
	clang src/main.c bin/runner.o bin/read_exec_dir.o -g -O3  -o bin/main
	clang src/ddmin_main.c bin/ddmin.o bin/runner.o bin/split.o bin/complement.o bin/substring.o -g -O3  -o bin/ddmin -lm

testcase:
	rm test/output/output_*.txt
	clang test/pass.c -g -O3  -o bin/pass
	clang test/fail.c -g -O3  -o bin/fail
	clang test/timeout.c -g -O3  -o bin/timeout
	cp test/output/output.txt test/output/output_passing.txt
	cp test/output/output.txt test/output/output_failing.txt
	cp test/output/output.txt test/output/output_timeout.txt

exec_all_dir:
	clang src/exec_test.c bin/runner.o -g -O3  -o bin/exec_test

ddmin:
	clang src/ddmin_main.c bin/ddmin.o bin/runner.o bin/split.o bin/complement.o bin/substring.o -g -O3  -o bin/ddmin -lm

split:
	clang src/split_main.c bin/split.o -g -O3  -o bin/split

reduce_to_substring:
	clang src/substring_main.c bin/runner.o bin/split.o bin/substring.o -g -O3  -o bin/substring

reduce_to_complement:
	clang src/complement_main.c bin/runner.o bin/split.o bin/complement.o -g -O3  -o bin/complement

clean:
	rm bin/*

