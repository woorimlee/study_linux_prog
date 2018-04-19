//The book says 'list1.c' instead of 'simple_ls.c'
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	DIR *dp;
	char *dir;
	struct dirent *d;
	struct stat st;
	
	//if you want to know what is 'BUFSIZ', than access below site.
	//http://www.delorie.com/gnu/docs/glibc/libc_226.html
	char path[BUFSIZ+1];

	if(argc ==1) dir = "."; //this dir
	else dir = argv[1];
	
	//DIR *opendir(const char *path);
	if ((dp = opendir(dir)) ==NULL) {
		perror(dir);
		exit(1);
	}

	//struct dirent *readdir(DIR *dp);
	while((d = readdir(dp)) != NULL) printf("%s \n", d->d_name);
	
	closedir(dp);
	exit(0);
}

	
