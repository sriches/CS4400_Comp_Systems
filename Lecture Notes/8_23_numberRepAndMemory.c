#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int arr[6] = {4, 8, 15, 16, 23, 42 };
	int* ptr = arr;

	printf("arr: %d\n", arr);
	printf("arr[5]: %d\n", arr[5]);
	printf("arr[6]: %d\n", arr[6]);
	printf("*ptr: %d\n", *ptr);
	printf("*(ptr+5): %d\n", *(ptr+5));
	printf("*(ptr+6): %d\n", *(ptr+6));
	printf("*ptr+6: %d\n", *ptr+6);


	print("\n\n");

	int i = -1;
	unsigned int u = i;
	print(i);


	return 0;
}


/**
 *  
 */
int is_negative(int n)
{
	// Int is a signed bit, if n is negative, it will fill in with 1's

	return (n >> 31) & 1;  // Bit shift down. Throw away the lower 31
	// Also can use the below
	// unsigned int x = n;
	//return (n >> 31);  // Bit shift down. Throw away the lower 31
}


int is_negative(double n)
{
	// double has 64 bits
	//return (n >> 63) & 1; // WRONG _ shift doesn't work for floating point numbers
	long x;
	memcpy(&x, &n, sizeof(long));
	return (*x >> 63) & 1;


}

// bit set ------------------------------------------
char* make_empty_bit_set(int capacity)
{
	char* x = malloc(capacity / 8+1);// malloc takes how many bytes you want
	memset(x, 0, capacity/8+1); // Set all memory in x with 0
	return x;
}

void add_to_set(char* s, int digit)
{
	// params: address s and number digit
	// Set one bit in memory
	s[digit >> 3] = (1<<(digit & 7)) | s[digit >> 3];  // digit >> 3 is the same as digit/8......digit & 7 is like modulo
}

// is the digit bit set ini s?
int is_in_set(char* s, int digit)
{
	return !! s[digit>>3] & (1<<(digit & 7));
	//     ^the right byte   ^ the right bit
}

// bit set END --------------------------------------