/**
 * Implementation of this header file will be an implementation of Queue abstract
 * data type using a double-way-link-list.
 * When a student wants to wait to get help from the TA, it enqueues
 * itself into the queue. A student must check the queue size against the maximum number
 * of seats available in the TA office before it enqueues itself into the queue.
 * Queue itself is of unlimited size.
 * When the TA is ready to help a waiting student, it dequeues the student
 * from the queue.
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

typedef struct student {
	int id;
	struct student* prev;
	struct student* next;
} st_node;

void enqueue(int st_id);
//Adds the student id at the tail of the queue.

int dequeue();
//Removes a student id from the head of the queue

int queue_size();
//Returns the current size of the queue.

#endif
