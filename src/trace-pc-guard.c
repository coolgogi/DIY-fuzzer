#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sanitizer/coverage_interface.h>
#include "../include/runner.h"

void 
__sanitizer_cov_trace_pc_guard_init (uint32_t * start, uint32_t * end) 
{
	uint32_t num_of_branch = 0 ; 
	
	if (start == end || * start) { 
		return ;  
	}
	
	for (uint32_t * i = start ; i < end ; i++) {
		num_of_branch++ ;
		* i = num_of_branch ;
	}
	
	uint32_t * tp = & num_of_branch ;
	write(TOTAL_FILENO, tp, sizeof(uint32_t)) ;
	
}

void 
__sanitizer_cov_trace_pc_guard (uint32_t * guard) 
{
	if (guard == NULL) 
		return ;

	
	void * PC = __builtin_return_address(0) ;
	char PcDescr[1024] ;
	
	__sanitizer_symbolize_pc(PC, "%p %F %L", PcDescr, sizeof(PcDescr)) ;
        uint32_t size = sizeof(PcDescr) ;
	uint32_t * size_ptr = &size ;

	write(BCOV_FILENO, guard, sizeof(uint32_t)) ;
	write(BCOV_FILENO, size_ptr, sizeof(uint32_t)) ;	
	write(BCOV_FILENO, PcDescr, size) ;

}
