#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main() {
	char* p[3];
	char imsi[101];
	int size;

	for (int i = 0; i < 3; i++) {
		printf("%d��° ���ڿ� : ", i + 1);
		gets(imsi);
		
		size = strlen(imsi);
		p[i] = (char*)malloc(sizeof(char)*size + 1);

		strcpy(p[i], imsi);
	}
	printf("\n-- �Է°� �ݴ�� ���(������) : ���� ������ �Ųٷ� --\n");

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