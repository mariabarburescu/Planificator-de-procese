#include "structura.h"

#ifndef Bonus
#define Bonus

void wait_Bonus(queue **waiting, queue **running)
{
	if (empty(*running) == 1)
	{
		(*running) -> exit = 0;
		(*running) -> wait ++;
		if ((*running) -> wait == 2)
		{
			(*running) -> priority ++;
			(*running) -> wait = 0;
		}
		enqueue_bonus(waiting, (*running) -> nume, (*running) -> time, (*running) -> priority, (*running) -> exit, (*running) -> wait);
		dequeue(running);
	}
}

void event_Bonus(char buffer[101], queue **waiting, queue **ready)
{
	int i = 2;
	int j = 3;
	char name[22];
	while (buffer[j] >= '0' && buffer[j]<= '9')
		j++;
	strncpy(name, buffer + i, j-i);
	name[j-i] = '\0';
	search_and_pop_waiting_bonus(waiting, ready, name);
}

void Bonus_function(FILE *in, FILE *out, int cuanta, int niv_priority)
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
			wait_Bonus(&waiting, &running);
			buffer[0] = 't';
		}
		if (buffer[0] == 'e')
		{
			event_Bonus(buffer, &waiting, &ready);
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
						search_and_pop_bonus(&ready, &running, priority_max(ready));
					}
				}
				if (clock == cuanta)
				{
					running -> exit ++;
					if (running -> exit == 2)
					{
						running -> priority --;
						running -> exit = 0;
						running -> wait = 0;
					}
					enqueue_bonus(&ready, running -> nume, running -> time, running -> priority, running -> exit, running -> wait);
					dequeue(&running);
					if (empty(ready) == 1)
					{
						clock = 0;
						search_and_pop_bonus(&ready, &running, priority_max(ready));
					}
				}
				if (empty(ready) == 1)
					if (priority_max(ready) > running -> priority)
					{
						enqueue_bonus(&ready, running -> nume, running -> time, running -> priority, running -> exit, running -> wait);
						dequeue(&running);
						search_and_pop_bonus(&ready, &running, priority_max(ready));
						clock = 0;
					}
			}
			else
				if (empty(ready) == 1)
				{
					clock = 0;
					search_and_pop_bonus(&ready, &running, priority_max(ready));
				}
		}
	}
	free_queue(&ready);
	free_queue(&running);
	free_queue(&waiting);
}

#endif