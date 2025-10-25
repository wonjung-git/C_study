#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

int main() {
	int* p;
	int hap = 0, cnt=0, data;
	

	p = (int*)malloc(4 * 1);

	for (int i = 1; ; i++) {
		printf("%d번째 숫자 : ", i);
		scanf("%d", &data);

		if (data != 0) 
			p = (int*)realloc(p, 4 * i);
		
		else break;

		*(p + i-1) = data;
		cnt++;
	}

	for (int i = 0; i < cnt; i++) {
		if (*(p + i) % 2 == 0)
			hap += *(p + i);
	}

	printf("입력한 짝수 합 ==> %d", hap);
	free(p);

	return 0;
}