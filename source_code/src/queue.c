#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */	

	// in queue.h
	if (q->size < MAX_QUEUE_SIZE)
	{
		// add process to queue
		q->proc[q->size] = proc;
		q->size++;
	}
	// else
	// {
	// 	return;
	// }
}

struct pcb_t * dequeue(struct queue_t * q) {
	/* TODO: return a pcb whose prioprity is the highest
	  in the queue [q] and remember to remove it from q */
	
	// if (!empty(q))
	if (q->size != 0)
	{
		// return process
		struct pcb_t* temp_process = NULL;

		// take the largest priority
		int max_priority = 0;
		int max_idx = 0;

		int i;
		for(i = 0; i < q->size; ++i)
		{
			if(q->proc[i]->priority > max_priority)
			{
				// chosen process
				temp_process = q->proc[i];

				// update new highest priority
				max_priority = temp_process->priority;

				// mark need-to-change-from-here index
				max_idx = i;
			}	
		}
		
		// from mark of need-to-change-from-here index
		// update the remaining queue
		for(i = max_idx; i < q->size - 1; ++i)
			q->proc[i] = q->proc[i+1];

		// last process is NULL
		q->proc[q->size - 1] = NULL;

		// Sreduce size
		--q->size;

		return temp_process;
	}

	return NULL;
}

