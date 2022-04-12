#include <stdio.h>
#include <stdlib.h>

double *
calculate_con (char mode, int * p_branch, int * f_branch, int * cases, int n) {

        double passed ;
        double failed ;
        double * con = (double *) malloc (sizeof(double) * (n + 1)) ;

        for (int i = 1 ; i < n + 1 ; i ++) {
                if (mode == 'T') {

                        passed = (double) p_branch[i] / (double) cases[0] ;
                        failed = (double) f_branch[i] / (double) cases[1] ;

                        if (passed > failed) {
                                con[i] = passed ;
                        }
                        else {
                                con[i] = failed ;
                        }
                }
                else {
                        con[i] = 0 ;
                }
        }
        return con ;
}
