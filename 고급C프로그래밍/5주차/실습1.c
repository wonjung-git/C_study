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
		
		for (int i = 0; i < size; i++) 
			if ('A' <= imsi[i] && imsi[i] <= 'Z')
				imsi[i] += 32;
		
		p[i] = (char*)malloc(sizeof(char) * size + 1);

		strcpy(p[i], imsi);
	}
	printf("\n-- ��ҹ��� ��� --\n");

	for (int i = 0; i < 3; i++) {
		printf("\n%d\n�ҹ��� : %s", i+1, p[i]);
		for (int j = 0; j < size; j++)
			if ('a' <= p[i][j] && p[i][j] <= 'z')
				p[i][j] -= 32;
		printf("�빮�� : %s", p[i]);
	}
	for (int i = 0; i < 3; i++)
		free(p[i]);

	return 0;
}