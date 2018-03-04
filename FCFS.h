#include "structura.h"

#ifndef FCFS
#define FCFS

void tick_FCFS(queue **running, queue **ready)
{
	if (empty(*running) == 1)
	{
		(*running) -> time --;
		if ((*running) -> time == 0)
		{
			dequeue(running);
			if (empty(*ready) == 1)
			{
				enqueue(running, (*ready) -> nume, (*ready) -> time, (*ready) -> priority);
				dequeue(ready);
			}
		}
	}
	else
		if (empty(*ready) == 1)
		{
			enqueue(running, (*ready) -> nume, (*ready) -> time, (*ready) -> priority);
			dequeue(ready);
		}
}

void wait_FCFS(queue **waiting, queue **running)
{
	if (empty(*running) == 1)
	{
		enqueue(waiting, (*running) -> nume, (*running) -> time, (*running) -> priority);
		dequeue(running);
	}
}

void event_FCFS(char buffer[101], queue **waiting, queue **ready)
{
	int i = 2;
	int j = 3;
	char name[22];
	while (buffer[j] >= '0' && buffer[j]<= '9')
		j++;
	strncpy(name, buffer + i, j-i);
	name[j-i] = '\0';
	search_and_pop(waiting, ready, name);
}

void FCFS_function(FILE *in, FILE *out)
{
	int k;
	char buffer[101];
	queue *ready;
	queue *running;
	queue *waiting;
	init(&ready);
	init(&running);
	init(&waiting);
	fscanf(in, "%d", &k);
	while (fgets(buffer,100, in) != NULL)
	{
		if (buffer[0] == 'a')
		{
			add_proces(buffer, &ready);
			tick_FCFS(&running, &ready);
		}
		if (buffer[0] == 'm' && buffer[1] == 'a')
		{
			madd_proces(buffer, &ready);
			tick_FCFS(&running, &ready);
		}
		if (buffer[0] == 's')
		{
			if (empty(running) == 1)
			{
				fprintf(out, "%s", running -> nume);
				fprintf(out, " %d", running -> time);
			}
			fprintf(out, "\n");
		}
		if (buffer[0] == 'w')
		{
			wait_FCFS(&waiting, &running);
			tick_FCFS(&running, &ready);
		}
		if (buffer[0] == 'e')
		{
			event_FCFS(buffer, &waiting, &ready);
			tick_FCFS(&running, &ready);
		}
		if (buffer[0] == 't')
		{
			tick_FCFS(&running, &ready);
		}
	}
	free_queue(&ready);
	free_queue(&running);
	free_queue(&waiting);
}

#endif