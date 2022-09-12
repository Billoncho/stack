/*
Author: Billy Gene Ridgeway
Date: Sept. 8th. 2022
Purpose: To learn about stacks in C.
*/

// A stack is last-in, first-out (LIFO) data structure.
// It can be though of like a stack of dinner plates

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int a;
	double b;
} DATA;

DATA *base;
DATA *end;
DATA *top;

#define STACKSIZE 8

// Pushes an item onto the top of the stack - returns 1 if the stack size was not exceeded, otherwise 0.
int push(DATA* data) {
	int ok;

	if (top == end) {		// Is there any more room?			
		ok = 0;				// No, so tell the caller.
	} else {
		memcpy(top, data, sizeof(DATA));
		top = top + 1;
		ok = 1;
	}
	return ok;
}

// Pop a data item off the top of the stack.
DATA* pop() {
	DATA* data;

	if (top == base) {		// Empty stack.
		data = NULL;
	} else {
		top = top - 1;		// Get the top item.
		data = top;			// Return the top item.
	}
	return data;
}

int main() {
	DATA data, *pdata;

	base = (DATA*)malloc(STACKSIZE * sizeof(DATA));
	end = base + STACKSIZE;
	top = base;

	// Add data items to the stack until the stack memory is exhausted.
	for (int i = 0; ; i++) {
		data.a = i;
		data.b = i * 2;
		if (!push(&data)) {
			break;
		}
	}

	printf("First item = %d : %f\n", base->a, base->b);
	pdata = base + 4; // Count 4 items up from the 1st struct (at base).
	printf("Last item = %d : %f\n\n", pdata->a, pdata->b);

	// Now pop the data items off the top of the stack until there are no more.
	do {
		pdata = pop();
		if (pdata != NULL) printf("Data popped is %d : %f\n", pdata->a, pdata->b);
	} while (pdata != NULL);

	// NOTE: Do NOT call free for each item 'popped' from the stack
	// because I may want to push onto the stack again.
	// Instead, I call 'free' to release the entire stack when I've finished with it.
	free(base);
	return 0;
}

