all:
	gcc -c src/runner.c -o src/runner.o
pass:
	gcc test/test_pass.c src/runner.o -o testFile

fail:
	gcc test/test_fail.c src/runner.o -o testFile

timeout:
	gcc test/test_timeout.c src/runner.o -o testFile

run:
	./testFile

clean:
	rm testFile
	rm file