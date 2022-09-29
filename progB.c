/* 
* Author: Kalvin McCallum
* Student ID: 01879187
* Class: EECE 4811 - Operating Systems and Kernel Design
* Last Modified: 09/22/2022
* Purpose: 
* The purpose of this program is to repeatedly create a sub-process using the fork Linux command. 
* The program will will wait until the sub-process is completed before it terminates.
* Each sub-process can be regarded as a child process and will print Child Running to the terminal.
* The child process then spawns a sub-program called the grandchild using the Linux command execve.
* After Child Running is printed to the terminal and the grandchild program has run, the program will call the exit command to exit the sub-process.
*/

//Libraries nedded for this program
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdbool.h>

int main(int argc, char **argv){ //Beginning of main function
printf("I am the grandchild \n"); //Output to illustrate that the grandchild process is running
exit(0);
}//end of the main function
