/* 
* Nawaf Alharbi
* Operating Systems
*/ 

#include "student.h"
#include "queue.h"
#include "ta.h"
#include "simulator.h"


void programming(int studentid, int programingtime)
{
  //Print message indicating the student id and programming time	
  printf ("\t\t\tstudent %i will be programming for %i seconds\n", studentid, programingtime);
  //Simulate programming by calling sleep() system call.
  sleep (programingtime);
}

void *run_student(void *param)
{
  //Start with UNKNOWN state    	
  student_state student_st = UNKNOWN; 
  int student_id = *(int*)param; //type cast the paramerter, convert it to int and store id 
  int num_of_loops = 0;
  //Check the number of loops this student has completed.
  //If number of loops does not exceed MAX_NUMBER_OF_LOOPS_OF_A_STUDENT and the state is not WAITING
  while (num_of_loops < MAX_NUMBER_OF_LOOPS_OF_A_STUDENT)
  {
    if (student_st != WAITING)
    {
      int programming_time = (rand() % MAX_PROGRAM_TIME) + 1 ; 
      //starts programming for a random amount of time by calling programming()
      programming(student_id, programming_time);
      //sets the sate PROGRAMMING.
      student_st = PROGRAMMING; 			
    }  
    //After finishing the programming, check the current waiting queue size by calling queue_size() from queue.h.					
    //Guard all queue operations using pthread_mutex locking and unlocking mechanism			
    pthread_mutex_lock (&mutex_lock_ws); //lock next operation on queue to get accurate size and do enqueue safely   
	int q_size = queue_size();
	pthread_mutex_unlock (&mutex_lock_ws);    
	//If the queue size is less than NUMBER_OF_SEATS, enqueues itself into the queue 
    //by calling enqueue() from queue.h and sets the state WAITING.
    if (q_size < NUMBER_OF_SEATS) 
    {
		pthread_mutex_lock (&mutex_lock_ws);
		enqueue(student_id);
		//sem_post(ta_sem); //in case TA is sleeping
		//appropriately. Make sure mutex lock does not cause deadlock in your assignment.
        q_size = queue_size();
		pthread_mutex_unlock (&mutex_lock_ws); // - end of operations on queue - unlock mutex
		//Notify the TA using a semaphore that this student is waiting to get help.	
		student_st = WAITING; 	
		//Wait for the TA to help using a semaphore.
		sem_post(ta_sem);	
		printf ("\t\tstudent <%i> takes a seat to get help, total %i student(s) waiting for help \n", student_id, q_size);
	
		//When TA starts helping, set the state to GETTING_HELP.
		//run_ta(param); 				
		sem_wait(students_sem);			            
		student_st = GETTING_HELP;
		printf("\t\t\tstudent <<<%i>>> is GETTING HELP\n",student_id); 
		//Keep track of the number of loops this student has completed.
		//If the the queue size is not less than NUMBER_OF_SEATS, loop back but don't
		//increment the number of loop counter.		
		num_of_loops++; 
   } 
 }
	pthread_exit(NULL);
}
