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
	char path[BUFSIZ+1];
	
	if (argc ==1) dir = ".";
	else dir = argv[1];
	
	if ((dp = opendir(dir)) ==NULL) {
		perror(dir);	
		exit(1);
	}
	
	while((d = readdir(dp)) != NULL) {
		sprintf(path, "%s/%s", dir, d->d_name);
		if (lstat(path,&st) < 0) perror(path);
		else printf("%2ld %s\n", st.st_blocks, d->d_name);
	}
}

