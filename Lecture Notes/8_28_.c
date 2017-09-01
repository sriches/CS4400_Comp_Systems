/* Mon Aug 28 Notes */


int f(long x, int y, char z, int* p)
{

}

/*  Parameters Order to Register
 *  1	edi	rdi
 *	2	esi	rsi
 *	3	edx	rdx
 *	4	ecx rcx
 *
 *	return eax
/*
	leal	($rsi, $rdi), $eax
	ret
*/
int f(long x, int y, char c, int* p)
{
	return y + x;
}

/*
	movq	$rdi, $rax
	movl	$edx, $ecx
	salq	$cl, $rax
	ret
*/
int f(long x, int y, char z, int* p)
{
	long temp = x;
	char temp2 = z;
	temp <<= temp2;
	return temp;

	// Otherwize, return x << z;
}


/* 	
 *	subl	$esi, $edi
 *	movsbl	$dl, $edx
 *	movl  $edi, $eax
 *	imull	$edx, $eax
 *	ret
 */
int f(long x, int y, char z, int* p)
{
	x = x-y;
	int temp = (int)z;
	int ret_val = x;
	ret_val = temp * ret_val;
	return ret_val;

	// OR
	// return z * (x-y);
}

/*
 *	leal	($rsi, $rdi), $eax
 *	movsbl	$eax, ($rcx)
 *	ret
*/
int f(long x, int y, char z, int* p)
{
	int temp = x+y;
	*p temp;
	return temp;

	// OR
	// return *p = x+y;
}



/*	movl  $edi, $eax
 * 	addl	($rcx), $eax
 *  movsbl$eax, ($rcx)
 *  ret
 */
int f(long x, int y, char z, int* p)
{
	int temp = x;
	temp += *p;
	*p = temp;
	return temp;

	// OR
	//return *p += x;
}






