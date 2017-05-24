#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char * allocate_256(char ** str)
{
//	*str = (char*)calloc(256*1024*1024,sizeof(char));
	*str = (char*)malloc(256*1024*1024*sizeof(char));
}

int main(void)
{
	char *p;
	printf("pid: %d\n", getpid());
	printf("allocate star\n");
	allocate_256(&p);
	if(NULL == p) {
		printf("p is null\n");
	}
	
	int i = 0;
	int m_256 = 256 * 1024 * 1024;
	int k_4 = 4 * 1024;
	printf("allocate end\n");
	printf("start write loop: \n");
	for(i = 0; i < m_256; i+=k_4){
//		printf("before read i : %d\n", i);
//		getchar();
//		int data_read = p[i];
//		printf("after read data: %d\n",data_read);
		printf("before write i : %d\n", i);
		getchar();
		p[i] = i % 26;
		printf("after write data");
		if(getchar() == 'q'){
			printf("break write i:%d\n", i);
			getchar();
			break;
		}else{
			getchar();
		}
		
	}
	
	printf("start read loop: \n");
	for(i = 0; i < m_256; i+= k_4) {
		printf("before read i: %d\n", i);
		getchar();
		char data_read = p[i];
		printf("after read data: %d\n", data_read);
		getchar();
	}

	printf("before release memory");
	free(p);
	printf("after release memory");
}
