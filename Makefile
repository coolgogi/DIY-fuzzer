all:
	gcc -c src/runner.c -o bin/runner.o
	gcc -c src/read_exec_dir.c -o bin/read_exec_dir.o
	gcc src/main.c bin/runner.o bin/read_exec_dir.o -o bin/main

testcase:
	rm ./test/output/output_*.txt
	gcc ./test/pass.c -o ./bin/pass
	gcc ./test/fail.c -o ./bin/fail
	gcc ./test/timeout.c -o ./bin/timeout
	cp ./test/output/output.txt ./test/output/output_passing.txt
	cp ./test/output/output.txt ./test/output/output_failing.txt
	cp ./test/output/output.txt ./test/output/output_timeout.txt

exec_all_dir:
	gcc ./src/exec_test.c bin/runner.o -o ./bin/exec_test


clean:
	rm bin/*

