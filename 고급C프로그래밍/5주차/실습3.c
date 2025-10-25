#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main() {
	char** p;
	char imsi[101];
	int size, t=0, *len, max_len=0;

	printf("입력할 문자열 개수 : ");
	scanf("%d", &t);
	getchar();
	p = (char**)malloc(sizeof(char*) * t);
	len = (int*)malloc(sizeof(int) * t);

	for (int i = 0; i < t; i++) {
		printf("%d번째 문자열 : ", i + 1);
		gets(imsi);

		size = strlen(imsi);
		len[i] = size;
		if (max_len < len[i])
			max_len = len[i];
		p[i] = (char*)malloc(sizeof(char) * size + 1);

		strcpy(p[i], imsi);
	}

	for (int j = 0; j < max_len; j++) {
		for (int i = 0; i < t; i++) {
			if (j <= len[i])
				printf("%c", p[i][j]);
		}
	}

	for (int i = 0; i < t; i++) {
		free(p[i]);   
	}
	free(len);        
	free(p);

	return 0;
}