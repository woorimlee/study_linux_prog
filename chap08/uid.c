#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/types.h>


int main() {
    int pid;
    printf("Real User ID : %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
    printf("Effective User ID : %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
    printf("Real Group ID : %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
    printf("Effective Group ID : %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
}

