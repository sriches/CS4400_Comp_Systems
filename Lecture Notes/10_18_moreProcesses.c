


/*
			 ------> 'c' ------
			 |				  .
			 |				  .
			 |				  .
			 |				  V
	-------- F --------------(w)-------> '1'----


	1 possible output: c,1

*/
int main() {
	pid_t pid;
	int status;

	pid = Fork();
	if(pid==0) {
		printf("c\n");
		return 1;
	}

	Waitpid(pid, &status, 0);
	printf("%d\n", WEXITSTATUS(status));

	return 0;
}






/*
			 ------> 'c' -----> (w) --------
			 |				  				|
			 |				  				|
			 |				  				|
			 |				  				V
	-------- F -----------------------------(w)-------> 0


	outputs: 0

	when running, OS knows it will get stuck, so it reports an error. Then prints 0.

*/
int main() {
	pid_t pid;
	int status;

	pid = Fork();
	if(pid==0) {
		printf("c\n");
		// SAME as above, but remove this return		return 1;
	}

	Waitpid(pid, &status, 0);
	printf("%d\n", WEXITSTATUS(status));

	return 0;
}





/*
			 ------> 'c' -----> (w)
			 |	  				|
			 |	  				|
			 |	  				|
			 |	  				V
	-------- F ----------------(w)-------> 0


	outputs: 0


*/
int main() {
	pid_t pid;
	int status;

	pid = Fork();
	if(pid==0) {
		printf("c\n");
		// SAME as above, but remove this return		return 1;
	}else {

		Waitpid(pid, &status, 0);
		printf("%d\n", WEXITSTATUS(status));
	}
	return 0;
}








/*
			 ------> 'c1' -- exit 1 --------
			 |				  				|                  
			 |				 --------------------> c2 ---> exit 2	  		
			 |				 | 				|                 |
			 |				 | 				V                 | 
	-------- F ------------- F ------------(w)-----> '1' --->(w) -- '2'----> 0


	outputs: 

	c1 c2 1 2
	c2 c1 1 2
	c1 1 c2 2

	

*/
int main() {
	pid_t pid1, pid2;
	int status;

	pid1 = Fork();
	if(pid1==0) {
		printf("c1\n");
		return 1;
	}


	pid2 = Fork();
	if(pid2==0) {
		printf("c2\n");
		return 2;
	}


	Waitpid(pid1, &status, 0);
	printf("%d\n", WEXITSTATUS(status));
	fflush(NULL);

	Waitpid(pid2, &status, 0);
	printf("%d\n", WEXITSTATUS(status));
	fflush(NULL);


	return 0;
}





/*
			 ------> 'c1' -- exit 1 --------o-----------------------------------------------------------------
			 |				  				|                                                                |  
			 |				 ---->'c2'------|-----------> exit 2 --------------------------------------------|
			 |				 | 				|                 |                                              |
			 |				 | 				V                 |                                              |
	-------- F ------------- F ------------(w)-----> '1' OR '2' (depending on if c1 or c2 finishes first)--->(w) -- '1' OR 2', from the OTHER one that didn't finish earilier-
                                  c1 OR c2 can converge here

	outputs: 

	c1 c2 1 2
	c1 1 c2 2
	c2 c1 1 2
	c1 c2 2 1
	c2 c1 2 1
	c2 2 c1 1

	

*/
int main() {
	pid_t pid1, pid2;
	int status;

	pid1 = Fork();
	if(pid1==0) {
		printf("c1\n");
		return 1;
	}


	pid2 = Fork();
	if(pid2==0) {
		printf("c2\n");
		return 2;
	}


	Waitpid(-1, &status, 0);
	printf("%d\n", WEXITSTATUS(status));
	fflush(NULL);

	Waitpid(-1, &status, 0);
	printf("%d\n", WEXITSTATUS(status));
	fflush(NULL);


	return 0;
}





/*	FROM THE QUIZ


                        .-----> a ------> d ----.
                        |                       | 
                        |                       |        
                        |                       |          
                        |                       |                  
			 .--------- F -------------------- (w) -----> b ------> d ------> return
			 |				  		
			 |				 
			 |				  		
			 |				  		
	-------- F ---------------> c -----> exit
*/
	




int main(int argc, char **argv)
{
	//int Execve(char * prog, char **argv, char **env);

	int status;

	char *a[6];
	a[0] = "/bin/gcc"
	a[1] = "-O2"
	a[2] = "-Wall"
	a[3] = argv[1];
	a[4] = "csapp.c";
	a[5] = NULL

	int pid = Fork();

	if(pid == 0)
	{
		Execve(a[0], a, environ);
		exit(1); // Shouldn't get here. Exit with failure.
	}
	

	Waitpid(pid, &status, 0);
	
	char *b[2];
	b[0] = "a.out";
	b[1] = NULL

	Execve(b[0] b, eniron);

	return 0;
}



