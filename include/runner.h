enum Code {
	PASS = 0,
	FAIL = 1,
	KILL = 9,
	SEGV = 11,
	STOP = 19
};

enum Valid {

	UNRESOLVED = -1,
	VALID = 0,
	INVALID = 1,
};

typedef struct exitcode {

	int code_num;
	int valid;

} EXITCODE;

EXITCODE runner (char *, char *, char *);
int read_exec_dir (char *, char *);