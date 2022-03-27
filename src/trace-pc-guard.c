#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sanitizer/coverage_interface.h>
#include "../include/runner.h"

uint32_t num_of_branch ;

void 
__sanitizer_cov_trace_pc_guard_init (uint32_t * start, uint32_t * end) 
{
	num_of_branch = 0 ; 
	if (start == end || * start) { 
		return ;  
	}
	
	for (uint32_t * i = start ; i < end ; i++) {
		num_of_branch++ ;
		* i = num_of_branch ;
	}

}

void 
__sanitizer_cov_trace_pc_guard (uint32_t *guard) 
{
	if (guard == NULL) 
		return ;

	void *PC = __builtin_return_address(0) ;
	char PcDescr[512] ;
	__sanitizer_symbolize_pc(PC, "%L", PcDescr, sizeof(PcDescr)) ;
	PcDescr[511] = '\n' ;
	uint32_t * tp = & num_of_branch ;

	write(STDOUT_FILENO, PcDescr, 512) ;	

	write(TOTAL_FILENO, guard, sizeof(uint32_t)) ;
	write(TOTAL_FILENO, tp, sizeof(uint32_t)) ;
	write(TOTAL_FILENO, PcDescr, 512) ;
}
