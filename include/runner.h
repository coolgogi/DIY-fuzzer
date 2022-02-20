enum Code {
	ERROR_FORK = -3,
	ERROR_DUP2 = -2,
	ERROR_EXECL = -1,
	PASS = 0,
	FAIL = 1,
	TIMEOUT = 9,
	SEGV = 11
};

enum Valid {

	VALID = 0,
	INVALID = 1,
};

typedef struct exitcode {

	int code_num;
	int valid;

} EXITCODE;

EXITCODE runner (char *, char *, char *);