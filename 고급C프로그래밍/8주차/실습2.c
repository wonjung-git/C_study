#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	struct student {
		char name[101];
		int old;
	};
	int s_num;
	printf("입력할 학생 수 : ");
	scanf("%d", &s_num);

	struct student* s = (struct student*)malloc(sizeof(struct student) * s_num);

	for (int i = 0; i < s_num; i++) {
		printf("이름과 나이 입력 : ");
		scanf("%s", s[i].name);
		getchar();
		scanf("%d", &s[i].old);
		getchar();
	}

	printf("\n-- 학생 명단 --");
	for (int i = 0; i < s_num; i++) {
		printf("\n이름:%s , 나이:%d", s[i].name, s[i].old);
	}

	free(s);
	return 0;
}