#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	union id {
		char callnumber[15];
		char user_id[14];
	};

	struct user {
		char name[10];
		union id id;
	}user;

	printf("이름 --> ");
	scanf("%s", user.name);
	printf("전화번호 또는 주민번호 --> ");
	scanf("%s", user.id.callnumber);

	printf("%s\n%s", user.name, user.id.callnumber);

	return 0;
}