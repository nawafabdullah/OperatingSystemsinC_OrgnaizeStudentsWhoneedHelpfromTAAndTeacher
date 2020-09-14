#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//#include <cstdlib>
#include <stdlib.h>

#ifndef STUDENT_H
#define STUDENT_H

// number of potential students
#define NUMBER_OF_STUDENTS 3

// the maximum number of times a student will loop through the simulation
#define MAX_NUMBER_OF_LOOPS_OF_A_STUDENT 5

// the maximum  time (in seconds) for a STUDENT to program 
#define MAX_PROGRAM_TIME 5

// the number of available seats to sit in for seeking help
#define NUMBER_OF_SEATS	2

//different states of a student
typedef enum {PROGRAMMING, WAITING, GETTING_HELP, UNKNOWN} student_state;

/*
 * Following external global variables will be needed to declare in student.c to implement student.h
 */
//extern pthread_mutex_t mutex_lock_ws;
//extern sem_t* ta_sem;
//extern sem_t* students_sem;


void programming(int studentid, int programingtime);
//Print message indicating the student id and programming time
//Simulate programming by calling sleep() system call.


void *run_student(void *param);
//Start with UNKNOWN state
//Check the number of loops this student has completed.
//If number of loops does not exceed MAX_NUMBER_OF_LOOPS_OF_A_STUDENT and the state is not
//WAITING, starts programming for a random amount of time by calling programming() and
//sets the sate PROGRAMMING.
//After finishing the programming, check the current waiting queue size by calling
//queue_size() from queue.h.
//If the the queue size is less than NUMBER_OF_SEATS, enqueues itself into the queue
//by calling enqueue() from queue.h and sets the state WAITING.
//Guard all queue operations using pthread_mutex locking and unlocking mechanism
//appropriately. Make sure mutex lock does not cause deadlock in your assignment.
//Notify the TA using a semaphore that this student is waiting to get help.
//Wait for the TA to help using a semaphore.
//When TA starts helping, set the state to GETTING_HELP.
//Keep track of the number of loops this student has completed.
//If the the queue size is not less than NUMBER_OF_SEATS, loop back but don't
//increment the number of loop counter.


#endif
