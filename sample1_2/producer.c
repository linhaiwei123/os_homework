#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

#include "shm_com_sem.h"

int main(void)
{
  void *shared_memory = (void * )0;
  struct shared_mem_st *shared_stuff;
  char key_line[256];

  int shmid;

  sem_t * sem_queue, *sem_queue_empty, *sem_queue_full;

  shmid = shmget((key_t)1234,sizeof(struct  shared_mem_st),IPC_CREAT);
  shared_memory = (char*)shmat(shmid, (void*)0, 0);
  shared_stuff = (struct shared_mem_st*) shared_memory;

  
  
  sem_queue = sem_open(queue_mutex, O_CREAT, 0644,1);
  sem_queue_empty = sem_open(queue_empty, O_CREAT, 0644,16);
  sem_queue_full = sem_open(queue_full, O_CREAT, 0644, 0);

  shared_stuff->line_write = 0;
  shared_stuff->line_read = 0;
  int result = -2;
  while(1)
  {
  sem_getvalue(sem_queue,&result);
   printf("sem_queue %d\n",result);
    sem_getvalue(sem_queue_empty,&result);
    printf("sem_queue_empty %d\n", result);
    sem_getvalue(sem_queue_full, &result);
    printf("sem_queue_full %d\n", result);
    printf("wait sem_queue_empty pid: %d\n", getpid());
    sem_wait(sem_queue_empty);
    printf("get sem_queue_empty pid: %id\n", getpid());
    printf("wait sem_queue pid: %d\n", getpid());
    sem_wait(sem_queue);
    printf("get sem_queue pid: %d\n", getpid());

    scanf("%s",key_line);
    strcpy(shared_stuff->buffer[shared_stuff->line_write], key_line);
    shared_stuff->line_write = (shared_stuff->line_write + 1) % NUM_LINE;
    printf("current line write %d\n",shared_stuff->line_write);
    sem_post(sem_queue);
    printf("post sem_queue pid: %d\n", getpid());
    sem_post(sem_queue_full);
    printf("post sem_queue_full pid: %d\n", getpid());
    printf("sleep pid: %d\n",getpid());
    sleep(2);
  }


  if(shmdt(shared_memory) == -1){
    fprintf(stderr, "shmdt failed\n");
    exit(EXIT_FAILURE);
  }
  
}

