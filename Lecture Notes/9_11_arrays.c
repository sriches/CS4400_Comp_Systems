


int sum_diagnol(int *a, int n);

int a[3][3] = {{1, 2, 3},
				{4, 5, 6},
				{7, 8, 9}};

// Want to g
et 1+5+9

int sum_diagnol(int *ap, int n)
{
	int sum = 0;

	int i;
	for(i=0; i<n; i++)
	{
		sum = sum + *(ap + (i*n+i));
	}

	return sum;
}


int* rows[3] = {a[0], a[1], a[2]};


int new_sum_diagnol(int **rows, int n)
{
	int sum = 0;
	int i;

	for(i=0; i<n; i++)
	{
		sum += *(*(rows + i)+i);

		/*   Another way: 
			sum += rows[i][i];
		*/
	}

	return sum;
}


int *make_2d_array(int n)
{
	int *test = malloc(sizeof(int) * n * n);

	int i;
	for(i=0; i<n*n; i++)
	{
		*(test + i) = i + 1;
	}

	return test;
}





























