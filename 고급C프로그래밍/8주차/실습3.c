#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	struct student {
		char name[101];
		int kor;
		int eng;
	};

	struct avg {
		float *s_avg;
		float kor_avg, eng_avg, sum_avg;
	};
	int s_num;
	FILE* output;
	output = fopen("average_strudent.txt", "w");

	printf("입력할 학생 수 : ");
	scanf("%d", &s_num);

	struct student* s = (struct student*)malloc(sizeof(struct student) * s_num);
	struct avg avg;
	avg.kor_avg = 0;
	avg.eng_avg = 0;
	avg.sum_avg = 0;
	avg.s_avg = (float*)malloc(sizeof(float*) * s_num);

	//학생 정보 입력
	for (int i = 0; i < s_num; i++) {
		printf("%d번째 학생 이름 : ", i+1);
		scanf("%s", s[i].name);
		getchar();
		printf("%d번째 학생 국어 점수 : ", i + 1);
		scanf("%d", &s[i].kor);
		printf("%d번째 학생 영어 점수 : ", i + 1);
		scanf("%d", &s[i].eng);
	}

	//평균 계산
	for (int i = 0; i < s_num; i++) {
		avg.s_avg[i] = (s[i].kor + s[i].eng)/2;
		avg.kor_avg += s[i].kor;
		avg.eng_avg += s[i].eng;
		avg.sum_avg += avg.s_avg[i];
	}
	avg.kor_avg /= s_num;
	avg.eng_avg /= s_num;
	avg.sum_avg /= s_num;


	//출력
	for (int i = 0; i < s_num; i++) {
		fprintf(output, "%s의 평균 점수 : %.2f\n", s[i].name, avg.s_avg[i]);
	}
	fprintf(output, "\n국어 평균 점수 : %.2f\n", avg.kor_avg);
	fprintf(output, "영어 평균 점수 : %.2f\n", avg.eng_avg);
	fprintf(output, "모든 학생들의 총 평균 점수 : %.2f\n", avg.sum_avg);

	fclose(output);
	free(s);
	free(avg.s_avg);
	return 0;
}