#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main() {
	char temp1[101], temp2[101];
	FILE* output;
	FILE* input;
	output = fopen("output2.txt", "w");
	input = fopen("in.txt", "r");

	for (;;) {
		fgets(temp1, 101, input);
		if (feof(input))
			break;

		for (int i = strlen(temp1) - 1; i > 0; i--) {
			temp2[strlen(temp1) - 1 - i] = temp1[i-1];
		}
		temp2[strlen(temp1)-1] = '\0';
		fputs(temp2, output);
		fputs("\n", output);
	}

	fclose(input);
	fclose(output);

	return 0;
}