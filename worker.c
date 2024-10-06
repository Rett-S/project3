//Rett Swyers - CS 4760

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define SHMKEY 44197
#define BUFF_SZ sizeof (int)

int main(int argc, char** argv) {

    int s = atoi(argv[1]); //this is an integer to store the amount of seconds
    int n = atoi(argv[2]); //this is an integer to store the amount of nanoseconds

    int shmid = shmget(SHMKEY, BUFF_SZ, 0777 | IPC_CREAT);
    if (shmid == -1) {
      printf(stderr,"Worker: Error with shmget\n");
      exit(1);
    }

    int *cint = (int*)(shmat(shmid,0,0));
    int *xint = cint + 1;
    s += *cint;
    n += *xint;
    for (int i=0;i<s;i++) {
      sleep(1);
    //SysClockS: %d SysClockNano: %d TermTimeS: %d TermTimeNano: %d - %d have passed since starting
      printf("WORKER PID:%d PPID:%d SysClockS:%d SysClockNano:%d TermTimeS:%d TermTimeNano:%d\n", getpid(),getppid(),*cint,*xint,s,n);
    }

    shmdt(cint);
    shmdt(xint);
    return EXIT_SUCCESS;

