#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

int main() {
	int* p;
	int hap = 0, cnt;

	printf("�Է��� ������ ? ");
	scanf("%d", &cnt);

	p = (int*)malloc(4 * cnt);

	for (int i = 0; i < cnt; i++) {
		printf("%d��° ���� : ", i+1);
		scanf("%d", p + i);
	}

	for (int i = 0; i < cnt; i++) {
		if (*(p + i) % 2 == 0)
			hap += *(p + i);
	}

	printf("�Է��� ¦�� �� ==> %d", hap);
	free(p);

	return 0;
}