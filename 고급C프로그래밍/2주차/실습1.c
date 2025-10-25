#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap_function(int data1, int data2) {
	int temp = data1;
	data1 = data2;
	data2 = temp;

	printf("\n\n\nAfter value swap(in Function), A : %d, B : %d", data1, data2);
}

void swap_pointer_function(int* data1, int* data2) {
	int temp = *data1;
	*data1 = *data2;
	*data2 = temp;
	printf("\n\n\nAfter value swap(in Function), A : %d, B : %d", *data1, *data2);
}

int main() {
	int data1, data2;
	printf("ÀÔ·Â°ª : ");
	scanf("%d %d", &data1, &data2);

	printf("\nBefore swap, A : %d, B : %d", data1, data2);
	swap_function(data1, data2);
	printf("\nAfter value swap(in main), A : %d, B : %d", data1, data2);


	swap_pointer_function(&data1, &data2);
	printf("\nAfter value swap(in main), A : %d, B : %d", data1, data2);
	return 0;
}