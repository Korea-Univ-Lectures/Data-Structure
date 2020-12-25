#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef struct {
	int row;
	int col;
	int value;
}entryNode;

typedef enum {head,entry} tagfield;

typedef struct _matrixNode{
	_matrixNode * down;
	_matrixNode * right;
	tagfield tag;
	union {
		_matrixNode * next;
		entryNode entry;
	}u;
}matrixNode;

typedef matrixNode * matrixPointer;



//headerNode���̴�.
matrixPointer hdnode[MAX_SIZE];

matrixPointer mread(void) 
{
	int numRows, numCols, numTerms, numHeads, i;
	int row, col, value, currentRow;
	matrixPointer temp, last;
	matrixPointer node;

	printf("**��, ��, �׸��� 0�� �ƴ� ���� ���� �Է� (����:3/2/6, �ݵ�� ���Ŀ� �����ּ���)**\n-------------------------->> ");
	scanf("%d%d%d", &numRows, &numCols, &numTerms);
	numHeads = (numCols > numRows) ? numCols : numRows;
	node = newNode();
	node->tag = entry;
	node->u.entry.row = numRows;
	node->u.entry.col = numCols;

	if (!numHeads) node->right = node;
}

matrixPointer newNode() {
	matrixPointer nodep = (matrixPointer)malloc(sizeof(matrixNode));
	return nodep;
}

void main() {
	printf("Hello world");
}

