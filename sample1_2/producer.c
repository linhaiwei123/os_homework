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

  shmid = shmget((key_t)123456,sizeof(struct  shared_mem_st),IPC_CREAT);
  shared_memory = (char*)shmat(shmid, (void*)0, 0);
  shared_stuff = (struct shared_mem_st*) shared_memory;
  
  sem_queue = sem_open(queue_mutex, O_CREAT, 0644,1);
  sem_queue_empty = sem_open(queue_empty, O_CREAT, 0644,1);
  sem_queue_full = sem_open(queue_full, O_CREAT, 0644, 1);
  sem_post(sem_queue);
  sem_post(sem_queue_empty);
  sem_post(sem_queue_full);
  shared_stuff->line_write = 0;
  shared_stuff->line_read = 0;
  while(1)
  {
    scanf("%s",key_line);
    sem_wait(sem_queue_empty);
    sem_wait(sem_queue);
    strcpy(shared_stuff->buffer[shared_stuff->line_write], key_line);
    shared_stuff->line_write = (shared_stuff->line_write + 1) * NUM_LINE;
    sem_post(sem_queue);
    sem_post(sem_queue_full);
  }

  if(shmdt(shared_memory) == -1){
    fprintf(stderr, "shmdt failed\n");
    exit(EXIT_FAILURE);
  }
  
}

