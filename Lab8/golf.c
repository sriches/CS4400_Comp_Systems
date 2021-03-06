#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
  int firstchild = fork();

  if( firstchild == 0)
  {
    // Do work here to fork to create target pstree diagram
    
    /* Target 1:  golf-+-golf
                       `-golf  */
        /*int pid1 = fork();
	if(pid1 != 0)
	{
	  fork();
	}
	*/


/* Target 2:  golf---golf-+-golf
                          `-golf
*/
    /*	int pid1 = fork();
	if(pid1 == 0)
	{
	  int pid2 = fork();
	  if(pid2 != 0)
	  {
	    fork();
	  }
	  }*/
	

 /* Target 3:  golf-+-golf-+-golf---golf
                    |      `-golf
		    |-golf---golf
		    `golf
 */
    int pid1;
    int pid2;
    int pid3;

	pid1 = fork();
	if(pid1 == 0)
	{
	  pid2 = fork();
	  if(pid2 != 0)
	  {
	    fork();
	  }else
	  {
	    fork();
	  }
	}else
	{
	  pid3 = fork();
	  

	  
	}













    // Put all calls to fork() above this line, and don't modify below.

    sleep(2); /* required so that execve will run before the process quits, don't do this sort of thing in real code */
    return 0;
  }
  else 
  {
    sleep(1); /* make it so child finishes forking before calling execve */


    // parent process calls execve on pstree

    char pid[20]; // This is where we will put the pid argument to the pstree execution
    char* args[] = {"/usr/bin/pstree", "-p" , pid, NULL};
    char* environ[] = {NULL};

    sprintf(pid, "%u", firstchild);
    execve( args[0], args, environ);
  }
}
