#include "structura.h"

#ifndef RR
#define RR

void wait_RR(queue **waiting, queue **running)
{
	if (empty(*running) == 1)
	{
		enqueue(waiting, (*running) -> nume, (*running) -> time, (*running) -> priority);
		dequeue(running);
	}
}

void event_RR(char buffer[101], queue **waiting, queue **ready)
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

void RR_function(FILE *in, FILE *out, int cuanta)
{
	int clock = 0;
	char buffer[101];
	queue *ready;
	queue *running;
	queue *waiting;
	init(&ready);
	init(&running);
	init(&waiting);
	while (fgets(buffer,100, in) != NULL)
	{
		if (buffer[0] == 'a')
		{
			add_proces(buffer, &ready);
			buffer[0] = 't';
		}
		if (buffer[0] == 'm' && buffer[1] == 'a')
		{
			madd_proces(buffer, &ready);
			buffer[0] = 't';
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
			wait_RR(&waiting, &running);
			buffer[0] = 't';
		}
		if (buffer[0] == 'e')
		{
			event_RR(buffer, &waiting, &ready);
			buffer[0] = 't';
		}
		if (buffer[0] == 't')
		{
			
			if (empty(running) == 1)
			{
				running -> time --;
				clock ++;
				if (running -> time == 0)
				{
					dequeue(&running);
					if (empty(ready) == 1)
					{
						clock = 0;
						enqueue(&running, ready -> nume, ready -> time, ready -> priority);
						dequeue(&ready);
					}
				}
				if (clock == cuanta)
				{
					enqueue(&ready, running -> nume, running -> time, running -> priority);
					dequeue(&running);
					if (empty(ready) == 1)
					{
						clock = 0;
						enqueue(&running, ready -> nume, ready -> time, ready -> priority);
						dequeue(&ready);
					}
				}
			}
			else
				if (empty(ready) == 1)
				{
					clock = 0;
					enqueue(&running, ready -> nume, ready -> time, ready -> priority);
					dequeue(&ready);
				}
		}
	}
	free_queue(&ready);
	free_queue(&running);
	free_queue(&waiting);
}

#endif