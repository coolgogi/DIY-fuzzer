#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sanitizer/coverage_interface.h>
#include "../include/runner.h"
void 
__sanitizer_cov_trace_pc_guard_init (uint32_t *start, uint32_t *stop) 
{
	static uint64_t N ; 
	if (start == stop || *start) 
		return ;  

//	printf("INIT: %p %p\n", start, stop) ;

	for (uint32_t *x = start; x < stop; x++)
		*x = ++N ;
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
	
	write(BCOV_FILENO, PcDescr, 512) ;
	write(TOTAL_FILENO, guard, sizeof(uint32_t)) ;
	write(TOTAL_FILENO, PcDescr, sizeof(PcDescr));
}
