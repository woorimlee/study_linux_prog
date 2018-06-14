#include <stdio.h>
#include <stdlib.h>
static void exit_handler1(void), exit_handler2(void);

int main(void) {
    if(atexit(exit_handler1) != 0) perror("Can't register a function 'exit_handler1' to be called at process termination\n");
    if(atexit(exit_handler2) != 0) perror("Can't register a function 'exit_h    andler2' to be called at process termination\n");
    printf("Process terminates\n");
    exit(0);
}

static void exit_handler1(void) {
    printf("exit_handler 1 is activated\n");
}

static void exit_handler2(void) {
    printf("exit_handler 2 is activated\n");
}

