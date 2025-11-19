#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

struct node {
	int data;

	struct node* next;
};

struct node* create_node(int data) {
	struct node* new_node = (struct node*)malloc(sizeof(struct node));

	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

struct node* insert_node(struct node* head, int data) {
	struct node* new_node = create_node(data);

	if (head == NULL)
		head = new_node;
	else {
		struct node* temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return head;
}

struct node* delete_node(struct node* head, int target) {
	struct node* temp1 = head;
	struct node* temp2 = NULL;

	if (temp1 != NULL && temp1->data == target) {
		head = temp1->next;
		free(temp1);
		return head;
	}

	while (temp1 != NULL && temp1->data != target) {
		temp2 = temp1;
		temp1 = temp1->next;
	}

	if (temp1 == NULL) {
		printf("데이터가 노드에 없습니다.");
		return head;
	}

	temp2->next = temp1->next;
	free(temp1);
	return head;
}

void print_list(struct node* list) {
	struct node* temp = list;
	while (temp != NULL) {
		printf("%d\n", temp->data);
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
	int data;
	struct node* list = NULL;

	while (1) {
		printf("정수값을 입력(0입력시 종료, 음수 입력시 절댓값이 같은 정수를 삭제) : ");
		scanf("%d", &data);
		if (data > 0) {
			list = insert_node(list, data);
		}
		else if (data < 0) {
			list = delete_node(list, -1*data);
		}
		else break;
	}
	print_list(list);

	free_list(list);
	return 0;
}