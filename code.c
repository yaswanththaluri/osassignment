#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#define MIN_PID 100
#define MAX_PID 1000
#define ARR_SIZE MAX_PID-MIN_PID+1

int pid_status[ARR_SIZE];

int allocate_map()        
{
    int i;
    for(i=0;i<ARR_SIZE;i++)
    {
        pid_status[i]=0;
    }
    return 0;               
}

int allocate_pid()
{
    int i;
    for(i=0;i<ARR_SIZE;i++)
    {
        if(pid_status[i]==0)   
        {
            pid_status[i]=1;     
            return i+100;        
        }
    }
    return 1;                
}

void release_pid(int p)
{
  int pid=p-100;            
  pid_status[pid]=0;       
}

void display()
{
  int i;
  for(i=0;i<ARR_SIZE;i++)
  {
    printf("[%d] = %d\t",i+100,pid_status[i]);
  }
}


struct proc
{
	int sno;
    int pid;
    int sl_time;
};

int pid_check(int pid)
{
    if(pid>=100)                        
    {
        printf("\nPid %d allocated successfully...\n",pid);
        return 0;                               
    }
    else if(pid==1)                     
    {
        printf("\nAllocating pid has been failed...\n"); 
        return 1;                        
    }
    else                        
    {
        printf("\nError.... pid: %d is returned...",pid);
        return 1;
    }
}

int set_sleep_time()
{
    return rand()%10;                     
}

void *thread_fun(void *pro)              
{
    struct process *p = (struct process *)pro;
    printf("\n%d: Fetching pid...\n",p->sno);
    p->pid = allocate_pid();               
  
    while(pid_check(p->pid)==1)             
    {
        sleep(5);                            
        printf("\n%d: Fetching pid...\n",p->sno);   
        p->pid = allocate_pid();             
    }
    display();                           
    p->sl_time = set_sleep_time();         
    printf("\n%d: pid = %d,sl_time = %d\n",p->sno,p->pid,p->sl_time);
    printf("\n%d - %d: Entered Sleep time...\n",p->sno,p->pid);
    sleep(p->sl_time);                                                  
    printf("\n%d - %d: Exited Sleep time...\n",p->sno,p->pid);
    release_pid(p->pid);                                
    display();
}

int main()
{
    int i, no_of_threads;
    printf("Enter no of threads: ");
    scanf("%d",&no_of_threads);               
    printf("...program gonna start...\n");
  
    int x = allocate_map();                  
    if(x==0)                                  
        printf("Mapping allocated...\n");
    else
        printf("Problem in initializing statuses...\n");
  
    struct process pr[no_of_threads];                    
    pthread_t pr_threads[no_of_threads];              
  
    for(i=0;i<no_of_threads;i++)
    {
        pr[i].sno = i;                                 
        pthread_create(&pr_threads[i],NULL,thread_fun,&pr[i]);          
    }
  
    for(i=0;i<no_of_threads;i++)              
    {
        pthread_join(pr_threads[i],NULL);                    
    }
  
    printf("\n...Program terminated successfully...\n");
}
