/*
	Code Movement
	i.e. moving a computation inside a loop outside the loop to use as a constant (as long as it doesn't change in the loop)

	Strength Reduction
	3/4 can be optimized as 3>>2  (shift by 2 bits)

	Common Subexpression Elimination
	for (i = 1; i<len + 3/4; i++)
		a[i] += a[0] + 3/4

		Replace the 3/4 with n by initializing n before the loop by n = 3/4.




	Aliasing -> When you have 2 pointers that may overlap each other


*/

/*
EXAMPLE 1
----------------------*/
int f(int *a, int len)
{
	int i, sum = 0;
	for(i=1; i<len; i++)
		a[i] += a[0];
	return sum;
}

/* Optimized to below */

int f(int *a, int len)
{
	int i, sum = 0;
	int v = a[0];
	for (i=1; i < len; i++)
		a[i] += v;
	return sum;
}


/*
EXAMPLE 2
Compiler optimized this on its own using -O2
Lifted the a[0] out of the loop, because you're noto writing to memory */
------------------------
int f(int *a, int len)
{
	int i, sum = 0;
	for(i=1; i<len; i++)
		sum += a[0] + a[i];
	return sum;
}


/*
EXAMPLE 3
Compiler does not lift a[0] out.

*/
int f(int *a, int *b, int len)
{
	int i, sum = 0;
	for(i=1; i<len; i++)
		b[i] += a[0];
	return sum;
}


/* EXAMPLE 4
	Loop unrolling, and common subexpression elimination to reuse i-1 for the next loop iteration.
	Compiler does not see optimization. You need to change the code by hand.
*/
int f(int *a, int len)
{
	int i, sum = 0;
	for(i=1; i<len; i++)
		sum += a[i-1] + a[i];
	return sum;
}

// Need to make optimization by hand
int f(int *a, int len)
{
	int i, sum = 0;
	int temp = a[0];
	for(i=1; i<len; i++)
	{
		int ai = a[i];	// Comiler doesn't care what scope this int is declared.
		sum += temp + ai;
		temp = ai;
	}
	return sum;
}




/*
	EXAMPLE 5
	Can't lift out a[0] because it's possible that convert could change a[0].
	Compiler won't optimize because we can't guarantee what till happen to a[0].
*/
typedef int (*convert_proc)(int, int);

int f(int *a, int len, convert_proc convert)
{
	int i, sum = 0;
	for(i=1; i<len; i++)
		sum += convert(a[0], a[i]);
	return sum;
}


/*
	EXAMPLE 6
	r is assumed not to overlap with a. Called strict aliasing. 
	You're not allowed to alias things that are of different types. 
	Compiler optimizes on its own.
*/
void f(long *r, int *a, int len)
{
	int i;
	for(i=1; i<len; i++)
		*r += a[i];
}


/* 
	EXAMPLE 7
	a[0] can be lifted out.
	compiler detects a[0] is constant.
	compiler replaces function with one multiplication.
*/
void f(long *r, int *a, int len)
{
	int i;
	for(i=1; i<len; i++)
		*r += a[0];
}










