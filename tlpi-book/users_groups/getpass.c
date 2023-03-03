#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>

int main(void) {
    char * prompt = "enter your password:";

    char * password;
    password = getpass(prompt);
    printf("password is: %s\n", password);
    return 0;
}

