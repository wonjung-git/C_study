#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

struct holzak {
	int data;

	struct holzak* next;
};

struct node {
	struct holzak* node1;
	struct holzak* node2;
};


struct holzak* create_node(int data) {
	struct holzak* new_node = (struct holzak*)malloc(sizeof(struct holzak));

	new_node->data = data;
	new_node->next = NULL;

	return new_node;

}

struct holzak* insert_node(struct holzak* head, int data) {
	struct holzak* new_node = create_node(data);

	if (head == NULL)
		head = new_node;
	else {
		struct holzak* temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return head;
}

struct holzak* delete_node(struct holzak* head, int target) {
	struct holzak* temp1 = head;
	struct holzak* temp2 = NULL;

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
	struct holzak* temp = list->node1;
	printf("홀수 리스트\n");
	while (temp != NULL) {
		printf("%d\n", temp->data);
		temp = temp->next;
	}

	temp = list->node2;
	printf("짝수 리스트\n");
	while (temp != NULL) {
		printf("%d\n", temp->data);
		temp = temp->next;
	}
}

void free_list(struct holzak* head) {
	struct holzak* temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}

void sort_list(struct holzak* head) {
	struct holzak* i, * j;
	int temp;
	for (i = head; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if (i->data > j->data) {
				temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
}


int main() {
	int data;
	struct node* list = (struct node*)malloc(sizeof(struct node));
	list->node1 = NULL;
	list->node2 = NULL;


	while (1) {
		printf("정수값 입력 (0: 종료, 음수: 절댓값 삭제) : ");
		scanf("%d", &data);
		if (data > 0) {
			if (data % 2 == 0) {
				list->node2 = insert_node(list->node2, data);
			}
			else
				list->node1 = insert_node(list->node1, data);
		}
		else if (data < 0) {
			data = -1 * data;
			if (data % 2 == 0) {
				list->node2 = delete_node(list->node2, data);
			}
			else
				list->node1 = delete_node(list->node1, data);
		}
		else break;
	}

	printf("=====정렬전=====\n");
	print_list(list);
	sort_list(list->node1);
	sort_list(list->node2);
	printf("=====정렬후=====\n");
	print_list(list);

	free_list(list->node1);
	free_list(list->node2);
	free(list);
	return 0;
}