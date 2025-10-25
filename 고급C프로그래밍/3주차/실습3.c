#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define size 4

void matrix_print(int data[size][size]) {
	for (int i = 0; i < size; i++) {
		printf("\n");
		for (int j = 0; j < size; j++)
			if (data[i][j] == 1)
				printf("X");
			else printf("O");
	}
}

void o_symmetry(int data[size][size]) {
	int temp_matrix[size][size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp_matrix[j][i] = data[j * (-1) + size - 1][i * (-1) + size - 1];
		}
	}
	matrix_print(temp_matrix);
}

void x_symmetry(int data[size][size]) {
	int temp_matrix[size][size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp_matrix[j][i] = data[j * (-1) + size - 1][i];
		}
	}
	matrix_print(temp_matrix);
}

void y_symmetry(int data[size][size]) {
	int temp_matrix[size][size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp_matrix[i][j] = data[i][j*(-1) + size - 1];
		}
	}
	matrix_print(temp_matrix);
}



int main() {
	int data[size][size] = { 0, }, x, y, a;
	while (1) {
		printf("x축 : ");
		scanf("%d", &x);

		printf("y축 : ");
		scanf("%d", &y);

		if (x > 0)
			x += size / 2 - 1;
		else x += size / 2;

		if (y > 0)
			y = y * (-1) + size / 2;
		else y = y * (-1) + size / 2 - 1;

		data[y][x] = 1;

		matrix_print(data);
		printf("\n좌표를 추가 하시겠습니까?(예 : 1, 아니요 : 0) : ");
		scanf("%d", &a);
		if (a == 0)
			break;
	}

	x_symmetry(data);
	printf("\nx축 대칭\n");
	

	y_symmetry(data);
	printf("\ny축 대칭\n");
	
	o_symmetry(data);
	printf("\n원점 대칭\n");
	return 0;
}