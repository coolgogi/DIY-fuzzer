TARGET 	= ./triangle.c
CC      = clang
BIN	= ./triangle
#CFLAGS	= -g -O0 -fprofile-instr-generate -fcoverage-mapping -Wall
CFLAGS = -g -fsanitize=address -fsanitize-coverage=trace-pc-guard
all:
	$(CC) $(CFLAGS) $(TARGET) -o $(BIN)

clean:
	rm -r triangle.gcda triangle.gcno triangle.c.gcov triangle *.profraw *.profdata triangle.dSYM
