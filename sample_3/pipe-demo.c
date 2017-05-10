#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
int main(){
  pid_t pid = 0;
  int fds[2];
  char buf[128];
  int nwr = 0;

  pipe(fds);
  
  pid = fork();
  if(pid < 0){
   printf("Fork error!\n");
   return -1;
  }else if(pid == 0) {
    printf("This is child process, pid = %id\n", getpid());
    printf("Child:waiting for message..\n");
    close(fds[1]);
    nwr = read(fds[0], buf, sizeof(buf));
    printf("Child:received\"%s\"\n", buf);
  } else {
    printf("This is parent process, pid = %d\n", getpid());
    printf("Parent:sending message...\n");
    close(fds[0]);
    strcpy(buf, "Message from parent!");
    nwr = write(fds[1], buf, sizeof(buf));
    printf("Parent:send %d bytes to child.\n", nwr);
  }
  return 0;
}
