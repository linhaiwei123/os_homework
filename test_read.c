#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <error.h>
#include <semaphore.h>
#include <errno.h>
#define SIZE 1024
int main(){
  int shmid;
  char *shmaddr;
  char buf[SIZE];
//  printf("pre hello");
//  key_t key = ftok("/dev/null",1);
//  printf("%d",key);
  shmid = shmget((key_t)1234,SIZE,IPC_CREAT);
//  printf("%d",shmid);
//  printf("hello");
  shmaddr = (char*)shmat(shmid, (void*)0, 0);
  printf("addr: %d",&shmaddr);
//  strcpy(shmaddr,"hello world");
//  printf("%s",shmaddr);
  sem_t *sem;
  sem = sem_open("src",O_CREAT,0644,1);
  sem_post(sem);//init the sem enter num
  sem_t *sem_read;
  sem_read = sem_open("read",O_CREAT,0644,1);
  sem_post(sem_read);
  sem_t *sem_write;
  sem_write = sem_open("write",O_CREAT,0644,1);
  if(sem == SEM_FAILED){
   printf("%s\n",strerror(errno));
  }else{
   printf("open success\n");
  }
  int result = -100; 
  while(1){
  sem_getvalue(sem,&result);
  printf("src %d\n",result);
  sem_getvalue(sem_read, &result);
  printf("read %d\n",result);
  sem_getvalue(sem_write,&result);
  printf("write %d\n", result);
  sem_wait(sem_read);
  sem_wait(sem);
//  printf("before scanf"); 
  scanf("%s",buf);
//  printf("scanf result: %s",buf);
//  printf("%s\n",buf);
  strcpy(shmaddr,buf);
  printf(" enter %s\n",shmaddr);
//  printf("before printf");
//  printf("%s",shmaddr);
//  printf("after printf");
  sem_post(sem);
  sem_post(sem_write);
//  if(strcmp(shmaddr,"q") == 0){
//    break;
//  }
//  strcpy(shamaddr, "hello world!");
//  shmdt(shmaddr);
//  sem_post(sem);
  }

  shmdt(shmaddr);
}
