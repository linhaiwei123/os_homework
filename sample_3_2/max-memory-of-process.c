#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char * allocate_x(char **str,int size)
{
	*str = (char*)malloc(size*1024*1024*sizeof(char));
}

int main(void) {
	int g_4 = 4 * 1024;
	int max_size = g_4;
	int min_size = 0;
	int mid_size = min_size + max_size / 2;
	char * p;
	while(1) {
		allocate_x(&p,mid_size);
		if(p == NULL){
			printf("mid_size error: %d\n", mid_size);
			max_size = mid_size;
			mid_size = (min_size + mid_size)/2;
			
			getchar();
		}else{
			printf("mid_size success: %d\n", mid_size);
			min_size = mid_size;
			mid_size = (max_size + mid_size)/2;
			
			getchar();
			free(p);
			
		}
	}
}
