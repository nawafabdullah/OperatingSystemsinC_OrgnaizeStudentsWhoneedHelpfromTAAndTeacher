#ifndef TA_H
#define TA_H


#define MAX_HELP_TIME 5

/* 
 * Following external global variables needs to be declared in ta.c to implement ta.h
 */
//extern pthread_mutex_t mutex_lock_ws;
//extern sem_t* ta_sem;
//extern sem_t* students_sem;



void *run_ta(void *param);
//Do the followings in an infinite loop.

//Check the current waiting queue size by calling queue_size() from queue.h.

//If the the queue size is zero, wait for a student to show up using a semaphore.

//If the the queue size is greater than zero, notify the waiting student that

//the TA is ready to help using a semaphore.

//Wait for the student to come forward using a semaphore.

//When a student comes forward, dequeue the student by calling dequeue() from queue.h

//and help the student for a random time by calling help_student().

//Guard all queue operations using pthread_mutex locking and unlocking mechanism

//appropriately. Make sure mutex lock does not cause deadlock in your assignment.

void help_student(int helptime, int number);
//Print message indicating the student number and help time
//Simulate helping by calling sleep() system call.

#endif
