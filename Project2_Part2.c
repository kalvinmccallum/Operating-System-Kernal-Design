/*
Kalvin McCallum
01879187
EECE 4811 - Operating System and Kernel Design

The purpose of this program is to implement the fundamental requirements detailed in part 1
of assignment 2. This file functions by implementing multithreading on a Linux based system
to facilitate a provider/buyer relationship. The C based code leverages a buffer, mutex,
semaphore, and threads in a process to provide and buy integer items without thread
interference. The Total number of provider threads is one while the total number of buyer
threads is six.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<signal.h>

#define BUFFER_SIZE 260
typedef int buffer_item;

buffer_item buffer[BUFFER_SIZE];

// global variable, all threads can acess
int provider_counter = 0;
int buyer_counter = 0;
int N;


void *thread_Insert(void *arg);	// function for sending
void *thread_Remove(void *arg);	// function for receiving

sem_t bin_sem;	// semaphore
pthread_mutex_t mutx;	// mutex

char thread1[]="Provider";
char thread3[]="Buyer";

int main(int argc, char **argv)
{
  pthread_t t1, t3;
  void *thread_result;
  //Local variables
  int state1, state2;
  
  printf("Enter number of Buyer threads: ");
  scanf("%i", &N);

  state1 = pthread_mutex_init(&mutx, NULL);//mutex initialization
  state2 = sem_init(&bin_sem, 0 ,0);//semaphore initialization, first value = 0

  if(state1||state2!=0)
    puts("Error mutex & semaphore initialization!!!");

  //Creates one provider threads
  pthread_create(&t1, NULL, thread_Insert, &thread1);
  
  
  //Creates six buyer threads
  for(int i = 0; i < N; i++){
    pthread_create(&t3, NULL, thread_Remove, &thread3);
  }

  // Waiting provider thread to terminate
  pthread_join(t1, &thread_result);
 
  
  // Waiting buyer threads to terminate
  for(int i = 0; i < N; i++){
  pthread_join(t3, &thread_result);
  }

  sem_destroy(&bin_sem);	// destroy semaphore
  pthread_mutex_destroy(&mutx);	// destroy mutex
  
  return 0;
}

//Provider function
void *thread_Insert(void *arg)
{
for(int i = 0; i < N; i++){
    pthread_mutex_lock(&mutx);
    buffer[provider_counter] = provider_counter;
    provider_counter++;
    printf("%s provided %d to buffer\n", (char*)arg, provider_counter);
    sem_post(&bin_sem);	// semaphore to increase
    pthread_mutex_unlock(&mutx);
    }
}

//Buyer function
void *thread_Remove(void *arg){
    sem_wait(&bin_sem);	//decrease index_counter
    pthread_mutex_lock(&mutx);
    sleep(1);
    buffer[buyer_counter++] = 0;
    buyer_counter++;
    printf("%s bought %d from buffer\n", (char*)arg, buyer_counter);
    pthread_mutex_unlock(&mutx);
    
}

