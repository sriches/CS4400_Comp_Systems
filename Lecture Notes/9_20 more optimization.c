/*
				latency		capacity
	load		4			2
	store		4			1

	int +		1			4
	int *		3			1

	FP +		3			1
	FP*			5			2
*/

/*
	want to know cycles per element.

	have a load, add, and multp
	a[i] = load

	Dependencies for 1st iteration	
	load -> mulp
	mulp -> add
	load -> add

	Dependendies for 2nd iteration
	add (++) -> load (a[i])
	load -> mulp
	load -> add
	addResultFromPrev -> mulp

	Dependencies for 3rd
	iFromPrev -> add (for +=)
	add (++) -> load
	load -> mulp
	addResultFromPrev -> mulp
	load -> add

	Each node has a cost (see table)
	Follow dependency lines to find the longest dependency path.
	4N+4
	about 4 cycles per element



*/
int f(int *a, int len)
{
	int i;
	int r= 0;

	for(i = 0; i < len; i++)
		r = r * a[i] + a[i]

	return r;
}


/*
	load -> mulp
	load -> add


	i++ -> load
	load -> mulp
	load -> add
	prevMult -> multp
	prevAdd -> add

	i -> i++
	i++ -> load

	i++ -> load
	load -> mulp
	load -> add
	prevMult -> multp
	prevAdd -> add

	total = 3N CPE
*/
int f(int *a, int len)
{
	int i;
	int sum = 0;
	int prod = 1;

	for(i = 0; i < len; i++)
	{
		prod = prod * a[i];
		sum = sum + a[i];
	}	

	return r;
}




/*
	same as above, but the latencies change to doubles. So FP* = 5.

	Total = 5N CPE

*/
double f(double *a, int len)
{
	int i;
	double sum = 0;
	double prod = 1;

	for (i = 0; i < len; i++)
	{
		prod = prod * a[i];
		sum = sum + a[i];
	}

	return sum + prod;
}




/*
	load -> mult
	mult -> add

	i++ -> add
	load -> mult
	mult -> add
	prevAdd -> add

	CPE = 3


*/
double f(double *a, int len)
{
	int i;
	double sq_sum = 0;

	for (i=0; i < len; i++)
	{
		sq_sum = sq_sum + (a[i] * a[i]);
	}

	return sq_sum;
}



/*
	load -> mulp
	mulp -> add
	load2 -> mult2
	mult2 -> add2

	add -> load
	load -> mulp
	mulp -> add
	load2 -> mult2
	mult2 -> add2
	prev add1 -> add1
	prev add2 -> add2

	CPE = 3(N/2) = 1.5N   (because we don't have N iterations, we have N/2 iterations)

*/
double f(doubls *a, int len)
{
	int i;
	double sq_sum = 0, sq_sum2 = 0;

	for (i = 0; i < len-1; i+=2)
	{
		sq_sum = sq_sum + (a[i] * a[i]);
		sq_sum2 = sq_sum2 + (a[i+1] * a[i+1]);
	}

	for(; i < len; i++)
	{
		sq_sum = sq_sum + (a[i] * a[i]);
	}

	return sq_sum + sq_sum2;
}



/*
	lea (3 cycles for lea)

	sub -> lea
	lea -> shift

	sub -> 
	prevLea -> shift

	sub -> lea
	prevShift -> lea


	CPE = 5 (N/3) = 1.67N

*/
long iterate(long v, int steps)
{
	while(steps --)
	{
		if(v & 0x1)
		{
			v = 3*v + 1;
		}else
		{
			v = v >> 1;
		}
	}

	return v;
}










