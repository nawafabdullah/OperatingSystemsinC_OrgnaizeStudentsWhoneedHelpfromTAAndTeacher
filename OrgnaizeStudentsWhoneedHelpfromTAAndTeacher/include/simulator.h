#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#ifndef SIMULATOR_H
#define SIMULATOR_H


#define SEM_TA_NAME "/TA"
#define SEM_STUDENT_NAME "/STUDENT"


/*
 * Following global variables will be necessary to declare in simulator.c file to implement simulator.h
 *
 */

// the numeric id of each student
int student_id[NUMBER_OF_STUDENTS];

// the thread identifier for TA thread
pthread_t ta;

// the thread identifiers for the STUDENT threads
pthread_t students[NUMBER_OF_STUDENTS];

// the STUDENT semaphore on which the TA will wait and be waked up 
sem_t* students_sem;

// the TA semaphore on which the students will wait and be waked up
sem_t* ta_sem;

// the mutex lock for the shared queue
pthread_mutex_t mutex_lock_ws;

/*
 * End of global variable declarations
 *
 */


void init();
//Initializes pthread mutex lock
//Opens both STUDENT and TA semaphores
//Initializes all students id

void cleanup();
//Destroys pthread mutex lock
//Unlinks both STUDENT and TA semaphores

void create_students();
//Creates all STUDENT threads

void create_ta();
//Creates TA thread



int main();
//Calls init()
//Calls create_ta()
//Calls create_students()
//Joins on and cancels other threads as necessary
//Calls cleanup();


#endif


