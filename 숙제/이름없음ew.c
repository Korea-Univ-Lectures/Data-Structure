#include <stdio.h>
#include <stdlib.h>

typedef struct term {
	char value;
	char prior;
	struct term* next;
}Term;

typedef struct tree {
	char value;
	struct tree* leftChild;
	struct tree* rightChild;
}Tree;

//////////////////////////
Term* push(Term* current, int prior, int vlaue);
/////////////////////////

int main(void) {
	Term* head=(Term*)malloc(sizeof(Term));
	head= push(head, 4,2);
	printf("%d",head->value);
}

Term* push(Term* head, int prior, int value){
	Term* current = head;
	current=(Term*)malloc(sizeof(Term));
	current->prior=prior;
	current->value=value;
	current->next=NULL;
	
	Term* target=head;
	
	while(target->next!=NULL){
		target=target->next;
	}
	
	target=current;
	
	current = current->next;
	return head;
}
