#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
	char value;
	struct tree* leftChild;
	struct tree* rightChild;
}Tree;

typedef struct term{
	char value;
	struct term* next;
}Term;
////////////////////////
void treePush(Tree* header,Tree* left, char value, Tree* right);
Tree* treeByArray(Tree* header, char arr[], int index);
Tree* treeByArrayInt(Tree* header, int arr[], int index);
void maxHeapInsert(int heapArr[], int value, int index);
void inorder(Tree* root);
void preorder(Tree* root);
void postorder(Tree* root);

int pmatch( char *string, char *pat );
////////////////////////
int main(){
	Term* queue;
	Tree* bt;
	
	char elements[170]= {'_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',NULL};
	int heapArray[100] = {0,16,14,10,8,7,9,3,2,4,1};
	bt=treeByArray(bt, elements, 1);
	preorder(bt);
	


	return 0;
}

void treePush(Tree* header,Tree* left, char value, Tree* right){
	
}

Tree* treeByArray(Tree* header, char arr[], int index){
	if(strlen(arr)<index){
		return NULL;
	}
	else{
		if(arr[index]==NULL){
			return NULL;
		}
		else{
			header=(Tree*)malloc(sizeof(Tree));
			header->value = arr[index];
			header->leftChild=treeByArray(header->leftChild, arr, index*2);
			header->rightChild=treeByArray(header->rightChild, arr, (index*2)+1);
			return header;
		}
	}
}

Tree* treeByArrayInt(Tree* header, int arr[], int index){
	if(10<index){
		return NULL;
	}
	else{
		header=(Tree*)malloc(sizeof(Tree));
		header->value = (arr[index]+'0');
		header->leftChild=treeByArray(header->leftChild, arr, index*2);
		header->rightChild=treeByArray(header->rightChild, arr, (index*2)+1);
		return header;
	}
}

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
void maxHeapInsert(int heapArr[], int value, int index){
	int temp;
	heapArr[index]=value;
	while(index!=1){
		if(heapArr[index]>heapArr[index/2]){
			temp=heapArr[index/2];
			heapArr[index/2]=heapArr[index];
			heapArr[index]=temp;
			index/=2;
		}
		else{
			break;
		}
	}
}


/*
int pmatch( char *string, char *pat ) { 

	int i=0, j=0; 
	int lens = strlen( string );
	int lenp = strlen( pat ); 

	while( i<lens && j<lenp ) { 
		if( string[i] == pat[j] ) { i++; j++; 
	} 
	else if( j==0 ) 
		i++; 
	else 
 		j=failure[j-1]+1; 
 	}
	  
 	return ( (j==lenp) ? (i-lenp) : -1 ); 
} 
void fail( char *pat ) {

	int n=strlen( pat ); 
	failure[0] = -1; 
	
	for( j=1; j<n; j++ ) { 
		i=failure[j-1]; 
		while( (pat[j] != pat[i+1]) && (i >= 0) ) 
			i = failure[i];
			
	if( pat[j] == pat[i+1] ) 
		failure[j] = i+1; 
	else
		failure[j] = -1; 
	}
} */
