#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef structura
#define structura

typedef struct nod{

	char nume[22];
	int time;
	int priority;
	int exit;
	int wait;
	struct nod *next;
}queue;

/* Functia care initializeaza o coada */
void init(queue **head)
{
	*head = NULL;
}

/* Functie care verifica daca o coada este vida */
int empty(queue* head)
{
	if (head == NULL)
		return 0;
	return 1;
}

//Functie de adaugare a unui proces in coada
void enqueue(queue **head, char nume[22], int time, int priority)
{
	queue *new;
	queue *aux;
	new = (queue*)calloc(1,sizeof(queue));
	aux = *head;
	new -> time = time;
	new -> priority = priority;
	strcpy(new -> nume, nume);
	if ((*head) == NULL)
	{
		*head = new;
		new -> next = NULL;
	}
	else
	{
		new -> next = NULL;
		while (aux -> next != NULL)
			aux = aux -> next;
		aux -> next = new;
	}
}

/*Functie de adaugare a unui proces in coada pentru BONUS, adaugand si valorile
campurilor exit si wait*/
void enqueue_bonus(queue **head, char nume[22], int time, int priority, int exit, int wait)
{
	queue *new;
	queue *aux;
	new = (queue*)calloc(1,sizeof(queue));
	aux = *head;
	new -> time = time;
	new -> priority = priority;
	new -> exit = exit;
	new -> wait = wait;
	strcpy(new -> nume, nume);
	if ((*head) == NULL)
	{
		*head = new;
		new -> next = NULL;
	}
	else
	{
		new -> next = NULL;
		while (aux -> next != NULL)
			aux = aux -> next;
		aux -> next = new;
	}
}

//Functie de eliminare a unui proces
void dequeue(queue **head)
{
	queue *aux;
	aux = *head;
	if ((*head) == NULL)
	{
		printf("Coada vida\n");
		return;
	}
	*head = aux -> next;
	free(aux);
}

/*Functie folosita pentru comanda event: aceasta cauta in waiting procesul cu
numele dat in comanda si il adauga in ready*/
void search_and_pop(queue **waiting, queue **ready, char name[22])
{
	queue *aux;
	aux = *waiting;
	if (strcmp((*waiting) -> nume, name) == 0)
	{
		enqueue(ready, (*waiting) -> nume, (*waiting) -> time, (*waiting) -> priority);
		dequeue(waiting); 
	}
	else
	{
		while (strcmp(aux -> next-> nume, name))
			aux = aux -> next;
		if (strcmp(aux -> next -> nume, name))
			return;
		enqueue(ready, aux -> next -> nume, aux -> next -> time, aux -> next -> priority);
		queue *p;
		p = aux -> next;
		aux -> next = p -> next;
		free(p);
	}
}

//Functie folosita pentru comanda event(BONUS)
void search_and_pop_waiting_bonus(queue **waiting, queue **ready, char name[22])
{
	queue *aux;
	aux = *waiting;
	if (strcmp((*waiting) -> nume, name) == 0)
	{
		enqueue_bonus(ready, (*waiting) -> nume, (*waiting) -> time, (*waiting) -> priority, (*waiting) -> exit, (*waiting) -> wait);
		dequeue(waiting); 
	}
	else
	{
		while (strcmp(aux -> next-> nume, name))
			aux = aux -> next;
		enqueue_bonus(ready, aux -> next -> nume, aux -> next -> time, aux -> next -> priority, aux -> next -> exit, aux -> next -> wait);
		queue *p;
		p = aux -> next;
		aux -> next = p -> next;
		free(p);
	}
}

/*Functie care returneaza cel mai scurt timp necesar pentru rulare al 
proceselor din coada ready*/
int time_min(queue *ready)
{
	int mini = ready -> time;
	ready = ready -> next;
	while (ready != NULL)
	{
		if (ready -> time < mini)
			mini = ready -> time;
		ready = ready -> next;
	}
	return mini;
}

/*Functie care adauga in running procesul cu cel mai scurt timp necesar pentru
rulare din ready*/
void search_and_pop_time(queue **ready, queue **running, int t)
{
	queue *aux;
	aux = *ready;
	if ((*ready) -> time == t)
	{
		enqueue(running, (*ready) -> nume, (*ready) -> time, (*ready) -> priority);
		dequeue(ready); 
	}
	else
	{
		while (aux -> next-> time != t)
			aux = aux -> next;
		enqueue(running, aux -> next -> nume, aux -> next -> time, aux -> next -> priority);
		queue *p;
		p = aux -> next;
		aux -> next = p -> next;
		free(p);
	}
}

/* Functie care returneaza prioritatea maxima a proceselor din ready */
int priority_max(queue *ready)
{
	int maxi = ready -> priority;
	ready = ready -> next;
	while (ready != NULL)
	{
		if (ready -> priority > maxi)
			maxi = ready -> priority;
		ready = ready -> next;
	}
	return maxi;
}

/* Functie care cauta in ready procesul cu prioritatea maxima si il adauga
in running */
void search_and_pop_priority(queue **ready, queue **running, int p)
{
	queue *aux;
	aux = *ready;
	if ((*ready) -> priority == p)
	{
		enqueue(running, (*ready) -> nume, (*ready) -> time, (*ready) -> priority);
		dequeue(ready); 
	}
	else
	{
		while (aux -> next-> priority != p)
			aux = aux -> next;
		enqueue(running, aux -> next -> nume, aux -> next -> time, aux -> next -> priority);
		queue *p;
		p = aux -> next;
		aux -> next = p -> next;
		free(p);
	}
}


/* Functie care cauta in ready procesul cu prioritatea maxima si il adauga
in running (folosita pentru BONUS) */
void search_and_pop_bonus(queue **ready, queue **running, int p)
{
	queue *aux;
	aux = *ready;
	if ((*ready) -> priority == p)
	{
		enqueue_bonus(running, (*ready) -> nume, (*ready) -> time, (*ready) -> priority, (*ready) -> exit, (*ready) -> wait);
		dequeue(ready); 
	}
	else
	{
		while (aux -> next-> priority != p)
			aux = aux -> next;
		enqueue_bonus(running, aux -> next -> nume, aux -> next -> time, aux -> next -> priority, aux -> next -> exit, aux -> next -> wait);
		queue *p;
		p = aux -> next;
		aux -> next = p -> next;
		free(p);
	}
}

/* Functie care adauga un proces in ready */
void add_proces(char buffer[101], queue **ready)
{
	int time = 0;
	int priority = 0;
	int i,j;
	char name[22];
	i = 2;
	j = 2;
	/* Parcurgem bufferul pana la primul spatiu de dupa nume */
	while (buffer[j] != ' ')
		j++;
	/* Copiem numele procesului din buffer*/
	strncpy(name, buffer + i, j-i);
	name[j-i] = '\0';
	j++;
	i = j;
	/* Parcurgem bufferul pana la primul spatiu de dupa timp */
	while (buffer[j] != ' ')
		j++;
	/* Daca avem un timp de o cifa, o convertim direct intr-un numar */
	if ((j - i) == 1)
	{
		time = buffer[i]- '0';
		i++;
	}
	/*Prelucram timpul procesului din buffer astfel incat sa obtinem un numar
	cu ajutorul unei structuri repetitive while*/
	else
	{
		while (j-i)
		{
			time = time * 10 + (buffer[i] - '0');
			i++;
		}
	}
	j++;
	/* Vom proceda la fel si cu prioritatea */
	while (buffer[j+1] >= '0' && buffer[j+1] <= '9')
		j++;
	if (j == i - 1)
		priority = buffer[j]- '0';
	else
	{
		while (j-i)
		{
			priority = priority * 10 + (buffer[i+1] - '0');
			i++;
		}
	}
	/* Adaugam procesul in ready */
	enqueue(ready, name, time, priority);
	
}

/* Functie care adauga mai multe procese in ready */
/* Aceasta functie este asemenea celei anterioare (add_proces), doar ca
aceasta se va repeta pana cand ajunge la finalul bufferului */
void madd_proces(char buffer[101], queue **ready)
{
	int i = 3;
	int j = 3;
	int time, priority;
	char name[22];
	while (j < strlen(buffer))
	{
		time = 0;
		priority = 0;
		while (buffer[j] != ' ')
			j++;
		strncpy(name, buffer + i, j-i);
		name[j-i] = '\0';
		j++;
		i = j;
		while (buffer[j] != ' ')
			j++;
		if ((j - i) == 1)
		{
			time = buffer[i]- '0';
			i++;
		}
		else
			while (j-i)
			{
				time = time * 10 + (buffer[i] - '0');
				i++;
			}
		j++;
		while (buffer[j+1] >= '0' && buffer[j+1] <= '9')
		j++;
		if ((j - i) == 1)
		{
			priority = buffer[j]- '0';
			i++;
		}
		else
			while (j-i)
			{
				priority = priority * 10 + (buffer[i+1] - '0');
				i++;
			}
		i+=2;
		j+=2;
		enqueue(ready, name, time, priority);
	}
}

/* Functia aceasta elibereaza o coada */
void free_queue(queue **head)
{
	while(*head != NULL)
		dequeue(head);
}

#endif