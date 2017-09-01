/*
 *
 *
 *
 */

#include <stdio.h>
#include <string.h>

/* Forward Declarations */
void aMode(char**, int);
void bMode(char**, int);
void cMode(char**, int);
void checkWhichCaseToRunWithMultipleArgs(int, char**);

int main(int argc, char *argv[])
{
	printf("Hello\n");

	/* Get the number of arguments */
	printf("Arguments: %d\n", argc);

	
	switch(argc)
	{
		/* If only one argument (argc=2), default to '-a' mode */
		case 2:
			aMode(argv, 0);
			break;

		/* If 2 arguments, check if the first is a flag, otherwise, default to '-a' mode */
		case 3:
			if (strcmp(argv[1], "-b") == 0)
			{
				printf(argv[1]);
				printf("\ngo to b mode\n");
				bMode(argv, 0);
			}
			else if (strcmp(argv[1], "-c") == 0)
			{
				printf(argv[1]);
				printf("\ngo to c mode\n");

				cMode(argv, 0);
			}
			else if (strcmp(argv[1], "-t") == 0)
			{
				/* 2 vars with the 1st as -t should go to aMode with conversion
				 * If the two arguments are "-t -b", then no match is made, so
				 * sending to aMode will process equally */
				printf(argv[1]);
				printf("\ngo to a mode with conversion\n");

				aMode(argv, 1);
			}
			else
			{
				printf(argv[1]);
				printf("\ngo to a mode\n");

				aMode(argv, 0);
			}
			break;

		/* If 3+ arguments, both could be flags so check for a combination of possibilities */
		default:
			checkWhichCaseToRunWithMultipleArgs(argc, argv);	
	}

	return 0;
}

void checkWhichCaseToRunWithMultipleArgs(int argc, char *argv[])
{
	printf("3+ args. Need to check args before sending to mode\n");

	/* If no flags, send to a mode */
	if (argv[1][0] != '-')
	{
		printf("no flags, default a mode\n");
		aMode(argv, 0);
	}
	/* If first arg is '-a' */
	else if (strcmp(argv[1], "-a") == 0)
	{
		/* If second arg is a '-t', then go to a mode with conversion */
		if (strcmp(argv[2], "-t") == 0)
		{
			printf("a mode with conversion");
			aMode(argv, 1);
		}
		else
		{
			printf("a mode without conversion");
			aMode(argv, 0);
		}
	}
	/* If first arg is '-b' */
	else if (strcmp(argv[1], "-b") == 0)
	{
		/* If second arg is a '-t', then go to b mode with conversion */
		if (strcmp(argv[2], "-t") == 0)
		{
			printf("b mode with conversion");
			bMode(argv, 1);
		}
		else
		{
			printf("b mode without conversion");
			bMode(argv, 0);
		}
	}
	/* If first arg is '-c' */
	else if (strcmp(argv[1], "-c") == 0)
	{
		/* If second arg is a '-t', then go to c mode with conversion */
		if (strcmp(argv[2], "-t") == 0)
		{
			printf("c mode with conversion");
			cMode(argv, 1);
		}
		else
		{
			printf("c mode without conversion");
			cMode(argv, 0);
		}
	}
	/* If first arg is '-t' */
	else if (strcmp(argv[1], "-t") == 0)
	{
		/* If second arg is a '-b', then go to b mode with conversion */
		if (strcmp(argv[2], "-b") == 0)
		{
			printf("b mode with conversion");
			bMode(argv, 1);
		}
		/* If second arg is a '-c', then go to c mode with conversion */
		else if (strcmp(argv[2], "-c") == 0)
		{
			printf("c mode with conversion");
			cMode(argv, 1);
		}
		/* Anything else, default to a mode with conversion */
		else
		{
			printf("a mode with conversion");
			aMode(argv, 1);
		}
	}
}

void aMode(char *argv[], int conversion)
{
	printf("beginning of a mode\n");

	








}

void bMode(char *argv[], int conversion)
{
	printf("beginning of b mode\n");



}

void cMode(char *argv[], int conversion)
{
	printf("beginning of c mode\n");



}