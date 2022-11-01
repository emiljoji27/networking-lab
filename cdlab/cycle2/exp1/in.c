//input program for lexical analyser

#include<stdio.h>

/* This
is
comment
*/

int sum(int a, int b) {
	return a + b;
}

void main() {
	int a,b,c;
	a = 1;
	b = 2;
	c = sum(a, b);
	printf("Sum: %d", c);
}
