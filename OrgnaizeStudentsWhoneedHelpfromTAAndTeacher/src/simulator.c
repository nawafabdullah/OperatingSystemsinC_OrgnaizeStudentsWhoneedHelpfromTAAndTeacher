/* 
* Nawaf Alharbi
* Operating Systems
*/ 

#include "student.h"
#include "ta.h"
#include "simulator.h"

void init()
{
  //Initializes pthread mutex lock	
  pthread_mutex_init(&mutex_lock_ws,NULL);
  sem_unlink(SEM_STUDENT_NAME);
  sem_unlink(SEM_TA_NAME);
  //Opens both STUDENT and TA semaphores
  students_sem = sem_open(SEM_STUDENT_NAME, O_CREAT,0600,0);
  ta_sem = sem_open(SEM_TA_NAME, O_CREAT,0600,0);
  if (students_sem == SEM_FAILED) //error check for semaphore open 
  {
      printf("COULD NOT CREATE STUDENT SEMAPHORE");
      return; 
  }
  //Initializes all students id	
  for (int i=0; i<NUMBER_OF_STUDENTS; i++)
  {
    student_id[i] = i+1;
  }
}
void cleanup()
{
  //Destroys pthread mutex lock
  pthread_mutex_destroy(&mutex_lock_ws);
  //Unlinks both STUDENT and TA semaphores
  sem_unlink(SEM_STUDENT_NAME);
  sem_unlink(SEM_TA_NAME);
}
void create_students()
//Creates all STUDENT threads
{
  for (int i = 0; i < NUMBER_OF_STUDENTS; i++)
  {
    pthread_create(&students[i], NULL, run_student, (void *)&student_id[i]);
  }		
}
void create_ta()
{
  //Creates TA thread
  pthread_create(&ta, NULL, run_ta, (void *)NULL); 
}

int main()
{
  //Calls init()	
  init();
  //Calls create_ta()
  create_ta();
  //Calls create_students()
  create_students();
  //pthread_join(ta,NULL); 
  //Joins on and cancels other threads as necessary
  for(int i = 0; i< NUMBER_OF_STUDENTS; i++)
  {
    pthread_join(students[i],NULL);    
  }
  pthread_cancel(ta);
  //pthread_cancel(student);
  
  //Calls cleanup();
  cleanup(); 
  return 1;
}


