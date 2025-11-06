#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	enum month {
		January=1, February, March, April, May, June, July, August, September, October, November, December
	}month;


	printf("월 입력 : ");
	scanf("%d", &month);

	switch (month) {
	case January: printf("1월은 January 입니다."); break;
	case February: printf("2월은 February 입니다."); break;
	case March: printf("3월은 March 입니다."); break;
	case April: printf("4월은 April 입니다."); break;
	case May: printf("5월은 May 입니다."); break;
	case June: printf("6월은 June 입니다."); break;
	case July: printf("7월은 July 입니다."); break;
	case August: printf("8월은 August 입니다."); break;
	case September: printf("9월은 September 입니다."); break;
	case October: printf("10월은 October 입니다."); break;
	case November: printf("11월은 November 입니다."); break;
	case December: printf("12월은 December 입니다."); break;
	default : printf("잘못된 월을 입력하셨습니다.");
	}
	
	return 0;
}