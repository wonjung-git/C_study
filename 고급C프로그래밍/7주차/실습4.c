#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

int my_strcmp(char word1[101], char word2[101]) {
	char data1[101], data2[101];
	strcpy(data1, word1);
	strcpy(data2, word2);

	for (int i = 0; i<strlen(data1); i++) {
		if ('A' <= data1[i] && data1[i] <= 'Z') 
			data1[i] += 32;
	}
	for (int i = 0; i < strlen(data2); i++) {
		if ('A' <= data2[i] && data2[i] <= 'Z')
			data2[i] += 32;
	}
	for (int i = 0; data1[i] != '\0' || data2[i] != '\0'; i++) {
		if (data1[i] - data2[i] > 0) {
			return 1;
		}
		else if (data1[i] - data2[i] < 0) {
			return -1;
		}
	}
	return 0;
}

void make_dictionary(char** word, int word_num) {
	char* temp;

	for (int i = 0; i < word_num-1; i++) {
		for (int j = i+1; j < word_num; j++) {
			if (my_strcmp(word[i], word[j])>0) {
				temp = word[i];
				word[i] = word[j];
				word[j] = temp;
			}
		}
	}

}

int main() {
	FILE *input, *output;
	char** word = (char**)malloc(sizeof(char*) * 1);
	char temp[101];
	int word_num=0;
	input = fopen("words.txt", "r");
	output = fopen("dictionary.txt", "w");

	word = (char**)realloc(word, sizeof(char*) * (word_num+1));
	word[word_num] = (char*)malloc(sizeof(char) * 1);

	while(1){
		fgets(temp, 101, input);
		if (feof(input))
			break;

		for (int j = 0, k = 0; j < strlen(temp); j++) {
			//단어 전처리
			if ((temp[j] == '|' || temp[j] == '\t' || temp[j] == ',' || temp[j] == ';' || temp[j] == ' ' || temp[j] == '\n') && k>0) {
				word[word_num][k] = '\0';
				word_num++;
				word = (char**)realloc(word, sizeof(char*) * (word_num + 1));
				word[word_num] = (char*)malloc(sizeof(char) * 1);
				k = 0;
			}
			else if (('A' <= temp[j] && temp[j] <= 'Z') || ('a' <= temp[j] && temp[j] <= 'z')) {
				word[word_num] = (char*)realloc(word[word_num], sizeof(char) * (k + 2));
				word[word_num][k++] = temp[j];
			}
		}
	}

	make_dictionary(word, word_num);
	
	for (int i = 0; i < word_num; i++)
		fprintf(output, "%s\n", word[i]);

	fclose(input);
	fclose(output);


	//이거 보고 쓰시는 분들 메모리 할당 한거 free()하셔야 돼요. 귀찮아서 그건 안쓸게요..
	return 0;
}