/* Name:		Spenser Riches
 * UID:			U1072910
 * Date:		Sept 5, 2017
 * Course:		CS 440-001
 * Assignment:	Match
 */


/* ASSIGNMENT INSTRUCTIONS

Match Assignment for u1072910

The goal of this assignment is to give you some practice with C on a problem that is algorithmically 
straightforward but difficult to get right on a first try. With any luck, you'll have a bug along 
the way, and then you get to practice using GDB.

Your task is to implement a program that takes command-line arguments and checks whether each 
argument matches a particular pattern. The pattern to check is determined by a command-line flag: 
-a, -b, or -c, where the default mode is -a. The patterns for each flag are described below.

By default, your program should print “yes” (always lowercase, no extra space) for each matching 
argument and “no” (always lowercase, no extra space) for each non-matching argument, each on a 
separate line. If the -t flag is provided, then your program should instead print nothing for 
non-matching argument and it should print a converted value for each matching argument. Each pattern 
mode has an associated conversion, as described below.

At most one of -a, -b, or -c will be provided. A -t flag can be provided before or after any of -a, 
-b, and -c. All flags (i.e,. up to two of them) precede other command-line arguments. A non-flag 
argument never starts with -. All arguments are in ASCII.

See the end of this page for example command-line uses of your program. Neither the examples there 
nor the examples for indvidual patterns are meant to be exhaustive.

Constraints: Your implementation must be in ANSI C, so that it compiles without errors or extra flags 
on the CADE lab1-n.eng.utah.edu machines using the default gcc. Your implementation must not depend 
on any libraries other than the standard C library; please note that while "regex.h" and its 
associated functions are POSIX-standard, they are not part of ANSI C and therefore not allowed in 
this assignment. Also, yor implementation must not use multiplication, division, or modulo operators. 
(Bitwise operations offer alternatives to those operations.) You should hand in one matchlab.c file 
so that gcc -o matchlab matchlab.c on a CADE lab machine builds your program as matchlab; your 
program should work the same with and without debugging and optimization options such as -g or -O2. 
Hand in via Canvas.

Important! Make sure the uID listed at the top of the page is correct, because this assignment (and 
its correct answer) is uID-specific.

Where the descriptions below say “even position” or “odd position”, counting is from 0, as in C. So, 
a first character is in an even position.

-a mode

Match a sequence of the following, with nothing else before, after, or in between:
 * any number (including zero) repetitions of the letter “j”;
 * exactly one “=”;
 * any odd number of repetitions of the letter “s”;
 * exactly one “,”; and
 * an odd number of uppercase letters.

For matches, perform the following conversion:
 * replace each character by the last one.

Example arguments that match, followed by their conversions:
=sssss,ADH
→ HHHHHHHHHH
jjj=sssss,H
→ HHHHHHHHHHH
j=s,F
→ FFFFF
jjj=sssssss,B
→ BBBBBBBBBBBBB
jjj=sssssss,ECG
→ GGGGGGGGGGGGGGG
j=sss,E
→ EEEEEEE
j=sssssss,HGFDG
→ GGGGGGGGGGGGGGG
jj=sssssssss,AEE
→ EEEEEEEEEEEEEEEE
jjjj=s,GCA
→ AAAAAAAAAA
jj=s,HBHBB
→ BBBBBBBBBB

Example arguments that do not match:
.=sssss,ADH
=sssss,ADH.
,www,E
jjjj_sssss,EEF
j=uuuuuu,A
k=sss,CGA
k=sss,CEF
jjjj=sssssssss=CEHCB
jjj=zzzzzzz,H
jj:sssssss,HBCDC
aaaaaaaaa=y,C
cccc=s,DGA
BHEAF=,sssssssj
=,sssssjjA

-b mode

Match a sequence of the following, with nothing else before, after, or in between:
 * between 1 and 2 repetitions (inclusive) of the letter “m”;
 * exactly one “:”;
 * an odd number of uppercase letters — call this sequence X;
 * 2 or more repetitions of the letter “r”;
 * exactly one “,”;
 * between 1 and 3 (inclusive) decimal digits; and
 * the same characters as X repeated 2 times.

For matches, perform the following conversion:
 * add one “G” after each “H”.

Example arguments that match, followed by their conversions:
m:EFGDBrrrrrr,375EFGDBEFGDB
→ m:EFGDBrrrrrr,375EFGDBEFGDB
m:Arrrrr,925AA
→ m:Arrrrr,925AA
m:FGEEArrrrrrr,555FGEEAFGEEA
→ m:FGEEArrrrrrr,555FGEEAFGEEA
m:FACrrrrrrrrr,934FACFAC
→ m:FACrrrrrrrrr,934FACFAC
m:Crrrrrrrrr,610CC
→ m:Crrrrrrrrr,610CC
m:Frrrrrr,790FF
→ m:Frrrrrr,790FF
m:BBGrrrrrrrrr,209BBGBBG
→ m:BBGrrrrrrrrr,209BBGBBG
m:Brrrrrrrrr,859BB
→ m:Brrrrrrrrr,859BB
m:EGArrrrrr,750EGAEGA
→ m:EGArrrrrr,750EGAEGA
m:CGCrrrrr,364CGCCGC
→ m:CGCrrrrr,364CGCCGC

Example arguments that do not match:
.m:EFGDBrrrrrr,375EFGDBEFGDB
m:EFGDBrrrrrr,375EFGDBEFGDB.
gggggggg:AGHDCn,419AGHDCAGHDC
aaaa:CAHBBrrrrrrr,700CAHBBCAHBB
dddddddd:GCArrrrrrrr_110GCAGCA
m:Fnnnnnnnnn,493FF
m:EBHttt,463EBHEBH
m:DGDHGrrrrrrrrr:990DGDHGDGDHG
:EADEDrrrrrrrrr,752EADEDEADED
m_Drrrrrrr,747DD
m:Brrrrrrrrr=711BB
m=AFBrrrrrr,667F
mFCF:,FCFFCF36rrrrr
,212rrrrrrH:HHm

-c mode

Match a sequence of the following, with nothing else before, after, or in between:
 * any number (including zero) repetitions of the letter “g”;
 * exactly one “,”;
 * an odd number of uppercase letters — call this sequence X;
 * 2 or more repetitions of the letter “u”;
 * exactly one “_”;
 * between 1 and 3 (inclusive) decimal digits; and
 * the same characters as X repeated 3 times.

For matches, perform the following conversion:
 * remove the first “E” and last “E”, if any.

Example arguments that match, followed by their conversions:
gg,Cuuuuuu_368CCC
→ gg,Cuuuuuu_368CCC
gg,Buuuuuu_996BBB
→ gg,Buuuuuu_996BBB
gg,Cuuuuuuu_852CCC
→ gg,Cuuuuuuu_852CCC
gggg,GCHuuuuuu_332GCHGCHGCH
→ gggg,GCHuuuuuu_332GCHGCHGCH
gg,Cuuuuuuu_555CCC
→ gg,Cuuuuuuu_555CCC
gggg,Duuuuuuuuu_989DDD
→ gggg,Duuuuuuuuu_989DDD
gggg,Huuuuuuuu_430HHH
→ gggg,Huuuuuuuu_430HHH
,AFDuuuuuuuuu_271AFDAFDAFD
→ ,AFDuuuuuuuuu_271AFDAFDAFD
ggg,Cuuuuuu_555CCC
→ ggg,Cuuuuuu_555CCC
gg,DDBuuuuuu_518DDBDDBDDB
→ gg,DDBuuuuuu_518DDBDDBDDB

Example arguments that do not match:
.gg,Cuuuuuu_368CCC
gg,Cuuuuuu_368CCC.
g=Euuuuuu_414EEE
gg,BGCuuuuuuu=98BC
aaaaaa,EHHuuuuuuuu=837EHHEHHEHH
g,EFDuuuuuu,697EFDEFDEFD
gg,HEGAGyy_503HEGAGHEGAGHEGAG
g:BHHuuuuuuuuu_549BHHBHHBHH
gggg=GAHuuuuu_958GAHGAHGAH
g,Hxxxxxxxxx_681HHH
g,EEDuuuuuu_703EEDEEDEEDEED
gggg,CFBzzzzzzzz_331CFBCFBCFB
36FBG_FBGFBGFBG,ggguuuuuuu
uuuuuuuuG800g,_GGG
Examples

Assuming that your program is created as ./matchlab, here are some example command-line uses 
(where “$” is a command-line prompt). We expect your program to match this output exactly.

  $ ./matchlab =sss,E
  yes

  $ ./matchlab j=sssssssss:FDD
  no

  $ ./matchlab =sss,E j=sssssssss:FDD
  yes
  no

  $ ./matchlab -t =sss,E
  EEEEEE

  $ ./matchlab -t j=sssssssss:FDD =sss,E
  EEEEEE
  
  $ ./matchlab -t =sss,E jjjj=s,EACHG
  EEEEEE
  GGGGGGGGGGGG
  
  $ ./matchlab -t -b m:CFHGArrrrrrrrr,846CFHGACFHGA
  m:CFHGGArrrrrrrrr,846CFHGGACFHGGA
  
  $ ./matchlab -c -t ,Euuuuuuuu_792EEE
  ,uuuuuuuu_792EE
  
  $ ./matchlab -c ,Euuuuuuuu_792EEE
  yes
 
 */

#include <stdio.h>
#include <string.h>

/* Forward Declarations */
void aMode(int, char**, int);
void bMode(int, char**, int);
void cMode(int, char**, int);
void checkWhichCaseToRunWithMultipleArgs(int, char**);
char* aConversion(char*);

int main(int argc, char *argv[])
{
	printf("Hello\n");

	/* Get the number of arguments */
	printf("Arguments: %d\n", argc);

	
	switch(argc)
	{
		/* If only one argument (argc=2), default to '-a' mode */
		case 2:
			aMode(argc, argv, 0);
			break;

		/* If 2 arguments, check if the first is a flag, otherwise, default to '-a' mode */
		case 3:
			if (strcmp(argv[1], "-b") == 0)
			{
				printf(argv[1]);
				printf("\ngo to b mode\n");
				bMode(argc, argv, 0);
			}
			else if (strcmp(argv[1], "-c") == 0)
			{
				printf(argv[1]);
				printf("\ngo to c mode\n");

				cMode(argc, argv, 0);
			}
			else if (strcmp(argv[1], "-t") == 0)
			{
				/* 2 vars with the 1st as -t should go to aMode with conversion
				 * If the two arguments are "-t -b", then no match is made, so
				 * sending to aMode will process equally */
				printf(argv[1]);
				printf("\ngo to a mode with conversion\n");

				aMode(argc, argv, 1);
			}
			else
			{
				printf(argv[1]);
				printf("\ngo to a mode\n");

				aMode(argc, argv, 0);
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
		aMode(argc, argv, 0);
	}
	/* If first arg is '-a' */
	else if (strcmp(argv[1], "-a") == 0)
	{
		/* If second arg is a '-t', then go to a mode with conversion */
		if (strcmp(argv[2], "-t") == 0)
		{
			printf("a mode with conversion");
			aMode(argc, argv, 1);
		}
		else
		{
			printf("a mode without conversion");
			aMode(argc, argv, 0);
		}
	}
	/* If first arg is '-b' */
	else if (strcmp(argv[1], "-b") == 0)
	{
		/* If second arg is a '-t', then go to b mode with conversion */
		if (strcmp(argv[2], "-t") == 0)
		{
			printf("b mode with conversion");
			bMode(argc, argv, 1);
		}
		else
		{
			printf("b mode without conversion");
			bMode(argc, argv, 0);
		}
	}
	/* If first arg is '-c' */
	else if (strcmp(argv[1], "-c") == 0)
	{
		/* If second arg is a '-t', then go to c mode with conversion */
		if (strcmp(argv[2], "-t") == 0)
		{
			printf("c mode with conversion");
			cMode(argc, argv, 1);
		}
		else
		{
			printf("c mode without conversion");
			cMode(argc, argv, 0);
		}
	}
	/* If first arg is '-t' */
	else if (strcmp(argv[1], "-t") == 0)
	{
		/* If second arg is a '-b', then go to b mode with conversion */
		if (strcmp(argv[2], "-b") == 0)
		{
			printf("b mode with conversion");
			bMode(argc, argv, 1);
		}
		/* If second arg is a '-c', then go to c mode with conversion */
		else if (strcmp(argv[2], "-c") == 0)
		{
			printf("c mode with conversion");
			cMode(argc, argv, 1);
		}
		/* Anything else, default to a mode with conversion */
		else
		{
			printf("a mode with conversion");
			aMode(argc, argv, 1);
		}
	}
}

void aMode(int argNum, char *argv[], int conversion)
{
	printf("beginning of a mode\n");

	/* Go through each word in argv */
	int i;
	for (i = 1; i < argNum; i++)
	{
		/* Check if the word is a flag */
		int isAFlag =
			(i == 1 && strcmp(argv[1], "-a") == 0) ||
			(i == 1 && strcmp(argv[1], "-t") == 0) ||
			(i == 2 && strcmp(argv[2], "-a") == 0) ||
			(i == 2 && strcmp(argv[2], "-t") == 0);

		/* If the word is not a flag, check to see if it matches the desired pattern:
		 * 
		 * 1. any number (including zero) repetitions of the letter “j”;
 		 * 2. exactly one “=”;
 		 * 3. any odd number of repetitions of the letter “s”;
 		 * 4. exactly one “,”; and
 		 * 5. an odd number of uppercase letters.
		 */
		if(!isAFlag)
		{
			/* Store the word */
			char *word = argv[i];

			/* Get the length of the word */
			int wordLength = strlen(word);

			printf("Not a flag\n");
			printf("Word: %s  Length: %d\n", argv[i], wordLength);

			/* Variable that will tell if the word is not a match */
			int notAMatch = 0;

			/* Variable to tell which requirement the character should match */
			int requirement = 1;

			/* Variable to keep track of 's' repetitions for requriement 3 */
			int sRepetitions = 0;

			/* Keep a character index counter */
			int charIndex;

			/* Look at each character in a row */
			for(charIndex = 0; charIndex < wordLength; charIndex++)
			{

				printf("Checking %c...  Req %d\n", word[charIndex], requirement);

				if(notAMatch)
				{
					break;
				}
				else
				{
					/* Check if the character matches */
					switch(requirement)
					{
						case 1:
							if(word[charIndex] != 'j')
							{
								requirement++;
								goto req2;
							}
							break;

						case 2:
						req2:
							if(word[charIndex] == '=')
							{
								requirement++;
							}
							else
							{
								notAMatch = 1;
								if(!conversion)
								{
									printf("no\n");
								}
							}
							break;

						case 3:
							if(word[charIndex] == 's')
							{
								sRepetitions++;
							}
							else
							{
								/* Make sure the 's' was repeated an odd number of times */
								if(sRepetitions & 1) /* Checks if the number is odd */
								{
									requirement++;
									goto req4;
								}
								else
								{
									notAMatch = 1;
									if(!conversion)
									{
										printf("no\n");
									}
								}
							}
							break;

						case 4:
						req4:
							if(word[charIndex] == ',')
							{
								requirement++;
							}
							else
							{
								notAMatch = 1;
								if(!conversion)
								{
									printf("no\n");
								}
							}
							break;

						case 5:
							/* Check if character is uppercase */
							if(word[charIndex] >= 'A' && word[charIndex] <= 'Z')
							{
								/* If this is the last letter in the word */
								if(wordLength - 1 == charIndex)
								{
									/* The whole word is a match */
									if(conversion)
									{
										/* Convert the word. 
										 * The conversion should replace each character by the last one.*/
										char lastChar = word[wordLength - 1];

										/* Create empty string */
										char convertedWord[wordLength + 1];
										int cIndex;
										for (cIndex = 0; cIndex < wordLength; cIndex++)
										{
											convertedWord[cIndex] = 0;
										}

										int i;
										for (i=0; i < wordLength; i++)
										{
											convertedWord[i] = lastChar;
										}
										/*terminate string */
										convertedWord[i] = 0;

										/* Print the conversion to the console */
										printf(convertedWord);
										printf("\n");
									}
									else
									{
										printf("yes\n");
									}
								}
							}
							else
							{
								notAMatch = 1;
								if(!conversion)
								{
									printf("no\n");
								}
							}

							break;
					}
				}
			}
		}
	}
}


void bMode(int argNum, char *argv[], int conversion)
{
	printf("beginning of b mode\n");



}

void cMode(int argNum, char *argv[], int conversion)
{
	printf("beginning of c mode\n");



}