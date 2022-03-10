all:
	gcc -c src/runner.c -o bin/runner.o
	gcc -c src/read_exec_dir.c -o bin/read_exec_dir.o
	gcc src/main.c bin/runner.o bin/read_exec_dir.o -o bin/main

testcase:
	rm test/output/output_*.txt
	gcc test/pass.c -o bin/pass
	gcc test/fail.c -o bin/fail
	gcc test/timeout.c -o bin/timeout
	cp test/output/output.txt test/output/output_passing.txt
	cp test/output/output.txt test/output/output_failing.txt
	cp test/output/output.txt test/output/output_timeout.txt

exec_all_dir:
	gcc src/exec_test.c bin/runner.o -o bin/exec_test

ddmin:
	gcc src/ddmin_main.c bin/runner.o -o bin/ddmin

split:
	gcc -c src/split.c -o bin/split.o
	gcc src/split_main.c bin/split.o -o bin/split

reduce_to_substring:
	gcc -c src/reduce_to_substring.c -o bin/substring.o
	gcc src/substring_main.c bin/runner.o bin/split.o bin/substring.o -o bin/substring

reduce_to_complement:
	gcc -c src/reduce_to_complement.c -o bin/complement.o
	gcc src/complement_main.c bin/runner.o bin/split.o bin/complement.o -o bin/complement

clean:
	rm bin/*

