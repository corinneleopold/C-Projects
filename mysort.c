#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
 * Sort an array of element of any type using "compFunc"
 *
 * The elements are sorted such as:
 *
 * if ascending != 0
 *  compFunc( array[ i ], array[ i+1 ] ) <= 0
 * else
 *  compFunc( array[ i ], array[ i+1 ] ) >= 0
*/

void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	void * temp = malloc(elementSize);
	int i;
	int j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i-1; j++) {
			void * e1 = (void *) ((char *) array + j * elementSize);
			void * e2 = (void *) ((char *) array + (j + 1) * elementSize);
			if (ascending != 0) {
				if ((*compFunc) (e1, e2) > 0) {
					memcpy(temp, e1, elementSize);
					memcpy(e1, e2, elementSize);
					memcpy(e2, temp, elementSize);
				}
			}
			else if (ascending == 0) {
				if ((*compFunc) (e1, e2) < 0) {
					memcpy(temp, e1, elementSize);
					memcpy(e1, e2, elementSize);
					memcpy(e2, temp, elementSize);
				}	
			}
		}
	}
	free(temp);
}

int compFunc(void *a, void *b) {
	int * a2 = (int *) a;
	int * b2 = (int *) b;
	if (*a2 > *b2)
		return 1;
	else if (*a2 < *b2)
		return -1;
	else
		return 0;
}
