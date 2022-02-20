#include <stdio.h>

int
main (int argc, char * argv[]) {
    char str[100] ;
    scanf("%s", str);
    printf("I'm failing case\nstring : %s\n", str);
    int *p = NULL;
    *p = 1;
    return 0;
}