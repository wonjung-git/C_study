#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int s_sum = 0;
	float grade = 0;
	char temp[101];
	FILE* input;
	input = fopen("grade.txt", "r");
	
	for (;;) {
		fgets(temp, 101, input);
		if (feof(input))
			break;
		for (int i = 0; i < strlen(temp); i++) {
			if ('0' <= temp[i] && temp[i] <= '9')
				s_sum += (temp[i] - '0');

			if ('0' == temp[i]) {
				switch (temp[i - 1]) {
				case 'A': grade += 4;
					break;
				case 'B': grade += 3;
					break;
				case 'C': grade += 2;
					break;
				case 'D': grade += 1;
					break;
				}
					
			}
			else if (temp[i] == '+') {
				switch (temp[i - 1]) {
				case 'A': grade += 4.5;
					break;
				case 'B': grade += 3.5;
					break;
				case 'C': grade += 2.5;
					break;
				case 'D': grade += 1.5;
					break;
				}

			}
				
		}
	}
	fclose(input);

	printf("ÃÑ ÆòÁ¡ : %.2f", grade / s_sum);
	printf("\n¼ºÀû ÃÑÇÕ : %.2f\nÇÐÁ¡ ÃÑÇÕ : %d", grade, s_sum);


	fclose(input);
	return 0;
}