#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int tprintf(const char*fmt, ...);

int  main(void)
{
	int i = 0, j = 0,k = 0,q = 0;
	pid_t pid;
	pid_t pid_array[3];
	int length = 0;
	printf("Hello from parent Process, PID is %d.\n", getpid());	
	for(k = 0; k <3; k++)
	{
		pid = fork();
		if(pid == 0)
		{
			break;
		}	
		else 
		{
		  pid_array[length] = pid;
		  length++;
		}
	}

	if(pid == 0) //child process
	{
		sleep(1);
		for(i = 0; i < 3; i++)
		{
			printf("Hello from Child Process %d. %d times\n", getpid(), i+1);
			sleep(1);
		}
		printf("exit from Child Process %d.\n", getpid());
		exit(0);
	}
	else if(pid != -1) //parent process
	{
		//tprintf("Parent forked one child process == %d.\n", pid);
		tprintf("Parent is waiting for child to exit.\n");
//		waitpid(pid, NULL, 0);
//		waitpid(another_pid, NULL, 0);
		for(q = 0 ; q < length; q++)
		{
			waitpid(pid_array[q],NULL, 0);
		}
		//tprintf("Child Process has exited.\n");
	printf("Parent had exited.\n");
	}else tprintf(" Everything was done without error.\n ");

	return 0;
}

int tprintf(const char*fmt, ...)
{
	va_list args;
		struct tm *tstruct;
		time_t tsec;
		tsec = time(NULL);
		tstruct = localtime(&tsec);
		printf("%02d:%02d:%02d: %5d|", tstruct->tm_hour, tstruct->tm_min, tstruct->tm_sec, getpid());
		va_start(args, fmt);
		return vprintf(fmt, args);
}


