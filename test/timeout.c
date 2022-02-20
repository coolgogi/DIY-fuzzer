#include <stdio.h>

int
main (int argc, char * argv[]) {
    char str[100] ;
    scanf("%s", str);
    printf("I'm timeout case\nstring : %s\n", str);
    while (1) {};
    return 0;
}