#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct node {
	char name[21];
	float price;

	struct node* next;
	struct node* prev;
};

struct node* create_node(char name[21], float price) {
	struct node* new_node = (struct node*)malloc(sizeof(struct node));

	strcpy(new_node->name, name);
	new_node->price = price;

	new_node->next = NULL;
	new_node->prev = NULL;

	return new_node;
}

struct node* insert_node(struct node* node, char name[21], float price) {
	struct node* new_node = create_node(name, price);

	if (node == NULL)
		node = new_node;
	else {
		struct node* temp = node;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
	return node;
}

struct node* price_sort(struct node* node) {
	struct node* temp1 = node;
	struct node* temp2 = NULL;
	struct node* temp3 = NULL;
	while (1) {

		temp2 = temp1;
		while (1) {
			if (temp1->price > temp2->price) {
				if (temp1->prev == NULL) {
					temp1->next = temp2->next;
					temp2->next = temp1;
					temp2->prev = NULL;
					temp1->prev = temp2;

					temp3 = temp1;
					temp1 = temp2;
					temp2 = temp3;
					node = temp1;
				}
				else {
					temp1->next = temp2->next;
					temp2->next = temp1;
					temp1->prev->next = temp2;
					temp2->prev = temp1->prev;
					temp1->prev = temp2;

					temp3 = temp1;
					temp1 = temp2;
					temp2 = temp3;
				}
			}
			else if (temp2->next != NULL)
				temp2 = temp2->next;
			else break;
		}
		if (temp1->next != NULL)
			temp1 = temp1->next;
		else break;
	}
	return node;
}

struct node* name_sort(struct node* node) {
	struct node* temp1 = node;
	struct node* temp2 = NULL;
	struct node* temp3 = NULL;
	while (1) {

		temp2 = temp1;
		while (1) {
			if (strcmp(temp1->name, temp2->name) > 0) {
				if (temp1->prev == NULL) {
					temp1->next = temp2->next;
					temp2->next = temp1;
					temp2->prev = NULL;
					temp1->prev = temp2;

					temp3 = temp1;
					temp1 = temp2;
					temp2 = temp3;
					node = temp1;
				}
				else {
					temp1->next = temp2->next;
					temp2->next = temp1;
					temp1->prev->next = temp2;
					temp2->prev = temp1->prev;
					temp1->prev = temp2;

					temp3 = temp1;
					temp1 = temp2;
					temp2 = temp3;
				}
			}
			else if (temp2->next != NULL)
				temp2 = temp2->next;
			else break;
		}
		if (temp1->next != NULL)
			temp1 = temp1->next;
		else break;
	}
	return node;
}

void print_list(struct node* list) {
	struct node* temp = list;
	while (temp != NULL) {
		printf("%s  %.2f\n", temp->name, temp->price);
		temp = temp->next;
	}
}

void free_list(struct node* head) {
	struct node* temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}

int main() {
	char temp[101];
	const char* delim = " ";
	char* name;
	float price;
	struct node* list = NULL;
	FILE* input = fopen("drink.txt", "r");

	while (1) {
		fgets(temp, 101, input);

		name = strtok(temp, delim);
		price = atof(strtok(NULL, delim));

		list = insert_node(list, name, price);
		if (feof(input)) break;
	}

	print_list(list);

	printf("=====이름순 정렬=====\n");
	list = name_sort(list);
	print_list(list);

	printf("=====가격순 정렬=====\n");
	list = price_sort(list);
	print_list(list);

	free_list(list);
	return 0;
}