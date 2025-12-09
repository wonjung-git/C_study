#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bike_num;
int rental_num = 0;
char user_id[21];
enum mode { admin, user, fail};

struct user {
	char* id;
	char* password;
	char* bool;
};

struct rental_history {
	char* user_name;
	char* bike_name;
	int tot;
};

struct rental_history_admin {
	char* user_name;
	char* bike_name;
	int tot;
	int num;
};

struct bike {
	char* name;
	int num;
	int price;
	int tot;
};

void user_free(struct user* user, int n) {
	for (int j = 0; j < n; j++) {
		free(user[j].id);
		free(user[j].password);
		free(user[j].bool);
	}
	free(user);
}

int read_admin() {
	FILE* input = fopen("admin.txt", "r");

	char password[21], admin_code[21];

	if (input != NULL) {
		fscanf(input, "%s", admin_code);
		printf("관리자 모드로 접속을 시도했습니다.\n");
		printf("관리자 인증 코드를 입력하세요 : ");
		scanf("%s", password);

		fclose(input);
		if (!strcmp(password, admin_code))
			return 1;
		else return 0;
	}
	else printf("파일이 없습니다.");
}

int read_user() {
	FILE* input = fopen("user_v2.txt", "r");
	char temp[101];
	const char* delim = "\t\n";
	struct user* user = NULL;
	int n = 0;
	if (input != NULL) {
		while (fgets(temp, 100, input) != NULL) {
			char* tok = strtok(temp, delim);

			user = (struct user*)realloc(user, sizeof(struct user) * (n + 1));
			user[n].id = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(user[n].id, tok);

			tok = strtok(NULL, delim);
			user[n].password = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(user[n].password, tok);

			tok = strtok(NULL, delim);
			user[n].bool = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(user[n].bool, tok);

			n++;
		}
	}
	else {
		printf("파일이 없습니다.");
		return 0;
	}

	while (1) {
		printf("로그인 아이디를 입력하세요 : ");
		scanf("%20s", user_id);

		int id_found = -1;
		for (int i = 0; i < n; i++) {
			if (!strcmp(user_id, user[i].id)) {
				id_found = i;
				break;
			}
		}

		if (id_found != -1) {
			for (int i = 1; i < 4; i++) {
				char password[21];
				printf("비밀번호를 입력하세요 : ");
				scanf("%s", password);

				if (!strcmp(password, user[id_found].password)) {
					if (!strcmp("o", user[id_found].bool)) {
						fclose(input);
						user_free(user, n);
						return 1;
					}
					else {
						printf("계정이 잠겨 있습니다. 프로그램을 종료합니다.");
						fclose(input);
						user_free(user, n);
						return 0;
					}
				}
				else {
					printf("비밀번호가 틀렸습니다. (%d/3)\n", i);
				}
			}
			strcpy(user[id_found].bool, "x");
			FILE* output = fopen("user_v2.txt", "w");
			for (int i = 0; i < n; i++) {
				fprintf(output, "%s\t%s\t%s\n", user[i].id, user[i].password, user[i].bool);
			}
			printf("3회 실패로 계정이 잠깁니다.\n");
			printf("계정이 잠겨 프로그램을 종료합니다.");
			fclose(output);
			fclose(input);
			user_free(user, n);
			return 0;
		}
		else {
			printf("존재하지 않는 ID입니다. 다시 입력해주세요.\n");
		}
	}
}

enum mode check_access(enum mode m) {

	if (m == admin) {
		while (1) {
			if (read_admin()) {
				printf("관리자 인증 성공!\n");
				return admin;
			}
			else printf("잘못된 코드 입니다. 다시입력하세요.\n");
		}
	}
	else {
		if (read_user()) {
			return user;
		}
		else return fail;
	}
}

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
	int choice;
	struct bike* bike_list = read_bikes_list_v2();

	while (1) {
		printf("--- 사용자 모드 ---\n");
		printf("1. 자전거 대여\n");
		printf("2. 자전거 반납\n");
		printf("선택 : ");
		scanf("%d", &choice);

		if (choice == 1) {
			struct bike* rental_list = NULL;
			int num, sum = 0;
			rental_num = 0;

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
		else if (choice == 2) {
			FILE* input = fopen("rental_history.txt", "r");
			char temp[101];
			const char* delim = "\t\n";
			struct rental_history_admin* rental_history_user = NULL;
			struct rental_history* rental_history = NULL;
			int n = 0, rental_n = 0;

			if (input != NULL) {
				while (fgets(temp, 100, input) != NULL) {
					//전체 rental_history저장
					char* tok = strtok(temp, delim);

					rental_history = (struct rental_history*)realloc(rental_history, sizeof(struct rental_history) * (n + 1));
					rental_history[n].user_name = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
					strcpy(rental_history[n].user_name, tok);

					tok = strtok(NULL, delim);
					rental_history[n].bike_name = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
					strcpy(rental_history[n].bike_name, tok);

					tok = strtok(NULL, delim);
					rental_history[n].tot = atoi(tok);

					if (!strcmp(rental_history[n].user_name, user_id) && rental_history[n].tot != 0) {
						rental_history_user = (struct rental_history_admin*)realloc(rental_history_user, sizeof(struct rental_history_admin) * (rental_n + 1));
						rental_history_user[rental_n].user_name = (char*)malloc(sizeof(char) * (strlen(user_id) + 1));
						strcpy(rental_history_user[rental_n].user_name, user_id);

						rental_history_user[rental_n].bike_name = (char*)malloc(sizeof(char) * (strlen(rental_history[n].bike_name) + 1));
						strcpy(rental_history_user[rental_n].bike_name, rental_history[n].bike_name);

						rental_history_user[rental_n].tot = rental_history[n].tot;
						rental_history_user[rental_n].num = rental_n;
						rental_n++;
					}

					n++;
				}
			}
			else {
				printf("파일이 없습니다.\n");
				break;
			}

			printf("=== %s님의 미반납 목록 ===\n", user_id);
			for (int i = 0; i < rental_n; i++) {
				printf("[%d] %s - %d대 미반납\n", rental_history_user[i].num, rental_history_user[i].bike_name, rental_history_user[i].tot);
			}

			while (1) {
				printf("반납할 번호(-1 종료): ");
				scanf("%d", &choice);

				if (choice == -1) {
					printf("반납완료\n");
					break;
				}
				else if (choice < 0 || choice >= rental_n) {
					printf("잘못된 번호입니다. 다시 입력하세요.\n");
					continue;
				}
				else {
					int tot;
					printf("반납할 수량 입력: ");
					scanf("%d", &tot);
					if (tot > rental_history_user[choice].tot) {
						printf("반납 요청 수량이 대여 중인 대수보다 많습니다. 가능한 %d대만 반납합니다.\n", rental_history_user[choice].tot);
						printf("\"%s\" %d대 반납 완료\n", rental_history_user[choice].bike_name, rental_history_user[choice].tot);


						for (int i = 0; i < bike_num; i++) {
							if (!strcmp(bike_list[i].name, rental_history_user[choice].bike_name)) {
								bike_list[i].tot += rental_history_user[choice].tot;
								rental_history_user[choice].tot = 0;
								break;
							}
						}
					}
					else if (tot < 1) {
						printf("1이상의 값을 입력해주세요.\n");
						continue;
					}
					else {
						printf("\"%s\" %d대 반납 완료\n", rental_history_user[choice].bike_name, tot);

						for (int i = 0; i < bike_num; i++) {
							if (!strcmp(bike_list[i].name, rental_history_user[choice].bike_name)) {
								bike_list[i].tot += tot;
								rental_history_user[choice].tot -= tot;
								break;
							}
						}
					}
				}
			}

			for (int i = 0; i < rental_n; i++) {
				for (int j = 0; j < n; j++) {
					if (!strcmp(rental_history[j].user_name, rental_history_user[i].user_name) && !strcmp(rental_history[j].bike_name, rental_history_user[i].bike_name)) {
						rental_history[j].tot = rental_history_user[i].tot;
						break;
					}
				}
			}

			FILE* output = fopen("rental_history.txt", "w");
			for (int i = 0; i < n; i++) {
				fprintf(output, "%s\t%s\t%d\n", rental_history[i].user_name, rental_history[i].bike_name, rental_history[i].tot);
			}
			fclose(output);
			fclose(input);
			for (int i = 0; i < rental_n; i++) {
				free(rental_history_user[i].bike_name);
				free(rental_history_user[i].user_name);
			}
			free(rental_history_user);
			for (int i = 0; i < n; i++) {
				free(rental_history[i].bike_name);
				free(rental_history[i].user_name);
			}
			free(rental_history);
			break;
		}
		else printf("다시 입력해주세요.\n");
	}

	write_updated_bikes(bike_list);
	for (int i = 0; i < bike_num; i++)
		free(bike_list[i].name);
	free(bike_list);

}

void admin_mode() {
	FILE* input = fopen("rental_history.txt", "r");
	char temp[101];
	const char* delim = "\t\n";
	struct rental_history_admin* rental_history = NULL;
	int n = 0;
	if (input != NULL) {
		while (fgets(temp, 100, input) != NULL) {
			char* tok = strtok(temp, delim);

			rental_history = (struct rental_history_admin*)realloc(rental_history, sizeof(struct rental_history_admin) * (n + 1));
			rental_history[n].user_name = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(rental_history[n].user_name, tok);

			tok = strtok(NULL, delim);
			rental_history[n].bike_name = (char*)malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(rental_history[n].bike_name, tok);

			tok = strtok(NULL, delim);
			rental_history[n].tot = atoi(tok);
			rental_history[n].num = n;
			n++;
		}
		fclose(input);
	}
	else {
		printf("파일이 없습니다.\n");
	}


	int choice;
	while (1) {
		printf("--- 관리자 모드 ---\n");
		printf("1. 전체 대여 기록 조회\n");
		printf("2. 미반납 사용자 조회\n");
		printf("선택 : ");
		scanf("%d", &choice);

		if (choice == 1) {
			printf("=== 전체 대여 기록 ===\n");
			for (int i = 0; i < n; i++) {
				printf("%s - %s : %d대\n", rental_history[i].user_name, rental_history[i].bike_name, rental_history[i].tot);
			}
			break;
		}
		else if (choice == 2) {
			printf("=== 미반납 사용자 ===\n");
			for (int i = 0; i < n; i++) {
				if (rental_history[i].tot != 0)
					printf("%s - %s : %d대\n", rental_history[i].user_name, rental_history[i].bike_name, rental_history[i].tot);
			}
			break;
		}
		else printf("다시 입력해주세요.\n");
	}


	for (int i = 0; i < n; i++) {
		free(rental_history[i].user_name);
		free(rental_history[i].bike_name);
	}
	free(rental_history);
}

int main(int argc, char* argv[]) {
	enum mode m;	

	if (argc > 1) {
		if (!strcmp(argv[1], "admin\0"))
			m = check_access(admin);
		else {
			printf("잘못된 관리자 아이디 입니다.\n");
			return 0;
		}
	}
	else 
		m = check_access(user);

	
	if (m == user) {
		printf("사용자 모드입니다.\n");
		user_mode();
	}
	else if(m == admin){
		printf("관리자 모드입니다.\n");
		admin_mode();
	}

	return 0;
}