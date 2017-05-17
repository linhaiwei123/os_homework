#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *allocate_p(char ** str)
{
	*str = (char*)malloc(128*1024*1024*sizeof(char));
}
char *allocate_p_1024(char ** str)
{
	*str = (char*)malloc(1024*1024*1024*sizeof(char));
}
char *allocate_p_64(char ** str)
{
	*str = (char*)malloc(64*1024*1024*sizeof(char));
}
int main(void)
{
	printf("pid: %d\n",getpid());
	char *p1;
	char *p2;
	char *p3;
	char *p4;
	char *p5;
	char *p6;
	allocate_p(&p1);
	if(NULL == p1){
		printf("p1 is null");
	}
	allocate_p(&p2);
	if(NULL == p2){
		printf("p2 is null");
	}
	allocate_p(&p3);
	if(NULL == p3){
		printf("p3 is null");
	}
	allocate_p(&p4);
	if(NULL == p4){
		printf("p4 is null");
	}
	allocate_p(&p5);
	if(NULL == p5){
		printf("p5 is null");
	}
	allocate_p(&p6);
	if(NULL == p6){
		printf("p6 is null");
	}
	printf("malloc-down\n");
	getchar();
	free(p2);
	free(p3);
	free(p5);
	printf("free-down\n");
	getchar();
	char *p_1024;
	allocate_p_1024(&p_1024);
	if(p_1024 == NULL){
		printf("p_1024 is null");
	}
	printf("malloc-1024-down\n");
	getchar();
	char* p_64;
	allocate_p_64(&p_64);
	if(p_64 == NULL){
		printf("p_64 is null");
	}
	printf("malloca-64-down\n");
	getchar();
	return 0;
}
