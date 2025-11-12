#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
	char** name;
	int* cnt;
};
struct book book;
struct book storage;

int book_cnt = 0;
int storage_book_cnt = 0;

void storage_initial_booklist() {
	FILE* input = fopen("storage.txt", "r");
	char temp[51];
	storage.name = (char**)malloc(sizeof(char) * 1);
	storage.cnt = (int*)malloc(sizeof(int) * 1);
	fgets(temp, 101, input);

	while (1) {
		fgets(temp, 101, input);

		storage_book_cnt++;
		storage.name = (char**)realloc(storage.name, sizeof(char*) * storage_book_cnt);
		storage.cnt = (int*)realloc(storage.cnt, sizeof(int) * storage_book_cnt);

		//책 제목 글자수 계산
		int name_max;
		for (name_max = strlen(temp) - 2; ; name_max--)
			if (('a' <= temp[name_max] && temp[name_max] <= 'z') || ('A' <= temp[name_max] && temp[name_max] <= 'Z'))
				break;

		//책 개수 계산
		int i_temp, i;
		char cnt[11];
		for (i_temp = strlen(temp) - 1; ; i_temp--) {
			if (temp[i_temp] == ' ')
				break;
		}
		for (i = 0; i < strlen(temp) - i_temp; i++) {
			cnt[i] = temp[i_temp + i + 1];
		}
		cnt[i] = '\0';
		storage.cnt[storage_book_cnt - 1] = atoi(cnt);

		temp[name_max + 1] = '\0';
		storage.name[storage_book_cnt - 1] = (char*)malloc(sizeof(char*) * (name_max + 2));

		strcpy(storage.name[storage_book_cnt - 1], temp);

		if (feof(input))
			break;
	}

	fclose(input);

}

void initial_booklist() {
	FILE* input = fopen("books.txt", "r");
	char temp[41];
	book.name = (char**)malloc(sizeof(char) * 1);
	book.cnt = (int*)malloc(sizeof(int) * 1);
	fgets(temp, 101, input);

	while (1) {
		fgets(temp, 101, input);

		book_cnt++;
		book.name = (char**)realloc(book.name, sizeof(char*) * book_cnt);
		book.cnt = (int*)realloc(book.cnt, sizeof(int) * book_cnt);

		//책 제목 글자수 계산
		int name_max;
		for (name_max = strlen(temp) - 2; ; name_max--)
			if (('a' <= temp[name_max] && temp[name_max] <= 'z') || ('A' <= temp[name_max] && temp[name_max] <= 'Z'))
				break;

		for (int i = strlen(temp) - 1; ; i--)
			if ('0' <= temp[i] && temp[i] <= '9') {
				book.cnt[book_cnt - 1] = temp[i] - '0';
				break;
			}

		temp[name_max + 1] = '\0';
		book.name[book_cnt - 1] = (char*)malloc(sizeof(char*) * (name_max + 2));

		strcpy(book.name[book_cnt - 1], temp);

		if (feof(input))
			break;
	}

	fclose(input);

}

manage_booklist(int id) {
	if (0 < id && id <= book_cnt) {
		if (book.cnt[id - 1] > 0) {
			printf("\n대여 되었습니다.\n");
			book.cnt[id - 1]--;
		}
		else {
			printf("\n대여 가능한 책이 없습니다.\n");
		}
	}
	else printf("\n존재하지 않는 id입니다.\n");

}

print_booklist() {
	printf("\n\n======현재 보유 도서 목록======\n");
	printf("id |   \t\t책이름\t\t   | 보유권수\n");

	for (int i = 0; i < book_cnt; i++)
		printf("%d | %33s | %d\n", i + 1, book.name[i], book.cnt[i]);
}

storage_print_booklist() {
	printf("\n\n======창고 보유 도서 목록======\n");
	printf("id |   \t\t책이름\t\t   | 보유권수\n");

	for (int i = 0; i < storage_book_cnt; i++)
		printf("%d | %33s | %d\n", i + 1, storage.name[i], storage.cnt[i]);
}


admin_check() {
	FILE* input;
	char temp[101], id[21], pw[31], id_u[21], pw_u[31];
	int u;
	input = fopen("admin_auth.txt", "r");

	//ID전처리
	fgets(temp, 100, input);
	for (int i = 4; temp[i] != '\n' && temp[i] != '\0'; i++)
		id[i - 4] = temp[i];
	id[strlen(temp) - 5] = '\0';


	//PW전처리
	fgets(temp, 100, input);
	for (int i = 4; temp[i] != '\n' && temp[i] != '\0'; i++)
		pw[i - 4] = temp[i];
	pw[strlen(temp) - 4] = '\0';

	fclose(input);

	while (1) {
		printf("관리자 ID입력 : ");
		scanf("%s", id_u);
		printf("관리자 PW입력 : ");
		scanf("%s", pw_u);

		if (!strcmp(id_u, id) && !strcmp(pw_u, pw)) {
			admin_book();
			printf("종료할까요?(1:사용자모드 전환, 0:종료) : ");
			scanf("%d", &u);
			return u;
		}
		else printf("id또는 pw가 잘못되었습니다.");
	}

}

admin_book() {
	printf("\n업데이트 전 보유현황");
	print_booklist();

	for (int i = 0; i < book_cnt; i++) {
		if (book.cnt[i] == 0) {
			for(int j=0; j<storage_book_cnt; j++) {
				if (!strcmp(book.name[i], storage.name[j])) {
					for (int k = 0; k < 3; k++) {
						if (storage.cnt[j] > 0) {
							storage.cnt[j]--;
							book.cnt[i]++;
						}
						else break;
					}
					break;
				}
			}
		}
	}

	printf("\n\n업데이트 후 보유현황");
	print_booklist();
	storage_print_booklist();
}

int main(int argc, char* argv[]) {
	int id;
	initial_booklist();
	storage_initial_booklist();

	if (argc > 1)
		if (!strcmp(argv[1], "admin")) {
			if (0 == admin_check())
				return 0;
		}

	while (1) {
		print_booklist();

		printf("어떤 책을 대여하시겠어요?(id 입력 / -1 입력시 대여 종료) : ");
		scanf("%d", &id);
		if (id == -1)
			break;
		manage_booklist(id);
	}

	


	for (int i = 0; i < book_cnt; i++) {
		free(book.name[i]);
	}
	free(book.name);
	free(book.cnt);

	for (int i = 0; i < storage_book_cnt; i++) {
		free(storage.name[i]);
	}
	free(storage.name);
	free(storage.cnt);
	return 0;
}
