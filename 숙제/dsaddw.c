#include <stdio.h>

typedef struct term {
	char value;
	struct term* next;
}Term;

typedef struct tree {
	char value;
	struct tree* leftChild;
	struct tree* rightChild;
}Tree;

/////////////////////////////////////
Tree* makeBT(Tree* leftChildBT, char element, Tree* rightChildBT);
void inorder(Tree* root);
void preorder(Tree* root);
Term* postFixer(char* string);
/////////////////////////////////////
void inorder(Tree* root) {
	if (root != NULL) {
		inorder(root->leftChild);
		printf("%c", root->value);
		inorder(root->rightChild);
	}
}
void preorder(Tree* root){
	if (root != NULL) {
		printf("%c", root->value);
		inorder(root->leftChild);
		inorder(root->rightChild);
	}
}

void postorder(Tree* root){
	if (root != NULL) {
		inorder(root->leftChild);
		inorder(root->rightChild);
		printf("%c", root->value);
	}
}


int main(void) {
	char* str = "((3+((2*6)/4))-7)";
	
	postFixer(str);
	
	Tree* leftNode = makeBT(NULL, '2', NULL);
	Tree* rightNode = makeBT(NULL, '6', NULL);
	leftNode = makeBT(leftNode, '*',rightNode);

	rightNode = makeBT(NULL, '4', NULL);
	leftNode = makeBT(leftNode, '/', rightNode);

	rightNode = makeBT(NULL, '3', NULL);
	leftNode = makeBT(leftNode, '+', rightNode);

	rightNode = makeBT(NULL, '7', NULL);
	leftNode = makeBT(leftNode, '-', rightNode);

	inorder(leftNode);
	printf("\n");
	preorder(leftNode);
	printf("\n");
	postorder(leftNode);
}

Tree* makeBT(Tree* leftChildBT, char element, Tree* rightChildBT) {
	Tree* newTree = (Tree*)malloc(sizeof(Tree));
	newTree->value = element;
	newTree->leftChild = leftChildBT;
	newTree->rightChild = rightChildBT;
}
Term* postFixer(char* string){
	int i;
	Term* postRear;
	Term* postFront;
	Term* postTop;
	
	postRear=postFront;
	postRear=(Term*)malloc(sizeof(Term));
	postRear->value='H';
	postRear->next=NULL;
	
	postTop->next=NULL:
	
	for(i=0;string[i]!=NULL;i++){
		if(string[i]=='('){
			stackPush(postTop, '(');
		}
		else if(string[i]==')'){
			while(1){
				
			}
		}
	}
	
	return queueRear->next;
}
void stackPush(Term * top, char value){
	top=(Term*)malloc(sizeof(Term));
	top->next=NULL;
	top->value = value;
	top=top->next;
}
char stackPop(Term * top){
	char popChar=top->value;
	Term* deleteTerm = top;
	top=top->next;
	free(deleteTerm);
	return popChar;
}
void queuePush(Term* front, char value){
	Term* newTerm = (Term*)malloc(sizeof(Term));
	newTerm->next=NULL;
	newTerm->value = value;
	front->next = newTerm;
	front = front->next;
}
