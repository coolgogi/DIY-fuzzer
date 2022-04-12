#include <stdio.h>
#include <stdlib.h>


int *
sorting_statement(int n, double * sus, double * con) {

        int * rank = (int *) malloc (sizeof(int) * (n + 1)) ;
        int * rank_tp = (int *) malloc (sizeof(int) * (n + 1)) ;

        for (int i = 1 ; i < n + 1 ; i ++) {
                rank_tp[i] = i ;
        }

        for (int i = 1 ; i < n ; i ++) {

                int pre_index = rank_tp[i] ;
                for (int j = i + 1 ; j < n + 1 ; j ++) {

                        int post_index = rank_tp[j] ;
                        double pre = sus[pre_index] ;
                        double post = sus[post_index] ;

                        if (pre < post) {
                                int tp = rank_tp[i] ;
                                rank_tp[i] = rank_tp[j] ;
                                rank_tp[j] = tp ;
                                pre_index = rank_tp[i] ;
                        }
                        else if (pre == post) {
                                pre = con[pre_index] ;
                                post = con[post_index] ;

                                if (pre < post) {
                                        int tp = rank_tp[i] ;
                                        rank_tp[i] = rank_tp[j] ;
                                        rank_tp[j] = tp ;

 			        	pre_index = rank_tp[i] ;
                                }
                                else if (pre == post) {
                                }
                        }
                }
        }
        int i = n ;
        while (i > 0) {
                int j = i - 1 ;

                int post_index = rank_tp[i] ;
                int pre_index = rank_tp[j] ;

                while ((sus[post_index] == sus[pre_index]) && (con[post_index] == con[pre_index])) {
                        j -- ;
                        pre_index = rank_tp[j] ;
                        if (j == 0) {
                                j = 1 ;
                                break ;
                        }

                }

                for (int index = i ; index > j ; index --) {
                        int tp = rank_tp[index] ;
                        rank[tp] = i ;
                }
                i = j ;
        }

        return rank ;
}
