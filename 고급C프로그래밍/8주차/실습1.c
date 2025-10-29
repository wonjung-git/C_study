#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	struct grade {
		char name[101];
		int hagjum;
		char grade[3];
		float jumsu;
	};
	int s_num = 1;
	float jumsu_sum = 0;
	int hagjum_sum = 0;
	char temp[101];
	FILE* input;
	input = fopen("grade.txt", "r");

	struct grade* s = (struct grade*)malloc(sizeof(struct grade));
	

	fgets(temp, 101, input);

	for (;;s_num++) {
		fgets(temp, 101, input);
		if (feof(input))
			break;

		s = (struct grade*)realloc(s, sizeof(struct grade) * s_num);

		int index = 0;
		//이름 전처리
		for (int i=0;; index++, i++) {
			if (temp[index] == '\t' || temp[index] == ' ') {
				s[s_num - 1].name[i] = '\0';
				index++;
				break;
			}
			else s[s_num-1].name[i] = temp[index];
		}

		//학점 전처리
		for (int i = 0; ; index++, i++) {
			if ('0' <= temp[index] && temp[index] <= '9') {
				s[s_num - 1].hagjum = (temp[index] - '0');
				index++;
				break;
			}
		}

		//성적 전처리
		for (int i = 0; ; index++, i++) {
			if ('0' == temp[index]) {
				switch (temp[index - 1]) {
				case 'A':
					strcpy(s[s_num - 1].grade, "A0");
					s[s_num - 1].jumsu = 4;
					break;
				case 'B':
					strcpy(s[s_num - 1].grade, "B0");
					s[s_num - 1].jumsu = 3;
					break;
				case 'C':
					strcpy(s[s_num - 1].grade, "C0");
					s[s_num - 1].jumsu = 2;
					break;
				case 'D':
					strcpy(s[s_num - 1].grade, "D0");
					s[s_num - 1].jumsu = 1;
					break;
				}
				break;	
			}
			else if ('+' == temp[index]) {
				switch (temp[index - 1]) {
				case 'A':
					strcpy(s[s_num - 1].grade, "A+");
					s[s_num - 1].jumsu = 4.5;
					break;
				case 'B':
					strcpy(s[s_num - 1].grade, "B+");
					s[s_num - 1].jumsu = 3.5;
					break;
				case 'C':
					strcpy(s[s_num - 1].grade, "C+");
					s[s_num - 1].jumsu = 2.5;
					break;
				case 'D':
					strcpy(s[s_num - 1].grade, "D+");
					s[s_num - 1].jumsu = 1.5;
					break;
				}
				break;
			}
			else if ('F' == temp[index]) {
				strcpy(s[s_num - 1].grade, "F");
				s[s_num - 1].jumsu = 0;
			}
		}
	}

	fclose(input);

	printf("=======과목별 점수=======\n");
	for (int i = 0; i < s_num-1; i++) {
		printf("%10s 점수 : %.2f\n", s[i].name, s[i].hagjum * s[i].jumsu);
		jumsu_sum += s[i].hagjum * s[i].jumsu;
		hagjum_sum += s[i].hagjum;
	}

	printf("총 평점 : %.2f", jumsu_sum / hagjum_sum);

	free(s);
	return 0;
}