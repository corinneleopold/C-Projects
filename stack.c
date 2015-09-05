
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

struct myStack {
	int top;
	double stack[MAXSTACK];	
}st;

void stack_clear() {
	st.top = 0;
}

double stack_pop() {
	double num = st.stack[st.top];
	st.top--;
	return num;
}

void stack_push(double val) {
	st.top++;
	st.stack[st.top] = val;
}

void stack_print() {
	int i;
	int num = 0;
	if (stack_is_empty())
		printf("Stack:\nStack is empty");
	else {
		printf("Stack:\n");
		for (i = 1; i <= st.top; i++) {
			printf("%d: %.6lf\n", num, st.stack[i]);
			num++;
		}
	}
}

int stack_top() {
  return st.top;
}

int stack_max() {
  return MAXSTACK;
}

int stack_is_empty() {
  return (st.top == 0);
}
