
#include<stdio.h>
#include<unistd.h>
#define MIN_PID 100
#define MAX_PID 1000
#define array_size MAX_PID - MIN_PID


int main()
{
	allocate_map();
	printf("\n After allocation\n");
	display();
	
}

int allocate_map()
{
	int i;
	for(i = 0; i < array_size; i++)
	{
		status_of_pid[i] = 0;
	}
}

int allocate_pid()
{
	int i;
	for(i = 0; i < array_size; i++)
	{
		if( status_of_pid[i] == 0)
		{
			status_of_pid[i] == 1;
			return i+100;
		}
	}
}

void release_pid()
{
	
}

