#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
  pid_t pid;
  pid = fork();
  if(pid < 0) {
   printf("error occured!\n");
  } else if(pid == 0) {
    printf("HI father! I`m ZOMBIE\n");
    exit(0);
  } else {
   sleep(10);
   wait(NULL);
  }

}
