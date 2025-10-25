#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void prime_number(int data[29]) {
	for (int i = 0; i < 29; i++) {
		if (data[i] != 0) {
			for (int j = i + 1; j < 29; j++) {
				if (data[j] % data[i] == 0)
					data[j] = 0;
			}
		}
	}
}

int main() {
	int data[29];
	for (int i = 2; i < 31; i++)
		data[i - 2] = i;
	prime_number(data);
	for (int i = 0; i < 29; i++) {
		if (data[i] != 0)
			printf(" %d", data[i]);
	}
	return 0;
}