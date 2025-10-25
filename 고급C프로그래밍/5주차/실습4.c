#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main() {
	int num = 0, num_temp, size=1;
	char *p;
	printf("숫자를 입력하세요 : ");
	scanf("%d", &num);
	getchar();

	if (num == 1000) {
		printf("1000 = 1000 = M, 1");
		return 0;
	}
	num_temp = num;
	
	p = (char*)malloc(sizeof(char) * size);
	p[0] = '\0';

	//100단위
	if (num >= 900) {
		size += 2;
		p = (char*)realloc(p, sizeof(char) * size);
		strcat(p, "CM");
		num -= 900;
	}
	if (num >= 500) {
		size ++;
		p = (char*)realloc(p, sizeof(char) * size);
		strcat(p, "D");
		num -= 500;
	}
	if (num >= 400) {
		size += 2;
		p = (char*)realloc(p, sizeof(char) * size);
		strcat(p, "CD");
		num -= 400;
	}
	if (num >= 100) {
		while(num >= 100){
			size++;
			p = (char*)realloc(p, sizeof(char) * size);
			strcat(p, "C");
			num -= 100;
		}
	}

	//10단위
	if (num >= 90) {
		size += 2;
		p = (char*)realloc(p, sizeof(char) * size);
		strcat(p, "XC");
		num -= 90;
	}
	if (num >= 50) {
		size ++;
		p = (char*)realloc(p, sizeof(char) * size);
		strcat(p, "L");
		num -= 50;
	}
	if (num >= 40) {
		size += 2;
		p = (char*)realloc(p, sizeof(char) * size);
		strcat(p, "XL");
		num -= 40;
	}
	if (num >= 10) {
		while (num >= 10) {
			size++;
			p = (char*)realloc(p, sizeof(char) * size);
			strcat(p, "X");
			num -= 10;
		}
	}

	//1단위
	if (num >= 9) {
		size += 2;
		p = (char*)realloc(p, sizeof(char) * size);
		strcat(p, "IX");
		num -= 9;
	}
	if (num >= 5) {
		size ++;
		p = (char*)realloc(p, sizeof(char) * size);
		strcat(p, "V");
		num -= 5;
	}
	if (num >= 4) {
		size += 2;
		p = (char*)realloc(p, sizeof(char) * size);
		strcat(p, "IV");
		num -= 4;
	}
	if (num > 0) {
		while (num > 0) {
			size++;
			p = (char*)realloc(p, sizeof(char) * size);
			strcat(p, "I");
			num -= 1;
		}
	}

	printf("--로마 숫자--\n");
	printf("%d = ", num_temp);
	if (num_temp >= 100) {
		printf("%d", num_temp / 100 * 100);
		if ((num_temp % 100) >= 10) {
			printf(" + %d", (num_temp % 100) / 10 * 10);
			if ((num_temp % 100) % 10 >= 1)
				printf(" + %d", (num_temp % 100) % 10);
		}
	}
	else if ((num_temp % 100) >= 10) {
		printf("%d", (num_temp % 100) / 10 * 10);
		if ((num_temp % 100) % 10 >= 1)
			printf(" + %d", (num_temp % 100) % 10);
	}
	else if ((num_temp % 100) % 10 >= 1)
		printf("%d", (num_temp % 100) % 10);

	printf(" = %s, %d", p, size-1);

	free(p);
	return 0;
}