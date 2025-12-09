#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bike_num;
int rental_num = 0;
char user_id[21];
enum mode { admin, user };

enum mode check_access() {
	char login[21];
	while (1) {
		printf("로그인 아이디를 입력하세요 : ");
		scanf("%20s", login);

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

char** read_bikes_list() {
	FILE* input = fopen("bikes.txt", "r");
	char temp[101];
	char** bike_list = NULL;
	bike_num = 0;

	while (fgets(temp, 100, input) != NULL) {
		int len = strlen(temp);
		if (len > 0 && temp[len - 1] == '\n') {
			temp[len - 1] = '\0';
		}

		bike_list = (char**)realloc(bike_list, sizeof(char*) * (bike_num + 1));
		bike_list[bike_num] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
		strcpy(bike_list[bike_num], temp);
		bike_num++;
	}

	fclose(input);
	return bike_list;
}

void user_mode() {
	char** bike_list = read_bikes_list();
	char** rental_list = NULL;
	int num;

	printf("=== 자전거 목록 ===\n");
	for (int i = 0; i < bike_num; i++) {
		printf("[%d] %s\n", i, bike_list[i]);
	}

	while (1) {

		printf("대여할 자전거 번호 (-1입력시 대여 확정)");
		scanf("%d", &num);

		if (num == -1) {
			printf("\n=== 대여 확인서 ===\n");
			for (int i = 0; i < rental_num; i++) {
				printf("%d. %s\n", i + 1, rental_list[i]);
			}
			break;
		}
		else if (num < 0 || num >= bike_num) {
			printf("존재하지 않는 자전거 번호입니다. 다시 입력하세요.");
		}
		else {
			printf("\"%s\"자전거가 대여 목록에 추가되었습니다.", bike_list[num]);
			rental_list = (char**)realloc(rental_list, sizeof(char*) * (rental_num + 1));
			rental_list[rental_num] = (char*)malloc(sizeof(char) * (strlen(bike_list[num]) + 1));
			strcpy(rental_list[rental_num], bike_list[num]);
			rental_num++;
		}
	}

	for (int i = 0; i < rental_num; i++)
		free(rental_list[i]);
	free(rental_list);
	for (int i = 0; i < bike_num; i++)
		free(bike_list[i]);
	free(bike_list);
}

int main() {

	if (check_access() == user) {
		printf("사용자 모드입니다.\n");
		user_mode();
	}
	else {
		printf("관리자 모드입니다.\n");
	}

	return 0;
}