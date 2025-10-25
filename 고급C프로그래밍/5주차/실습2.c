#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int my_strcmp(char* data1, char* data2) {
	int size = strlen(data1);
	if (size != strlen(data2))
		return 0;

	
	for (int i = 0; i < size; i++) {
		if ('A' <= data1[i] && data1[i] <= 'Z') {
			data1[i] += 32;
		}
		if ('A' <= data2[i] && data2[i] <= 'Z') {
			data2[i] += 32;
		}
	}

	for (int i = 0; i < size; i++) 
		if (data1[i] != data2[i])
			return 0;
	return 1;
}

int main() {
	char* p[2];
	char imsi[101];
	int size;

	for (int i = 0; i < 2; i++) {
		printf("%d번째 문자열 : ", i + 1);
		gets(imsi);

		size = strlen(imsi);

		p[i] = (char*)malloc(sizeof(char) * size + 1);

		strcpy(p[i], imsi);
	}

	if (0 == my_strcmp(p[0], p[1]))
		printf("False");
	else printf("True");

	for (int i = 0; i < 2; i++)
		free(p[i]);

	return 0;
}