#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

float pi = 3.14;

float area(int r) {
	return r * r * pi;
}

float circumference(int r) {
	return r * pi * 2;
}

int main() {
	int r;
	printf("����/�ѷ��� ���� ���� �������� �Է��Ͻʽÿ� : ");
	scanf("%d", &r);
	printf("�Է��� ������ : %d �� ���� ", r);
	printf("\n���� ���̴� %f", area(r));
	printf("\n���� �ѷ��� %f", circumference(r));
	return 0;
}