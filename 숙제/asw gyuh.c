#include <stdio.h>
#include <stdlib.h>

typedef struct term{
	char value;
	term* leftChild;
	term* rightChild;
}Term;

int main (){
	char[] arr={'_','A','B','C','D','E','F','_','_','G','_','_','_','H',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	
	return 0;
}
Term* treeMaker (char[] arr, Term* root){
	int i;
	
	
}
int twosPower(int a){
	int i,mul=1;
	for(i=0;i<a;i++){
		mul*=2;
	}
	return mul;
}

