


typedef struct fish {
int color;
char *name;
} fish;

/*
	offsetof(fish, color) = 0
	offsetof(fish, name) = 8 (pointers are always 8 bytes, no matter what they point to)
	sizeof(fish) = 16
*/


typedef struct fish2 {
	char *name;
	int color;
} fish2;


/*
	offsetof(fish2, color) = 0
	offsetof(fish2, name) = 8
	sizeof(fish2) = 16
*/


typedef struct int_tree {
	struct int_tree *left;
	struct int_tree *right;
	int val;
} int_tree;

/*
	offsetof(int_tree, left) = 0
	offsetof(int_tree, right) = 8
	offsetof(int_tree, val) = 16
	sizeof(int_tree) = 24
*/


typedef struct {
	short a;
	char b;
	double d;
	int x;
	short *y;
	union {
		char b2;
		int b3;
	} u;
	short end;
} jumble;

/*
	offsetof(jumble, a) = 0
	offsetof(jumble, b) = 2
	offsetof(jumble, d) = 8
	offsetof(jumble, x) = 16
	offsetof(jumble, y) = 24
	offsetof(jumble, u.b2) = 32
	offsetof(jumble, u.b3) = 32
	offsetof(jumble, end) = 36
	sizeof(jumble) = 40
*/


typedef struct {
	short a;
	char b;
	double d;
	int x;
	short *y;
	union {
		char b2;
		int b3;
	} u;
	short end;
	struct {
		double x;
		double y;
	} posn;
} jumble2;

/*
	offsetof(jumble2, a) = 0
	offsetof(jumble2, b) = 2
	offsetof(jumble2, d) = 8
	offsetof(jumble2, x) = 16
	offsetof(jumble2, y) = 24
	offsetof(jumble2, u.b2) = 32
	offsetof(jumble2, u.b3) = 32
	offsetof(jumble2, end) = 36
	
	offsetof(jumble2, posn.x) = 
	offsetof(jumble2, posn.y) = 

	sizeof(jumble2) = 
*/




int sum_list(int_list *lst)
{
	int sum = 0;

	while(lst->next != NULL)
	{
		sum += lst->val;
		lst = lst->next;
	}

	return sum;
}


int_list *array_to_list(int *a, int len) 
{
	int_list *retList = NULL;
	int i;

	for(i = len-1; i>=0; i--)
	{
		int_list *newNode = malloc(sizeof(int_list));
		newNode->val = a[i];
		newNode->next = retList;
		retList = newNode;
	}

	return retList;
}











