#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

struct drink {
	char** name;
	float *price;
	int* buy;
}drink;

struct dessert {
	char** name;
	float* price;
	int* buy;
}dessert;

print_receipt() {
	FILE* output;
	int i = 0;
	float price, price_hap=0;
	output = fopen("Receipt.txt", "w");

	fprintf(output, "======================\n       Receipt\n======================\n");

	for(int i=0; i<5; i++) {
		if (drink.buy[i] != 0) {
			price = drink.price[i] * drink.buy[i];
			fprintf(output, "%-20s%3d%10.2f\n", drink.name[i], drink.buy[i], price);
			price_hap += price;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (dessert.buy[i] != 0) {
			price = dessert.price[i] * dessert.buy[i];
			fprintf(output, "%-20s%3d%10.2f\n", dessert.name[i], dessert.buy[i], price);
			price_hap += price;
		}
	}
	fprintf(output, "======================\nTotal : %30.2f\n", price_hap);
	printf("영수증이 Receipt.txt에 저장되었습니다.");

	fclose(output);
}

dessert_count() {
	int item;
	printf("주문하실 디저트를 선택하세요\n");
	printf("\ndessert menues\n");
	for (int l = 1; l < 6; l++)
		printf("[%d] %-20s %3.2f\n", l, dessert.name[l - 1], dessert.price[l - 1]);

	scanf("%d", &item);

	if (item < 6)
		dessert.buy[item - 1]++;
	else printf("없는 메뉴입니다.");
}

drink_count() {
	int item;
	printf("주문하실 음료를 선택하세요\n");
	printf("\ndrink menues\n");
	for (int l = 1; l < 6; l++)
		printf("[%d] %-20s %3.2f\n", l, drink.name[l - 1], drink.price[l - 1]);

	scanf("%d", &item);

	if (item < 6)
		drink.buy[item - 1]++;
	else printf("없는 메뉴입니다.");
	
}

Initial_menulist() {
	
	FILE* input_drink, * input_dessert;
	drink.name = (char**)malloc(sizeof(char*) * 1);
	drink.price = (float*)malloc(sizeof(int) * 1);
	dessert.name = (char**)malloc(sizeof(char*) * 1);
	dessert.price = (float*)malloc(sizeof(int) * 1);
	char temp[101], i_temp[5];
	int i;
	input_drink = fopen("drink.txt", "r");
	input_dessert = fopen("dessert.txt", "r");

	//음료 전처리
	for (i = 1;; i++) {
		fgets(temp, 101, input_drink);

		drink.name = (char**)realloc(drink.name, sizeof(char*) * i);
		drink.price = (float*)realloc(drink.price, sizeof(int) * i);
		drink.name[i - 1] = (char*)malloc(sizeof(char) * 1);

		for (int j = 0; j < strlen(temp); j++) {
			//메뉴 이름 전처리
			if (('A' <= temp[j] && temp[j] <= 'Z') || ('a' <= temp[j] && temp[j] <= 'z') || temp[j] == '_') {
				drink.name[i - 1] = (char*)realloc(drink.name[i - 1], sizeof(char) * (j + 2));
				drink.name[i - 1][j] = temp[j];
				if (temp[j + 1] == ' ' || temp[j + 1] == '\t')
					drink.name[i - 1][j + 1] = '\0';
			}
			//가격 전처리
			else if (('0' <= temp[j] && temp[j] <= '9') || temp[j] == '.') {
				for (int k = 0; k < 4; k++)
					i_temp[k] = temp[j + k];
				i_temp[4] = '\0';
				drink.price[i - 1] = atof(i_temp);
				break;
			}
		}
		if (feof(input_drink))
			break;
	}
	drink.buy = (int*)calloc(i, sizeof(int));

	//디저트 전처리
	for (i = 1;; i++) {
		fgets(temp, 101, input_dessert);

		dessert.name = (char**)realloc(dessert.name, sizeof(char*) * i);
		dessert.price = (float*)realloc(dessert.price, sizeof(int) * i);
		dessert.name[i - 1] = (char*)malloc(sizeof(char) * 1);

		for (int j = 0; j < strlen(temp); j++) {
			//메뉴 이름 전처리
			if (('A' <= temp[j] && temp[j] <= 'Z') || ('a' <= temp[j] && temp[j] <= 'z') || temp[j] == '_') {
				dessert.name[i - 1] = (char*)realloc(dessert.name[i - 1], sizeof(char) * (j + 2));
				dessert.name[i - 1][j] = temp[j];
				if (temp[j + 1] == ' ' || temp[j + 1] == '\t')
					dessert.name[i - 1][j + 1] = '\0';
			}
			//가격 전처리
			else if (('0' <= temp[j] && temp[j] <= '9') || temp[j] == '.') {
				for (int k = 0; k < 4; k++)
					i_temp[k] = temp[j + k];
				i_temp[4] = '\0';
				dessert.price[i - 1] = atof(i_temp);
				break;
			}
		}
		if (feof(input_dessert))
			break;
	}
	dessert.buy = (int*)calloc(i, sizeof(int));
	
	fclose(input_dessert);
	fclose(input_drink);
}

int main() {
	int temp;
	Initial_menulist();

	while (1) {
	printf("1. 음료 주문하기\n2. 디저트 주문하기\n0. 종료\n:");
	scanf("%d", &temp);

	
		if (temp == 1)
			drink_count();
		else if (temp == 2)
			dessert_count();
		else if (temp == 0) {
			break;
		}
		else printf("숫자로 다시 입력해주세요.");
	}
	print_receipt();
	


	for (int i = 0; i < 5; i++) {
		free(drink.name[i]);
		free(dessert.name[i]);
	}
	free(drink.name);
	free(dessert.name);
	free(drink.price);
	free(dessert.price);
	free(drink.buy);
	free(dessert.buy);
	return 0;
}