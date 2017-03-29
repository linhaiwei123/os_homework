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
#define SIZE 1024
int main(){
  int shmid;
  char *shmaddr;
//  printf("pre hello");
  shmid = shmget(IPC_PRIVATE,SIZE,0666);
//  printf("%d",shmid);
//  printf("hello");
  shmaddr = (char*)shmat(shmid, NULL, 0);
  printf("%s",shmaddr);
//  sem_t *sem;
//  sem = sem_open("hiahiahia",O_CREAT,0644,1);
//  while(1){
//  sem_wait(sem);
  //scanf("%s",&shmaddr);
//  printf("%s",shmaddr);
//  sem_post(sem);
//  if(strcmp(shmaddr,"q") == 0){
//    break;
//  }
//  strcpy(shamaddr, "hello world!");
//  shmdt(shmaddr);
//  sem_post(sem);
//  }

//  shmdt(shmaddr);
}
