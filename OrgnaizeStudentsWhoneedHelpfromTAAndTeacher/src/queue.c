/* 
* Nawaf Alharbi
* Operating Systems
*/ 

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

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
st_node *head = NULL; 
int q_size = 0;

void enqueue(int st_id)
//Adds the student id at the tail of the queue.
{
  st_node *tmp = (st_node*)malloc(sizeof(st_node)); // create storage space to store task temproraly  
  tmp->id = st_id; // assign task holder in struct to task that was passed  
  tmp->next = NULL;
  if (head == NULL) // -empty list- check if head is empty. if it is, give it the data that was passed 
  {
     head = tmp; // 
  } else
  {
    st_node *p; //follow links to end of list -look for the end of the list - Declared here to avoid creating space if head is empty  
    p = head; 

    while (p->next != NULL)
    {
      p = p->next; 
    }
    p->next = tmp;
    tmp->prev = p;
  }
  q_size++;  
}


int dequeue()
//Removes a student id from the head of the queue
{

  st_node *tmp = head;
  int deleted_st_ID; // create a place holder for the ID of student to be deleted to return it upon exiting the function
  if (tmp != NULL) // is the list empty?? if it is, inform user and return 
  {
	  deleted_st_ID = tmp -> id; // create a place holder for the ID of student to be deleted to return it upon exiting the function 
	  head = tmp->next; // make head point ath next element in the list
	  free (tmp);
	  q_size--;
  }
  return deleted_st_ID; 

} 
  
int queue_size()
//Returns the current size of the queue.
{
  return q_size; 
}

