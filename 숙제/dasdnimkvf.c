#include <stdio.h>
#include <stdlib.h>

typedef struct term{
	int value;
	struct term* next;
}Term;
////////////////////
void pushList(Term* head,int value);
void swapList(Term* previous, Term* current, Term* next);
////////////////////
void main (){
	Term* head;
	pushList(head,5);
	printf("%d",head->value);
	
	//printList(head);
	
//	current = head->next;
//	swapList(head,current, current->next );
	
//	printList(head);
}

void pushList(Term* head, int value){
	head=(Term*)malloc(sizeof(Term));
	head->next=NULL;
	head->value=value;
	head=head->next;
}

void swapList(Term* previous, Term* current, Term* next){
	current=next->next;
	next->next=current;
	previous->next=next;
}

void printList (Term* head){
	Term* current = head;
	while(current!=NULL){
		printf("%d",current->value);
		current=current->next;
	}
}
