#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

void Write_result_to_file(char* B[20], char A_D);
void sort_Ascending(char* B[20]);
void sort_Descending(char* B[20]);

void sort_Ascending(char* B[20]) {
	char* temp;
	for (int i = 0; i < 20; i++) {
		for (int j = i+1; j < 20 && B[j] != NULL; j++) {
			if (strcmp(B[i], B[j]) > 0) {
				temp = B[i];
				B[i] = B[j];
				B[j] = temp;
			}
		}
	}
	Write_result_to_file(B, 'A');
}

void sort_Descending(char* B[20]) {
	char* temp;
	for (int i = 0; i < 20; i++) {
		for (int j = i+1; j < 20 && B[j] != NULL; j++) {
			if (strcmp(B[i], B[j]) < 0) {
				temp = B[i];
				B[i] = B[j];
				B[j] = temp;
			}
		}
	}
	Write_result_to_file(B, 'D');
}

void Write_result_to_file(char* B[20], char A_D) {
	FILE* output;

	if (A_D == 'A')
		output = fopen("Result_Ascending.txt", "w");
	else
		output = fopen("Result_Descending.txt", "w");

	fputs("=========Sorting Result=========", output);
	for (int i = 0; i<20 && B[i] != NULL; i++) {
		fprintf(output, "\n[%-15s]", B[i]);
	}
	fclose(output);
}

int main() {
	int k = 0;
	char* A[5], *B[20], temp[101];
	FILE* input;
	input = fopen("data.txt", "r");
	
	for (int i = 0; i < 20; i++)
		B[i] = NULL;

	for (int i=0;i<4;i++) {
		//A에 문자열 받기
		fgets(temp, 101, input);
		A[i] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
		strcpy(A[i], temp);

		//B에 파싱 시작
		int j = 0;
		for (;;) {
			int l = 0;
			while (('A' <= A[i][j] && A[i][j] <= 'Z') || ('a' <= A[i][j] && A[i][j] <= 'z') || A[i][j] == ' ') {
				temp[l++] = A[i][j++];
			}

			temp[l] = '\0';

			B[k] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
			strcpy(B[k], temp);
			k++;
			if ((A[i][j + 1] == '\n' && A[i][j] == ',') || A[i][j] == '\n')
				break;
			else j++;
		}
		if (feof(input))
			break;
	}

	sort_Ascending(B);
	sort_Descending(B);

	fclose(input);

	return 0;
}