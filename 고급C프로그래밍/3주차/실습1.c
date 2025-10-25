#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int my_strcmp(char data1[101], char data2[101]) {
	for (int i = 0; data1[i] != '\0' || data2[i] != '\0'; i++) {
		if (data1[i] - data2[i] > 0) {
			return 1;
		}
		else if (data1[i] - data2[i] < 0) {
			return -1;
		}
	}
	return 0;
}

void my_strcat(char data1[101], char data2[101], char *cat_arr) {
	int i = 0, j=0;
	while (data1[i] != '\0') {
		*(cat_arr + i) = data1[i];
		i++;
	}
	while (data2[j] != '\0') {
		*(cat_arr + i) = data2[j];
		i++;
		j++;
	}
}

void my_strcpy(char data1[101], char *cpy_arr) {
	int i = 0;
	while (data1[i] != '\0') {
		*(cpy_arr + i) = data1[i];
		i++;
	}
}

int main() {
	char data1[101] = { 0, }, data2[101] = { 0, }, cat_arr[201] = { 0, }, cpy_arr[101] = { 0, };
	printf("첫번째 문자열 : ");
	scanf("%s", data1);
	printf("두번째 문자열 : ");
	scanf("%s", data2);

	printf("\nmy_strcmp결과 : %d", my_strcmp(data1, data2));

	my_strcat(data1, data2, cat_arr);
	printf("\nmy_strcat결과 : %s", cat_arr);

	my_strcpy(data1, cpy_arr);
	printf("\nmy_strcpy결과 : %s", cpy_arr);

	return 0;
}