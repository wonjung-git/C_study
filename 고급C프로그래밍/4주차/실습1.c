#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

int main() {
	int* p;
	int hap = 0, cnt;

	printf("입력할 개수는 ? ");
	scanf("%d", &cnt);

	p = (int*)malloc(4 * cnt);

	for (int i = 0; i < cnt; i++) {
		printf("%d번째 숫자 : ", i+1);
		scanf("%d", p + i);
	}

	for (int i = 0; i < cnt; i++) {
		if (*(p + i) % 2 == 0)
			hap += *(p + i);
	}

	printf("입력한 짝수 합 ==> %d", hap);
	free(p);

	return 0;
}