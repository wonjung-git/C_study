#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int total_score(int* arr, int num) {
	int hap = 0;
	for (int i = 0; i < num; i++)
		switch (arr[i]) {
		case 11: hap += 10; break;
		case 12: hap += 10; break;
		case 13: hap += 10; break;
		default : hap += arr[i];
		}
		
	return hap;
}

void Shuffle(int** card) {
	int index[13] = { 0, }, temp;
	*card = malloc(sizeof(int) * 20);
	srand(time(NULL));

	for (int i = 0; i < 20; i++) {
		while (1) {
			temp = (rand() % 13) + 1;
			if (index[temp - 1] != 4) {
				index[temp - 1]++;
				(*card)[i] = temp;
				break;
			}
			else continue;
		}
	}
}

void Initialization(int* card, int** user, int** dealer, int* card_num) {
	*user = malloc(sizeof(int *) * 2);
	*dealer = malloc(sizeof(int *) * 2);

	for (int i = 0; i < 2; i++) {
		(*user)[i] = card[(*card_num)++];
		(*dealer)[i] = card[(*card_num)++];
	}
}

void Status(int** user, int** dealer, int *user_card_t, int* dealer_card_t) {
	printf("Dealer : ");
	for (int i = 0; i < *dealer_card_t -1; i++) {
		switch ((*dealer)[i]) {
		case 1: printf("A, "); break;
		case 11: printf("J, "); break;
		case 12: printf("Q, "); break;
		case 13: printf("K, "); break;
		default: printf("%d, ", (*dealer)[i]);
		}
	}
	switch ((*dealer)[*dealer_card_t -1]) {
	case 1: printf("A\n"); break;
	case 11: printf("J\n"); break;
	case 12: printf("Q\n"); break;
	case 13: printf("K\n"); break;
	default: printf("%d\n", (*dealer)[*dealer_card_t -1]);
	}

	printf("User : ");
	for (int i = 0; i < *user_card_t - 1; i++) {
		switch ((*user)[i]) {
		case 1: printf("A, "); break;
		case 11: printf("J, "); break;
		case 12: printf("Q, "); break;
		case 13: printf("K, "); break;
		default: printf("%d, ", (*user)[i]);
		}
	}
	switch ((*user)[*user_card_t - 1]) {
	case 1: printf("A\n"); break;
	case 11: printf("J\n"); break;
	case 12: printf("Q\n"); break;
	case 13: printf("K\n"); break;
	default: printf("%d\n", (*user)[*user_card_t - 1]);
	}
}

void hit(int *card, int** user, int *card_num, int* user_card_t) {
	*user = realloc(*user, (*user_card_t +1) * sizeof(int));
	(*user)[(*user_card_t)++] = card[(*card_num)++];
}

void End(int *card, int** dealer, int *card_num, int *dealer_card_t, int** user, int* user_card_t) {
	while (1) {
		if (total_score(*dealer, *dealer_card_t) < 17) {
			*dealer = realloc(*dealer, (*dealer_card_t + 1) * sizeof(int));
			(*dealer)[(*dealer_card_t)++] = card[(*card_num)++];
			Status(user, dealer, user_card_t, dealer_card_t);
		}
		else break;
	}
}

void Result(int** user, int* user_card_t, int** dealer, int* dealer_card_t) {
	if (total_score(*dealer, *dealer_card_t) > 21) {
		printf("Dealer Busted! User Win! Congratulation!");
	}
	else if (total_score(*dealer, *dealer_card_t) < total_score(*user, *user_card_t))
		printf("User Win! Congratulation!");
	else if (total_score(*dealer, *dealer_card_t) > total_score(*user, *user_card_t))
		printf("Dealer Win!");
	else printf("Draw!");
}

int main() {
		while (1){
			char temp[30];
			int* card, * user, * dealer, card_num = 0, user_card_t=2, dealer_card_t=2;

			printf("\nGame Start? ");
			scanf("%s", temp);

			if (!strcmp(temp, "Start")) {
				Shuffle(&card);
				Initialization(card, &user, &dealer, &card_num);
				Status(&user, &dealer, &user_card_t, &dealer_card_t);
			}
			else if(!strcmp(temp, "End")) {
				return 0;
			}
			else {
				printf("Error : Wrong Input, Try Again.\n");
				continue;
			}

			//여기부터 추가 받을지 결정
			while (1) {
				if (total_score(user, user_card_t) > 21) {
					printf("Busted! Over 21! Dealer Wins.");
					break;
				}
				printf("More Card? ");
				scanf("%s", temp);

				if (!strcmp(temp, "Hit")) {
					hit(card, &user, &card_num, &user_card_t);
					Status(&user, &dealer, &user_card_t, &dealer_card_t);
					if (total_score(user, user_card_t) == 21) {
						printf("BlakJack! Winner Winner chicken Dinner! User Win!");
						break;
					}
				}
				else if (!strcmp(temp, "Stay")) {
						End(card, &dealer, &card_num, &dealer_card_t, &user, &user_card_t);
						Result(&user, &user_card_t, &dealer, &dealer_card_t);
						break;
				}
				else 
					printf("Error : Wrong Input, Try Again.\n");
			}
		}

	return 0;
}