#include <stdio.h>
#include <stdlib.h>

// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	//Print bits
	unsigned int size = sizeof(unsigned int);
	unsigned int maxPow = 1<<(size*8-1);
	int count = 0;
	while (maxPow) {
		printf("%u", (bitmap & maxPow) ? 1 : 0);
		count++;
		maxPow >>= 1;
	}
	printf("\n");

	//Print indices
	int array[count];
	int i;
	int index = 0;
	for (i = 1; i <= count; i++) {
		if (index == 10) {
			index = 0;
		}
		array[i] = index;
		index++;
	}
	for (i = count; i > 0; i--)
		printf("%d", array[i]);
	printf("\n");
}

// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt(unsigned int *bitmap, int i, int bitValue ) {
	if (bitValue == 1) {
		*bitmap |= 1 << i;
	}
	else {
		*bitmap &= ~(1 << i);
	}
}
// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	return ((bitmap>>i)&1);
}
// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	int count0 = 0;
	int count1 = 0;
	int n = (sizeof(bitmap) << 3);
	int i;
		for (i = 0; i < n; i++) {
			if (getBitAt(bitmap, i) == 1)
				count1++;
			else if (getBitAt(bitmap, i) == 0)
				count0++;
		}
	if (bitValue == 1)
		return count1;
	else
		return count0;
}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	int count = 0;
	int maxCount = 0;
	int i;
	int lastPos = 0;
	for (i = 0; i < 32; i++) {
		if (getBitAt(bitmap, i) == 1) 
			count++;
		else {
			if (count > maxCount) {
				maxCount = count;
				lastPos = i-count;
			}
			count = 0;
		}
	}
	*position = lastPos;
	return maxCount;
}
