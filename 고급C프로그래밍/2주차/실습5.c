#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort_Ascending(int data[100]) {
	for (int i = 0; i < 100; i++) {
		for (int j = i; j < 100; j++) {
			if (data[i] >= data[j])
				swap(&data[i], &data[j]);
		}
	}
}

void sort_Descending(int data[100]) {
	for (int i = 0; i < 100; i++) {
		for (int j = i; j < 100; j++) {
			if (data[i] <= data[j])
				swap(&data[i], &data[j]);
		}
	}
}

int main() {
	int data[100], a;
	for (int i = 0; i < 100; i++)
		data[99 - i] = i;
	printf("정렬방식 입력(오름차순=0, 내림차순=1) : ");
	scanf("%d", &a);

	printf("Before : ");
	for (int i = 0; i < 100; i++)
		printf(" %d", data[i]);

	if (a == 0)
		sort_Ascending(data);
	else if (a == 1)
		sort_Descending(data);
	else printf("0 또는 1로 입력해주세요.");

	printf("\n\nafter : ");
	for (int i = 0; i < 100; i++)
		printf(" %d", data[i]);
}