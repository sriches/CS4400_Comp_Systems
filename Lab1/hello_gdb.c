// cs 4400 Lab 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(int argc, char* argv[])
{

	for(int i = 1; i<argc; i++)
	{
		greet(argv[i]);
	}

	return 0;
}

greet(char* name)
{
	printf("%s\n", name);
	name += 2;
	printf("%s\n", name);
}
