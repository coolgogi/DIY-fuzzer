#define ERROR_FORK -1
#define ERROR_DUP2 -2
#define PASS 0
#define FAIL 1
#define TIMEOUT 9
#define SEGV 11

typedef struct exitcode {

	int num;
	char msg[100];

} EXITCODE;

EXITCODE *
runner (char *, char *);