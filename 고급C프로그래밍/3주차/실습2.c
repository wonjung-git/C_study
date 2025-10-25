#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int data[4][8] = { 0, };
	for (int i = 0; i < 8; i++)
		scanf("%d", &data[0][i]);


	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 7; j += 2*(i+1)) {
			*(*(data + i + 1) + j) = *(*(data + i) + j) + *(*(data + i) + j + (1 << i));
		}
	 }

	for (int i = 0; i < 4; i++) {
		printf("\n");
		for (int j = 0; j < 8; j++)
			printf("%3d", data[i][j]);
	}

	return 0;
}