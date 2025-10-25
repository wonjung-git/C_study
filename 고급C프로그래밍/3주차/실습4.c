#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* vip_check(int num) {
	static int vip[3] = { 0, };
	int room_num, necessary_room = num / 4;
	if (num % 4 != 0)
		necessary_room++;
	static char result[30];
	strcpy(result, "\0");

	room_num = 0;
	for (int i = 0; i < 3; i++)
		if (vip[i] == 0)
			room_num++;
	if (room_num < necessary_room)
		strcpy(result, "가능한 방이 없습니다.");

	else {
		int j = 1;
		char a[3] = {0};
		while (necessary_room != 0) {
			char temp[5] = " 30";
			if (vip[j - 1] == 0) {
				vip[j - 1] = 1;
				necessary_room--;
				_itoa(j, a, 10);
				strcat(temp, a);
				strcat(result, temp);
			}
			j++;
		}
	}

	return result;
}

int normal_check(int num) {
	static int normal[5] = { 0, };
	int room_num, necessary_room = num / 2;
	if (num % 2 != 0)
		necessary_room++;
	static char result[30];
	strcpy(result, "\0");

	room_num = 0;
	for (int i = 0; i < 5; i++)
		if (normal[i] == 0)
			room_num++;
	if (room_num < necessary_room)
		strcpy(result, "가능한 방이 없습니다.");

	else {
		int j = 1;
		char a[3] = { 0 };
		while (necessary_room != 0) {
			char temp[5] = " 20";
			if (normal[j - 1] == 0) {
				normal[j - 1] = 1;
				necessary_room--;
				_itoa(j, a, 10);
				strcat(temp, a);
				strcat(result, temp);
			}
			j++;
		}
	}

	return result;
}

char* reservation_hotel(int num, char room[16]) {
	static char result[50] = "\0";
	if (!strcmp(room, "vip룸")) 
		return vip_check(num);
	
	
	else if (!strcmp(room, "일반룸")) {
		normal_check(num);
	}
	else printf("방 이름을 확인해주세요.");
}



int main() {
	int num;
	char room[16];
	char* result;

	for(int i=0; i<5; i++){
		printf("\n어떤방을 예약하시겠어요?(vip룸, 일반룸 입력) : ");
		scanf("%s", &room);

		printf("몇명을 예약하시겠어요? : ");
		scanf("%d", &num);

		result = reservation_hotel(num, room);

		if (!strcmp(result, "가능한 방이 없습니다."))
			printf("예약 가능한 방이 없습니다.");
		else printf("%s호를 예약해 드릴게요", result);
	}
	
	return 0;
}