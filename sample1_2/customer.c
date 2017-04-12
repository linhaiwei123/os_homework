#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com_sem.h"


int main(){
  void *shared_memory = (void *)0;
  struct shared_mem_st * shared_stuff;
  
  int shmid;
  int num_read;
  pid_t fork_result;
  sem_t *sem_queue, *sem_queue_empty, *sem_queue_full;
  
  shmid = shmget((key_t)123456, sizeof(struct shared_mem_st), IPC_CREAT);
  shared_memory = (char*)shmat(shmid, (void*)0,0);
  shared_stuff = (struct shared_mem_st *)shared_memory;

  sem_queue = sem_open(queue_mutex, O_CREAT, 0644, 1);
  sem_queue_empty = sem_open(queue_empty, O_CREAT, 0644, 1);
  sem_queue_full = sem_open(queue_full, O_CREAT, 0644, 1);
    
  
  fork_result = fork();
  if(fork_result == -1){
    fprintf(stderr, "Fork failure\n");
  }
  if(fork_result == 0){
    while(1){
      sem_wait(sem_queue_full);
      sem_wait(sem_queue);
      printf("PID: %d ",getpid());
      printf("line read %d",shared_stuff->line_read);
      printf("content: %s\n",shared_stuff->buffer[shared_stuff->line_read]);
      if(strcmp(shared_stuff->buffer[shared_stuff->line_read],"QUIT") == 0){
            break;
      }
      shared_stuff->line_read = (shared_stuff->line_read + 1) % NUM_LINE;
      sem_post(sem_queue);
      sem_post(sem_queue_empty);	
    }
    sem_unlink(queue_mutex);
    sem_unlink(queue_empty);
    sem_unlink(queue_full);
  }else{
     while(1){
      sem_wait(sem_queue_full);
      sem_wait(sem_queue);
      printf("PID: %d ", getpid());
      printf("content: %s\n", shared_stuff->buffer[shared_stuff->line_read]);
      if(strcmp(shared_stuff->buffer[shared_stuff->line_read],"QUIT") == 0){
           break;
      }
      shared_stuff->line_read = (shared_stuff->line_read + 1) % NUM_LINE;
      sem_post(sem_queue);
      sem_post(sem_queue_empty);
     }
     sem_unlink(queue_mutex);
     sem_unlink(queue_empty);
     sem_unlink(queue_full);
  }
  exit(EXIT_SUCCESS);
}

