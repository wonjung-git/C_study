#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main() {
	char* p[3];
	char imsi[201];
	int size, size_sum=0;
	
	for (int i = 0; i < 2; i++) {
		printf("%d번째 문자열 : ", i + 1);
		gets(imsi);

		size = strlen(imsi);
		p[i] = (char*)malloc(sizeof(char) * size + 1);

		strcpy(p[i], imsi);
		size_sum += size;
	}
	p[2] = (char*)malloc(sizeof(char) * size_sum + 1);

	strcpy(p[2], p[0]);
	strcat(p[2], p[1]);

	for (int i = 0; i < 3; i++) {
		printf("%d : %s\n", i+1, p[i]);
	}

	for (int i = 0; i < 3; i++)
		free(p[i]);

	return 0;
}