/* 
* Nawaf Alharbi
* Operating Systems
*/ 

#include "student.h"
#include "queue.h"
#include "ta.h"
#include "simulator.h"

void *run_ta(void *param)
{
	// do following in an infinite loop
  while (1)
  {
	
    //If the the queue size is zero, wait for a student to show up using a semaphore.
    pthread_mutex_lock(&mutex_lock_ws); //lock mutex to safely get size of queue  
    int q_size = queue_size();
	pthread_mutex_unlock(&mutex_lock_ws);

    if(q_size == 0)
    {
      //TA is ready to help using a semaphore.
      printf("TA will sleep until a student shows up ...\n");
      sem_wait(ta_sem);

    }
    //If the the queue size is greater than zero, notify the waiting student
    if(q_size > 0)
	{      			
      //When a student comes forward, dequeue the student by calling dequeue() from queue.h
      //and help the student for a random time by calling help_student().
      pthread_mutex_lock (&mutex_lock_ws); //lock mutex to safely get size of queue  
      int dequeued_id = dequeue();	
      int helping_time = (rand() % MAX_HELP_TIME) + 1;
      help_student(helping_time,dequeued_id);
      pthread_mutex_unlock(&mutex_lock_ws);

      sem_post(students_sem);
      //Guard all queue operations using pthread_mutex locking and unlocking mechanism
      //appropriately. Make sure mutex lock does not cause deadlock in your assignment.
    }
  }
}


void help_student(int helptime, int number)
{
  //Print message indicating the student number and help time
  printf ("TA is helping student <<%i>> for %i seconds\n", number, helptime);

  //Simulate helping by calling sleep() system call.
  sleep(helptime);
}
