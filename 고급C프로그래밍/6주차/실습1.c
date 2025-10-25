#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main() {
	FILE* output;
	output = fopen("output1.txt", "w");
	char* p[3];
	char imsi[101], *temp;
	int size;

	for (int i = 0; i < 3; i++) {
		printf("%d번째 문자열 : ", i + 1);
		gets(imsi);

		size = strlen(imsi);
		p[i] = (char*)malloc(sizeof(char) * size + 1);

		strcpy(p[i], imsi);
	}
	printf("\n-- 입력과 반대로 출력(포인터) : 글자 순서도 거꾸로 --\n");

	for (int i = 3; i > 0; i--) {
		printf("%d :", i);
		temp = (char*)malloc(sizeof(char) * strlen(p[i - 1]) + 1);
		for (int j = strlen(p[i - 1]) - 1; j >= 0; j--) {
			printf("%c", p[i - 1][j]);
			temp[strlen(p[i - 1])-1 - j] = p[i - 1][j];
		}
		temp[strlen(p[i - 1])] = '\0';
		fputs(temp, output);
		fputs("\n", output);
		printf("\n");
		free(temp);
	}
	for (int i = 0; i < 3; i++)
		free(p[i]);

	fclose(output);

	return 0;
}