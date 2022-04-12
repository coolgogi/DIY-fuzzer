#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *
calculate_sus (char type, int * p_branch, int * f_branch, int * cases, int n) {

        double passed ;
        double failed ;
        double totalFailed ;

        double * sus = (double *) malloc (sizeof(double) * (n + 1)) ;

        for (int i = 1 ; i < n + 1 ; i ++) {

                if (type == 'T') {
                        passed = (double) p_branch[i] / (double) cases[0] ;
                        failed = (double) f_branch[i] / (double) cases[1] ;

                        if (passed == 0 && failed == 0) {
                                sus[i] = 0 ;
                        }
                        else {
				sus[i] = failed / (failed + passed) ;
                        }
                }
                else if (type == 'S') {
                        passed = (double) p_branch[i] ;
                        failed = (double) f_branch[i] ;

                        if (passed == 0 && failed == 0) {
                                sus[i] = 0 ;
                        }
                        else {
                                sus[i] = failed / (failed + passed) ;
                        }
                }
                else if (type == 'J') {
                        passed = (double) p_branch[i] ;
                        failed = (double) f_branch[i] ;
                        totalFailed = (double) cases[1] ;

                        if (totalFailed == 0 && passed == 0) {
                                sus[i] = 0 ;
                        }
                        else {
                                sus[i] = failed / (totalFailed + passed) ;
                        }
                }
                else if (type =='O') {
                        passed = (double) p_branch[i] ;
                        failed = (double) f_branch[i] ;
                        totalFailed = (double) cases[1] ;

                        double tp = totalFailed * (failed + passed) ;
                        if (tp == 0) {
                                sus[i] = 0 ;
                        }
                        else {
                                sus[i] = failed / sqrt(tp) ;
	                }
                }
        }
        return sus ;
}
