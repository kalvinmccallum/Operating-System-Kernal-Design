/*
Kalvin McCallum
01879187
EECE 4811 - Operating System and Kernel Design
The purpose of this program is to implement the fundamental requirements detailed in part 1 of assignment 3.
*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<signal.h>

// global variable, all threads can acess
int N;
int* ptr;
int memorySize = 0;
int memoryAllocated = 0;
int users_memory[6] = {128, 256, 512, 1024, 2048, 4096};
int user_memory_index = 0;
int MAX_SIZE = 2000 * sizeof(int);

void* thread(void* arg);          // thread function
void* memory_malloc();      // memory allocation
void* memory_free(int memSize);        // memory deallocation

pthread_mutex_t mutx;          // mutex

char thread1[] = "User";
int state1; 

int main(int argc, char** argv)
{
    ptr = (int *)malloc(MAX_SIZE);
    pthread_t t1;
    void* thread_result;
    
    printf("Enter number of Users: ");
    scanf("%i", &N);
   
    state1 = pthread_mutex_init(&mutx, NULL); // mutex initialization

    if (state1 != 0){
        puts("Error mutex initialization!!");
        }

    //Creates User threads
    for (int i = 0; i < N; i++) {
        pthread_create(&t1, NULL, thread, &thread1);
    }

    // Waiting for User threads to terminate
    for (int i = 0; i < N; i++) {
        pthread_join(t1, &thread_result);
    }

    pthread_mutex_destroy(&mutx);   // destroy mutex
    
    return 0;
}

// Thread function
void* thread(void* arg){
    pthread_mutex_lock(&mutx);
    
    if (state1 == 0) {
    printf("I am thread %ld going to sleep \n", pthread_self());
    sleep(2);
    printf("I am thread %ld waking-up \n",pthread_self());
    memory_malloc();
    } 
    
    pthread_mutex_unlock(&mutx);
}

// Memory allocation function
void* memory_malloc() {
    memorySize = users_memory[user_memory_index % 6];
    memoryAllocated += memorySize;
    
    if (memoryAllocated < MAX_SIZE) {
        *ptr += memorySize;
        user_memory_index++;
    }
    
    else {
        memoryAllocated -= memorySize;
        memoryAllocated -= users_memory[(user_memory_index--) % 6];
        memory_free(memorySize);
    }
    
}

// Memory deallocation function
void* memory_free(int memSize) {
    int deallocation = 0;
    int tempMemAllocated = memoryAllocated;
    
    while (tempMemAllocated > MAX_SIZE - memSize ){
          deallocation = 2;
          *ptr -= deallocation;
          }
          memory_malloc();
           
}

