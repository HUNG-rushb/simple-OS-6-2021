
#include "queue.h"
#include "sched.h"
#include <pthread.h>

static struct queue_t ready_queue;
static struct queue_t run_queue;
static pthread_mutex_t queue_lock;

int queue_empty(void) {
	return (empty(&ready_queue) && empty(&run_queue));
}

void init_scheduler(void) {
	ready_queue.size = 0;
	run_queue.size = 0;
	pthread_mutex_init(&queue_lock, NULL);
}

struct pcb_t * get_proc(void) {
	/*TODO: get a process from [ready_queue]. 
	 * If ready queue is empty,
	 * push all processes in [run_queue] back to
	 * [ready_queue] and return the highest priority one.
	 * 
	 * Remember to use lock to protect the queue.
	 * */
	struct pcb_t * return_process = NULL;

	// Lock
	// http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Fp%2Fpthread_mutex_lock.html
	pthread_mutex_lock(&queue_lock);

	// if (empty(&ready_queue))
	if (ready_queue.size == 0)
	{
		// Copy loop
		for(int i = 0; i < MAX_QUEUE_SIZE; ++i)
		{
			// Copy back to ready_queue
			ready_queue.proc[i] = run_queue.proc[i];

			// Set run_queue to NULL
			run_queue.proc[i] = NULL;	
		}

		// Copy size to ready_queue
		ready_queue.size = run_queue.size;

		// run_queue's sizeis now 0
		run_queue.size = 0;
	}

	// Take the highest priority process
	return_process = dequeue(&ready_queue);

	// Unlock
	// http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Fp%2Fpthread_mutex_lock.html
	pthread_mutex_unlock(&queue_lock);

	return return_process;
}

void put_proc(struct pcb_t * proc) {
	pthread_mutex_lock(&queue_lock);
	enqueue(&run_queue, proc);
	pthread_mutex_unlock(&queue_lock);
}

void add_proc(struct pcb_t * proc) {
	pthread_mutex_lock(&queue_lock);
	enqueue(&ready_queue, proc);
	pthread_mutex_unlock(&queue_lock);	
}


