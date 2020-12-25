#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int row;
	int col;
	int val;
	struct node* next;
}Node;
//////////////////////
void mread(Node* header);
void bubbleSort(struct Node *start);
void swap(struct Node *a, struct Node *b);


////////////////////
void main() {
	Node* head1 = NULL;
	Node* head2 = NULL;

	mread(head1);

}
void bubbleSort(struct Node *start)
{
	int swapped, i;
	struct Node *ptr1;
	struct Node *nextn;
	nextn=ptr1->next;
	struct Node *lptr = NULL;

	/* Checking for empty list */
	if (start == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			if (ptr1->row > nextn->row)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
			nextn = nextn->next;
		}
		lptr = ptr1;
	} while (swapped);
}
void swap(struct Node *a, struct Node *b)
{
	int row = a->row;
	a->row = b->row;
	b->row = row;

	int col = a->col;
	a->col = b->col;
	b->col = col;

	int val = a->val;
	a->val = b->val;
	b->val = val;
}
void mread(Node* header) {
	int inputRow, inputCol, inputVal;
	int i;
	Node* currentNode;
	Node* newNode;

	scanf("%d/%d/%d", &inputRow, &inputCol, &inputVal);
	header = (struct Node*)malloc(sizeof(Node));
	header->row = inputRow; header->col = inputCol;  header->val = inputVal;
	header->next = NULL;
	currentNode = header;

	printf("%d, %d, %d\n", header->row, header->col, header->val);

	for (i = 0; i < (header->val); i++) {
		scanf("%d/%d/%d", &inputRow, &inputCol, &inputVal);
		newNode = (struct Node*)malloc(sizeof(Node));
		newNode->row = inputRow; newNode->col = inputCol;  newNode->val = inputVal;
		newNode->next = NULL;
		currentNode->next = newNode;
		currentNode = currentNode->next;
	}

	bubbleSort(header);

	for (currentNode = header->next; currentNode != NULL; currentNode = currentNode->next) {
		printf("%d\n", currentNode->val);
	}
}
