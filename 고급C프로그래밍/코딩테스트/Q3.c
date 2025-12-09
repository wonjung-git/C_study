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
			printf("잘못된 ID입니다 다시 시도하세요.\n");
			fclose(input);
		}
	}
}

struct rental_history {
	char* user_name;
	char* bike_name;
	int tot;
};

struct bike {
	char* name;
	int num;
	int price;
	int tot;
};

struct bike* read_bikes_list_v2() {
	FILE* input = fopen("bikes_v2.txt", "r");
	char temp[101];
	const char* delim = "\t\n";
	struct bike* bike_list = NULL;
	bike_num = 0;

	while (fgets(temp, 100, input) != NULL) {
		char* tok = strtok(temp, delim);

		bike_list = (struct bike*)realloc(bike_list, sizeof(struct bike) * (bike_num + 1));
		bike_list[bike_num].name = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
		strcpy(bike_list[bike_num].name, tok);

		tok = strtok(NULL, delim);
		bike_list[bike_num].price = atoi(tok);
		tok = strtok(NULL, delim);
		bike_list[bike_num].tot = atoi(tok);
		bike_list[bike_num].num = bike_num;

		bike_num++;
	}

	fclose(input);
	return bike_list;
}

void save_rental_history(struct bike* rental_list) {
	FILE* input = fopen("rental_history.txt", "r");
	char temp[101];
	const char* delim = "\t\n";
	struct rental_history* rental_history = NULL;
	int n = 0;
	if (input != NULL) {
		while (fgets(temp, 100, input) != NULL) {
			char* tok = strtok(temp, delim);

			rental_history = (struct rental_history*)realloc(rental_history, sizeof(struct rental_history) * (n + 1));
			rental_history[n].user_name = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(rental_history[n].user_name, tok);

			tok = strtok(NULL, delim);
			rental_history[n].bike_name = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(rental_history[n].bike_name, tok);

			tok = strtok(NULL, delim);
			rental_history[n].tot = atoi(tok);

			n++;
		}
		fclose(input);
	}


	for (int i = 0; i < rental_num; i++) {
		int found = 0;
		for (int j = 0; j < n; j++) {
			if (!strcmp(rental_history[j].user_name, user_id) && !strcmp(rental_history[j].bike_name, rental_list[i].name)) {
				rental_history[j].tot += rental_list[i].tot;
				found = 1;
				break;
			}
		}
		if (!found) {
			rental_history = (struct rental_history*)realloc(rental_history, sizeof(struct rental_history) * (n + 1));
			rental_history[n].user_name = (char*)malloc(sizeof(char) * (strlen(user_id) + 1));
			strcpy(rental_history[n].user_name, user_id);

			rental_history[n].bike_name = (char*)malloc(sizeof(char) * (strlen(rental_list[i].name) + 1));
			strcpy(rental_history[n].bike_name, rental_list[i].name);

			rental_history[n].tot = rental_list[i].tot;

			n++;
		}
	}

	FILE* output = fopen("rental_history.txt", "w");
	for (int i = 0; i < n; i++) {
		fprintf(output, "%s\t%s\t%d\n", rental_history[i].user_name, rental_history[i].bike_name, rental_history[i].tot);
	}

	fclose(output);
	for (int i = 0; i < n; i++) {
		free(rental_history[i].user_name);
		free(rental_history[i].bike_name);
	}
	free(rental_history);
}

void write_updated_bikes(struct bike* bike_list) {
	FILE* output = fopen("bikes_v2.txt", "w");
	for (int i = 0; i < bike_num; i++) {
		fprintf(output, "%s\t%d\t%d\n", bike_list[i].name, bike_list[i].price, bike_list[i].tot);
	}
	fclose(output);
}

void user_mode() {
	struct bike* bike_list = read_bikes_list_v2();

	while (1) {
		struct bike* rental_list = NULL;
		int num, sum = 0;

		printf("=== 대여 가능 자전거 목록 ===\n");
		printf("번호 | 자전거 이름       | 비용 | 재고\n");

		for (int i = 0; i < bike_num; i++) {
			if (bike_list[i].tot != 0)
				printf("%d | %22s | %d | %d\n", bike_list[i].num, bike_list[i].name, bike_list[i].price, bike_list[i].tot);
		}

		while (1) {

			printf("대여할 자전거 번호 (-1입력시 대여 확정)");
			scanf("%d", &num);

			if (num == -1) {
				printf("\n=== 이번 세션 대여 내역 ===\n");
				printf("번호 | 자전거 이름       | 수량 | 비용 | 합계\n");
				for (int i = 0; i < rental_num; i++) {
					int subtotal = rental_list[i].tot * rental_list[i].price;
					sum += subtotal;
					printf("%d | %22s | %d | %d | %d\n", i + 1, rental_list[i].name, rental_list[i].tot, rental_list[i].price, subtotal);
				}
				printf("총 결제 금액 : %d\n", sum);
				break;
			}
			else if (num < 0 || num >= bike_num) {
				printf("존재하지 않는 자전거 번호입니다. 다시 입력하세요.\n");
			}
			else if (bike_list[num].tot == 0) {
				printf("재고가 부족한 자전거 입니다.\n");
			}
			else {
				printf("\"%s\"자전거가 대여 목록에 추가되었습니다.\n", bike_list[num].name);

				int idx = -1;
				for (int i = 0; i < rental_num; i++) {
					if (!strcmp(rental_list[i].name, bike_list[num].name)) {
						idx = i;
						break;
					}
				}
				if (idx == -1) {
					rental_list = (struct bike*)realloc(rental_list, sizeof(struct bike) * (rental_num + 1));
					rental_list[rental_num].name = (char*)malloc(sizeof(char) * (strlen(bike_list[num].name) + 1));
					strcpy(rental_list[rental_num].name, bike_list[num].name);
					rental_list[rental_num].price = bike_list[num].price;
					rental_list[rental_num].num = rental_num;
					rental_list[rental_num].tot = 0;
					idx = rental_num;
					rental_num++;
				}

				bike_list[num].tot--;
				rental_list[idx].tot++;
			}
		}

		save_rental_history(rental_list);

		for (int i = 0; i < rental_num; i++)
			free(rental_list[i].name);
		free(rental_list);
		break;
	}

	write_updated_bikes(bike_list);
	for (int i = 0; i < bike_num; i++)
		free(bike_list[i].name);
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