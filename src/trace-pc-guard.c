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
	if (write(TOTAL_FILENO, tp, sizeof(uint32_t)) == -1) {
//		fprintf(stderr, "in trace-pc-guard-init : write error\n") ;	      
	}	
	
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
//	fprintf(stderr, "%s\n", PcDescr) ;
	if (write(BCOV_FILENO, guard, sizeof(uint32_t)) == -1) {
//		fprintf(stderr, "in trace-pc-guard : guard write error\n") ;	      
	}
	if (write(BCOV_FILENO, size_ptr, sizeof(uint32_t)) == -1) {
//		fprintf(stderr, "in trace-pc-guard : size write error\n") ;	      
	}
	if (write(BCOV_FILENO, PcDescr, size) == -1) {
//		fprintf(stderr, "in trace-pc-guard : PcDescr write error\n") ;	      
	}

}
