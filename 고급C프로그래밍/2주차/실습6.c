#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void func_sort(char string[101], char data[15]);
void input_char();
void func_print(char string[101]);


void input_char() {
	char string[101], data[15];
	printf("���ڿ� �Է� : ");
	scanf("%s", string);

	printf("���Ĺ��(��������, ��������) �Է� : ");
	scanf("%s", data);

	func_sort(string, data);
}

void func_sort(char string[101], char data[15]) {
	char temp;
	if (!strcmp(data, "��������")) {
		for (int i = 0; i < 101 ; i++) {
			for (int j = i; j < 101 && string[j] != NULL; j++) {
				if (string[i] >= string[j]) {
					temp = string[i];
					string[i] = string[j];
					string[j] = temp;
				}
			}
		}
	}
	else if (!strcmp(data, "��������")) {
		for (int i = 0; i < 101; i++) {
			for (int j = i; j < 101 && string[j] != NULL; j++) {
				if (string[i] <= string[j]) {
					temp = string[i];
					string[i] = string[j];
					string[j] = temp;
				}
			}
		}
	}
	else printf("���Ĺ���� �߸� �Է��߽��ϴ�.");

	func_print(string);
}

void func_print(char string[101]) {
	printf("after : %s", string);
}

int main() {
	input_char();
	return 0;
}