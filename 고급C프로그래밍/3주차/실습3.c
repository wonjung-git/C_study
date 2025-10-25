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
		printf("x�� : ");
		scanf("%d", &x);

		printf("y�� : ");
		scanf("%d", &y);

		if (x > 0)
			x += size / 2 - 1;
		else x += size / 2;

		if (y > 0)
			y = y * (-1) + size / 2;
		else y = y * (-1) + size / 2 - 1;

		data[y][x] = 1;

		matrix_print(data);
		printf("\n��ǥ�� �߰� �Ͻðڽ��ϱ�?(�� : 1, �ƴϿ� : 0) : ");
		scanf("%d", &a);
		if (a == 0)
			break;
	}

	x_symmetry(data);
	printf("\nx�� ��Ī\n");
	

	y_symmetry(data);
	printf("\ny�� ��Ī\n");
	
	o_symmetry(data);
	printf("\n���� ��Ī\n");
	return 0;
}