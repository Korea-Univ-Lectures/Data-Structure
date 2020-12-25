#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct term{
	int priotity;
	int value;
	struct term* next;
}Term;

////////////////////
void QueuePush(Term*front,int value, int pri);
////////////////////

void main(){
	Term* rear;
	Term* front;
	front=rear;
	
	QueuePush(front, 9, 3);
	printf("%d",rear->value);
}
void QueuePush(Term*front,int value, int pri){
	Term* newNode = (Term*)malloc(sizeof(Term));
	newNode->value=value;
	newNode->priotity = pri;
	newNode->next=NULL;
	front->next=newNode;
	front= front->next;
}
