#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

int main() {
	FILE *input, *output;
	char** menu = (char**)malloc(sizeof(char*) * 1);
	char temp[101], i_temp[5];
	int* price, i, item, price_hap=0;
	input = fopen("menu.txt", "r");
	output = fopen("receipt.txt", "w");

	
	price = (int*)malloc(sizeof(int) * 1);

	fgets(temp, 101, input); //첫 줄 삭제

	for (i=1;;i++) {
		fgets(temp, 101, input);
		if (feof(input))
			break;
		menu = (char**)realloc(menu, sizeof(char*) * i);
		price = (int*)realloc(price, sizeof(int) * i);
		menu[i-1] = (char*)malloc(sizeof(char) * 1);

		for (int j = 0; j < strlen(temp); j++) {
			//메뉴 이름 전처리
			if (('A' <= temp[j] && temp[j] <= 'Z') || ('a' <= temp[j] && temp[j] <= 'z') || temp[j] == '_') {
				menu[i-1] = (char*)realloc(menu[i-1], sizeof(char) * (j + 1));
				menu[i - 1][j] = temp[j];
				if (temp[j+1] == ' ' || temp[j+1] == '\t')
					menu[i - 1][j + 1] = '\0';
			}
			//가격 전처리
			else if ('0' <= temp[j] && temp[j] <= '9') {
				for (int k =0; k < 4; k++)
					i_temp[k] = temp[j+k];
				i_temp[4] = '\0';
				price[i - 1] = atoi(i_temp);
				break;
			}
		}
	}

	while (1) {
		printf("[			menu :			PRICE]");

		for (int l = 1; l < i; l++)
			printf("\n[%d]%25s :%23d]\n", l, menu[l - 1], price[l - 1]);

		printf("메뉴를 고르세요, 주문완료는 0을 누르세요 : ");
		scanf("%d", &item);

		if (item == 0) {
			break;
		}
		else if (item < i) {
			printf("%s, 주문 받았습니다.\n", menu[item - 1]);
			fprintf(output, "%s : %d\n", menu[item - 1], price[item - 1]);
			price_hap += price[item - 1];
		}
		else {
			printf("없는 메뉴입니다. 다시 입력해주세요\n");
		}
	}
	fprintf(output, "\nprice total : %d", price_hap);
	
	//이거 쓰실분들 메모리 free()해주세요. 귀찮아서 그건 안쓸게요..

	fclose(input);
	fclose(output);
	return 0;
}