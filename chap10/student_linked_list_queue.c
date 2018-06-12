#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    int id;
    char name[20];
    struct student *next;
}student;

int main() {
    int id;
    char name[20];
    student *ptr, *head = NULL, *tail = NULL;

    printf("학번과 이름을 입력하세요\n");

    while(scanf("%d %s", &id, name) == 2) {
	ptr = (student *)malloc(sizeof(student));
	if(ptr == NULL) {
	    perror("malloc");
	    exit(1);
	}

	ptr->id = id;
	strcpy(ptr->name, name);

	if(head == NULL) {
	    head = ptr;
	    tail = ptr;
	}

	tail->next = ptr;
	tail = ptr;

    }

    printf("학생 정보 출력\n");
    ptr = head;
    while(ptr != NULL) {
	printf("학번:%d 이름 :%s\n", ptr->id, ptr->name);
	ptr = ptr->next;
    }

    return 0;
}
