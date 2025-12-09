#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char user_id[21];
enum mode { admin, user };

enum mode check_access() {
	char login[21];
	while (1) {
		printf("로그인 아이디를 입력하세요 : ");
		scanf("%s", login);

		if (!strcmp(login, "admin\0")) {
			return admin;
		}
		else {
			FILE* input = fopen("user.txt", "r");

			while (fscanf(input, "%s", user_id) == 1) {
				if (!strcmp(login, user_id)) {
					fclose(input);
					return user;
				}
			}
			fclose(input);
			printf("잘못된 ID입니다 다시 시도하세요.\n");
		}
	}
}

int main() {

	if (check_access() == user) {
		printf("사용자 모드입니다.");
	}
	else {
		printf("관리자 모드입니다.");
	}

	return 0;
}