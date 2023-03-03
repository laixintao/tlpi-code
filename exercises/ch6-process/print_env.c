#include <stdio.h>
#include <stdlib.h>

extern char ** environ;

int main(int argc, char ** argv){
    char **ep;

    for (ep=environ; *ep != NULL; ep ++){
        puts(*ep);
    }

    char * shell = getenv("SHELL");
    puts(shell);

    return 0;

}
