/* 
* Author: Kalvin McCallum
* Student ID: 01879187
* Class: EECE 4811 - Operating Systems and Kernel Design
* Last Modified: 09/22/2022
* Purpose: 
* The purpose of this program is to repeatedly create a sub-process using the fork Linux command. 
* The program will will wait until the sub-process is completed before it terminates.
* Each sub-process can be regarded as a child process and will print Child Running to the terminal.
* The child process then spawns a sub-program called the chandchild using the Linux command execve.
* After Child Running is printed to the terminal and the grandchild program has run, the program will call the exit command to exit the sub-process.
*/

//Libraries nedded for this program
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdbool.h>

int main(int argc, char **argv){ //Beginning of the main function
	
	int res; //Integer variable declaration
	bool conditional = true; //Boolian variable declaration and initialization
	
	while(conditional){
		
		res = fork();
		
		if(res < 0){
			perror("fork");//Produces a message on standard error describing the fork error
			conditional = false; //Changes while loop condition to false and exits while loop
			exit(0); //Exit while loop
		}
		
		else if(res == 0){ //Checks if child process is running
			printf("Child Running \n"); //Output to illustrate that the child process is running
			char command[] = "./a.out"; //Character declaration and initialization
			char *args[] = {"a.out"}; //Character declaration and initialization
			char *argevn[] = {NULL}; //Character declaration and initialization
			res = execve(command,args,argevn); //Setting res variable to execve function with three new character arguements
			
			if(res == -1){
				perror("execv"); //Prints process error
				exit(2); //Exits child process
			}
		}
		
		else{
			int child_pid = res; //Sets child process idea variable
			waitpid(child_pid, NULL, 0); //Waits until child process is terminated
		}
	}
}//end of the main function
