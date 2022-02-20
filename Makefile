all:
	gcc -c src/runner.c -o bin/runner.o
	gcc src/main.c bin/runner.o -o bin/main

testcase:
	rm ./test/output/output_*.txt
	gcc ./test/pass.c -o ./bin/pass
	gcc ./test/fail.c -o ./bin/fail
	gcc ./test/timeout.c -o ./bin/timeout
	cp ./test/output/output.txt ./test/output/output_passing.txt
	cp ./test/output/output.txt ./test/output/output_failing.txt
	cp ./test/output/output.txt ./test/output/output_timeout.txt

clean:
	rm bin/*

