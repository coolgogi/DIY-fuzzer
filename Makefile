all:
	gcc -c src/runner.c -o bin/runner.o
	gcc src/main.c bin/runner.o -o main


pass:
	gcc test/pass.c -o file


fail:
	gcc test/fail.c -o file


timeout:
	gcc test/timeout.c -o file


run:
	./main file test/input.txt


clean:
	rm file
	rm main