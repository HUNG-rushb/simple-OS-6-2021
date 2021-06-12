#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) 
{
	/* TODO: put a new process to queue [q] */	
	if (q->size >= MAX_QUEUE_SIZE) 
		return;

	q->proc[q->size++] = proc;
}

struct pcb_t * dequeue(struct queue_t * q) 
{
	/* 
	 * return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	
	int i, idx = 0;
	if (q->size > 0)
	{
		// Find the highest-priority process
		for (i = 1; i < q->size; i++)
		{
			if (q->proc[idx]->priority < q->proc[i]->priority) 
				idx = i;
		}

		// Update remaining queue
		struct pcb_t* rem = q->proc[idx];
		for (i = idx + 1; i < q->size; i++)
		{
			q->proc[i-1] = q->proc[i];
		}

		q->size--;
		return rem;
	}

	return NULL;
}

