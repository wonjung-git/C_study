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
	printf("넓이/둘레를 구할 원의 반지름을 입력하십시오 : ");
	scanf("%d", &r);
	printf("입력한 반지름 : %d 에 대한 ", r);
	printf("\n원의 넓이는 %f", area(r));
	printf("\n원의 둘레는 %f", circumference(r));
	return 0;
}