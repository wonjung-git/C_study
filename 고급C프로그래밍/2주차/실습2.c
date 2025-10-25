#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap_by_index(int data[2]) {
	int temp = data[0];
	data[0] = data[1];
	data[1] = temp;
}

void swap_by_pointer(int* data1, int* data2) {
	int temp = *data1;
	*data1 = *data2;
	*data2 = temp;
}

int main() {
	int data[2];
	printf("\nBefore swap: ");
	scanf("%d %d", &data[0], &data[1]);
	swap_by_index(data);
	printf("swap by index : %d %d", data[0], data[1]);


	
	printf("\n\nBefore swap: ");
	scanf("%d %d", &data[0], &data[1]);
	swap_by_pointer(&data[0], &data[1]);
	printf("swap by pointer : %d %d", data[0], data[1]);
	return 0;
}