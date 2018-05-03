#include <stdio.h>

int main ( int argc, char * argv[]) {
	char **ptr;
	extern char **environ;

	for (ptr = environ; *ptr != 0; ptr++) {
		printf("%s \n", *ptr);
		printf("se:%d \n", **ptr);
	}

	return 0;
}
