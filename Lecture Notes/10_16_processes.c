


// Will print 0 1  or 1 0
int main(){
	int x=0;
	if(Fork() == 0){
		printf("%d\n", x);
	}else {
		x++;
		printf("%d\n", x)
	}
}


// Will print 10,20 or 20,10
// For creates a copy of malloc, it is the same address, 
// but the process's view of address space is virtual
//
// For the most part, nothing is shared after a fork
int main(){
	int *x = malloc(sizeof(int));
	*x = 10;

	if(Fork() == 0){
		printf("%d\n", *x);
	}else {
		x = 20;
		printf("%d\n", x)
	}
}


/*

		  -------> c1 (exit)	
          | 
          | 
          |
		  |			----------> c2 ---------> p (exit)
          |         | 
          |         | 
	------F----------F


3! = 6 possible ways of printing output (all combinations of c1, c2, and p)

*/
int main() {
	if (Fork() == 0){
		printf("c1\n");
	}else {
		if(Fork() == 0)
			printf("c2\n");
	}else 
		printf("p\n");

	return 1;
}




/*

		  -------> c1 --------> c2 (exit)	
          | 
          | 
          |
		  |		
          |         
          |         
	------F----------> p


p, c1, c2
c1, p, c2
c1, c2, p

*/
int main() {
	if (Fork() == 0){
		printf("c1\n");
		printf("c22\n");
	}else 
		printf("p\n");

	return 1;
}






/*

		  -------> c --------> done (exit)	
          | 
          | 
          |
		  |		
          |         
          |         
	------F----------> p ----------> done (exit)


c, p, done, done
p, c, done, done  (however, without buffering (fflush), this one will not print)
c, done, p, done
p, done, c, done

*/
int main() {
	if (Fork() == 0){
		printf("c\n");
		fflush(NULL)
	}else {
		printf("p\n");
	}


	printf("done\n");
	return 1;
}




/*

		  -------> c ----> file created ----> done (exit)	
          |                     . 
          |                     .   
          |                     .
		  |		                . 
          |                     . 
          |                     V         
	------F-------------------- opening file -------> remove file -------> p done (exit)


2 outputs
----------------
c, done, p, done
c, p, done, done


*/
int main() {
	if (Fork() == 0){
		printf("c\n");
		fflush(NULL)

		fclose(fopen("file", "w")); // writing to file
	}else {
		while (!fopen("file", "r")) {}  // reading file   // 
		remove("file");

		printf("p\n");
	}


	printf("done\n");
	return 1;
}














