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

enum file_descriptor {
	BCOV_FILENO = 3,
	TOTAL_FILENO = 4,	
};

typedef struct exitcode {

	int code_num;
	int valid;
	int child_pid;

} EXITCODE;

EXITCODE runner (char *, char *, char *);
EXITCODE rm_runner (char *);
EXITCODE sancov_runner (char *, char *, char *);
int * read_exec_dir (char *, char *, char *, int);
int * exec_sancov_dir (char *, char *, char *, int);
double * calculate_sus(char, int *, int *, int *, int) ;
double * calculate_con(char, int *, int *, int *, int) ;
int * sorting_statement(int, double *, double *) ;
