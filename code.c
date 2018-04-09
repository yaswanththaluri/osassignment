
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>

#define MIN_PID 100
#define MAX_PID 1000
#define array_size MAX_PID-MIN_PID+1

void *thread_fun(void *args);

int processID_status[ array_size ];
int no_of_processes;
struct process
{
int process_number;
int pid;
int time;
};


int main()
{
printf("Enter number of Threads: \n");
scanf("%d",&no_of_processes);

int result = allocation_map();

if(result == 0)
{
printf("Map Allocated successfully");
}
else
{
printf("Error occured in Allocation Map");
}


struct process p[no_of_processes];
pthread_t process_threads[no_of_processes];

for(int i=0; i<no_of_processes; i++)
{
p[i].process_number = i;
pthread_create(&process_threads[i], NULL, thread_fun, &p[i]);
}

for(int i=0; i<no_of_processes; i++)
{
pthread_join(process_threads[i],NULL);
}
}



int allocation_map()
{
int i;
for(i = 0; i < array_size; i++)
{
processID_status[i] = 0;
}
return 0;
}


void *thread_fun(void *pro)
{
struct process *p = (struct process*)pro;
printf("%d is fetching process id\n",p->process_number);
p->pid = allocate_pid();
while(processid_check(p->pid) == 1)
{
sleep(2);
printf("\n%d is fetching pid...\n",p->process_number);
p->pid = allocate_pid();
}
p->time = sleep_time();
printf("\n%d: pid = %d, sleep time =%d\n",p->process_number,p->pid,p->time);
printf("Process %d entered into sleep...\n",p->pid);
sleep(p->time);
printf("\n Process:%d Terminated...\n",p->pid);
release_pid(p->pid);
display(no_of_processes);
}


int allocate_pid()
{
int i;
for(i = 0;i<array_size;i++)
{
if(processID_status[i] == 0)
{
processID_status[i] = 1;
return i+100;
}
}
return 1;
}


int processid_check(int pid)
{
if(pid>=100)
{
printf("Process ID: %d allocated to the process Successfully\n",pid);
return 0;
}
else if(pid == 1)
{
printf("Allocating Process ID has been Failed\n");
return 1;
}
else
{
printf("Error.........\n");
return 1;
}
}


int sleep_time()
{
return rand()%10;
}


void release_pid(int p)
{
int pid = p-100;
processID_status[pid] = 0;
}


void display(int n)
{
int i;
for(i = 0;i<n;i++)
{
printf("Process: %d = status:  %d\t",i+100,processID_status[i]);
}
}
