/*
* Author: Kalvin McCallum
* Student ID: 01879187
* Class: EECE 4811 - Operating Systems and Kernel Design
* Last Modified : 09 / 22 / 2022
* Purpose:
* The purpose of this program is to take a single integer argument from the command line and create a set of 2*n processes.
* The program utilizes a for loop to iterate through the 2*n processes and print the process ID and process number of each process.
*/

//Libraries nedded for this program
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) //Beginning of main function
{
	int n, res; //Declares integer variables
	
	printf("Enter single integer argument:"); //Prints user prompt
	scanf("%d", &n); //Reads users response to prompt
	
	for(int i = 1; i <= 2*n; i++){
		res = fork();
		if (res < 0) {
			perror("fork");//Produces a message on standard error describing the fork error
			exit(0);
		}

		else if (res == 0) { //Checks if child process is running
			printf("I am %d of process %d\n", getpid(), i); //Prints current process ID and number
			exit(0); //Exits child process
		}
		else{
			int child_pid = res; //Sets child process idea variable
			waitpid(child_pid, NULL, 0); //Waits until child process is terminated
		}
	}
} //End of main function
