#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	FILE* output;
	int dan_n;
	char dan[3], path[101];
	printf("출력하고 싶은 단을 입력 : ");
	scanf("%s", dan);

	strcpy(path, dan);
	strcat(path, "_dan.txt");
	dan_n = atoi(dan);
	output = fopen(path, "w");

	for (int i = 1; i < 10; i++) {
		fprintf(output, "%d X %d = %d\n", dan_n, i, dan_n * i);
	}

	fclose(output);

	return 0;
}