all:
	gcc -c src/runner.c -o bin/runner.o
	gcc src/main.c bin/runner.o -o bin/main


pass:
	gcc test/pass.c -o bin/file


fail:
	gcc test/fail.c -o bin/file


timeout:
	gcc test/timeout.c -o bin/file


run:
	./bin/main bin/file test/input/input.txt


clean:
	rm bin/*
