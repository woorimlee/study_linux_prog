#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*);

int main(int argc, char **argv) {
	DIR *dp;
	char *dir;
	struct stat st;
	struct dirent *d;
	char path[BUFSIZ+1];

	if (argc == 1) dir=".";
	else dir=argv[1];

	if ((dp=opendir(dir))==NULL) perror(dir);
	
	//printf("O\n");
	while((d=readdir(dp))!=NULL) {
		sprintf(path, "%s/%s", dir, d->d_name);
		if(lstat(path, &st) < 0) perror(path);
		else printStat(path, d->d_name , &st);
	}

	closedir(dp);
	exit(0);
}

void printStat(char *pathname, char *file, struct stat *st) {
	printf("%c%s ", type(st->st_mode), perm(st->st_mode));
	printf("%2lu ", st->st_nlink);
	printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
	printf("%6ld ", st->st_size);
	printf("%.12s ", ctime(&(st->st_mtime))+4);
	printf("%s\n", file);
}

char type(mode_t mode){
	if(S_ISREG(mode)) return('-');
	else if(S_ISDIR(mode)) return('d');
	else if(S_ISCHR(mode)) return('c');
	else if(S_ISBLK(mode)) return('b');
	else if(S_ISLNK(mode)) return('l');
	else if(S_ISFIFO(mode)) return('p');
	else if(S_ISSOCK(mode)) return('s');
	else return('0');
}

char *perm(mode_t mode) {
	int i;
	static char perms[10] = "----------";

	for(i=0; i<3; i++) {
		if(mode & (S_IRUSR >> i*3)) perms[i*3] = 'r';
		else if(mode & (S_IWUSR >> i*3)) perms[i*3+1] = 'w';
		else if(mode & (S_IXUSR >> i*3)) perms[i*3+2] = 'x';
	}
	return(perms);
}
