#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main() {
	char* p[3];
	char imsi[101];
	int size;

	for (int i = 0; i < 3; i++) {
		printf("%d번째 문자열 : ", i + 1);
		gets(imsi);
		
		size = strlen(imsi);
		p[i] = (char*)malloc(sizeof(char)*size + 1);

		strcpy(p[i], imsi);
	}
	printf("\n-- 입력과 반대로 출력(포인터) : 글자 순서도 거꾸로 --\n");

	for (int i = 3; i > 0; i--) {
		printf("%d :", i);
		for (int j = strlen(p[i-1]) - 1; j >= 0; j--) 
			printf("%c", p[i-1][j]);
		printf("\n");
	}
	for (int i = 0; i < 3; i++)
		free(p[i]);

	return 0;
}