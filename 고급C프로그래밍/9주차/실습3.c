#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
	char** name;
	int* cnt;
}book;

int book_cnt = 0;

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
			book.cnt[id-1]--;
		}
		else {
			printf("\n대여 가능한 책이 없습니다.\n");
		}
	}
	else printf("\n존재하지 않는 id입니다.\n");
	
}

int main() {
	int id;
	initial_booklist();

	while (1) {
		printf("\n\n======현재 보유 도서 목록======\n");
		printf("id |   \t\t책이름\t\t   | 보유권수\n");

		for (int i = 0; i < book_cnt; i++)
			printf("%d | %33s | %d\n", i + 1, book.name[i], book.cnt[i]);

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

	return 0;
}
