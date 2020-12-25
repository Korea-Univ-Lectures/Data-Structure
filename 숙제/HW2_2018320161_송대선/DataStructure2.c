#include <stdio.h>
#include <stdlib.h>

//����� ��� ����ü�̴�.
typedef struct Node {
	int row;
	int col;
	int val;
	struct node* next;
}Node;

//////////////////////
Node* mread(Node* header); //����Է��� �޴� �Լ�
void mwrite(Node*header); //��İ��� ����ϴ� �Լ�
void merase(Node*header); //����� �����ϴ� �Լ�
Node* mtranspose(Node*header); //����� transpose
void madd(Node*header1, Node*header2); //��� ����
void mmult(Node*header1, Node*header2); //��� ����

Node* findRow(Node*header, int targetRow); //targetRow��° row�� ã�� �Լ�
Node* findCol(Node*header, int targetCol); //targetCol��° col�� ã�� �Լ�
int multLine(Node*rowLine, Node*colLine); //�ϳ��� row�� �ϳ��� col�� ������� ������ �����ϴ� �Լ�

void bubbleSort(struct Node *start); //��� linkedlist�� ������� �����ϴ� �Լ�
void swap(struct Node *a, struct Node *b); //��İ��� swap�ϴ� �Լ�

////////////////////
void main() {
	Node* head1 = NULL;//ù��° ����� header
	Node* head2 = NULL;//�ι�° ����� header

	int inputInt=0;//�޴������� �����ϴ� ��

	printf("***************************************************************************\n\n\n");
	printf("                                                         �ڷᱸ�� 2�� Assignment\n");
	printf("                                                        ��ǻ���а� �۴뼱\n\n\n\n\n");
	printf("*****************************************************************************\n\n");
	printf("�޴�����---------------------------------------------------------------------\n\n");
	printf("     [1]��� ��� �Է��ϱ� [2]������     \n\n");
	printf("----------------------------------------------------------------------------\n\n");
	printf("---(���ϴ� �޴��� ������ �ּ���)--->> ");
	scanf("%d",&inputInt);

	if (inputInt == 1) {
		head1= mread(head1);//ù��° �������� �Է�

		printf("�ι�° �޴�����--------------------------------------------------------------\n\n");
		printf("     [1]�ι��� ��� ��� �Է��ϱ�(����, ����) [2]ù��° �Է� ��� Transpose [3]������\n\n");
		printf("----------------------------------------------------------------------------\n\n");
		printf("---(���ϴ� �޴��� ������ �ּ���)--->> ");
		scanf("%d", &inputInt);

		if (inputInt == 1) {
			head2 = mread(head2);//�ι�° �������� �Է�

			printf("����° �޴�����--------------------------------------------------------------\n\n");
			printf("     [1]�� ��� ���� ���� ���� [2]�� ��� ���� ���� ���� [3]������\n\n");
			printf("----------------------------------------------------------------------------\n\n");
			printf("---(���ϴ� �޴��� ������ �ּ���)--->> ");
			scanf("%d", &inputInt);

			if (inputInt == 1) {
				madd(head1, head2);//��� ����
				printf("��� ������ �������ϴ�. ���α׷��� �����մϴ�.");
				return;
			}
			else if (inputInt == 2) {
				mmult(head1, head2);//��� ����
				printf("��� ������ �������ϴ�. ���α׷��� �����մϴ�.");
				return;
			}
			else if (inputInt == 3) {
				printf("���α׷��� �����մϴ�.");
				return;
			}
			else {
				printf("������ �߻��߽��ϴ�. ���α׷��� ���������մϴ�.");
				exit(1);
			}
		}
		else if (inputInt == 2) {
			head1=mtranspose(head1);//��� transpose
		}
		else if (inputInt == 3)
		{
			printf("���α׷��� �����մϴ�.");
			return;
		}
		else {
			printf("������ �߻��߽��ϴ�. ���α׷��� ���������մϴ�.");
			exit(1);
		}
	}
	else if (inputInt==2) {
		printf("���α׷��� �����մϴ�.");
		return;
	}
	else {
		printf("������ �߻��߽��ϴ�. ���α׷��� ���������մϴ�.");
		exit(1);
	}

}

int multLine(Node*rowLine, Node*colLine) {
	//rowLine�� ������ row��, colLine�� ������ col���� ������.
	Node* currentRow= rowLine->next;
	Node* currentCol = colLine->next;
	int sum = 0;

	//������ rowline�� element�� col���� colline�� element�� row���� �����ؾ�
	//��������, ������ ���� ��� ���Ѵ�.
	while( currentRow != NULL&&currentCol != NULL ) {

		//���� rowline�� element�� col����
		//colline�� element�� row������ ������
		//������° currentRow�� �ҷ��´�.
		if (currentRow->col < currentCol->row) {
			currentRow = currentRow->next;
		}

		//���� rowline�� element�� col����
		//colline�� element�� row������ ������
		//������° currentCol�� �ҷ��´�.
		else if (currentRow->col > currentCol->row) {
			currentCol = currentCol->next;
		}

		//���� rowline�� element�� col����
		//colline�� element�� row���� ������
		//���� ���Ͽ� ���Ѵ�.
		//�׸��� �������� ���� ���Ѵ�.
		else {
			sum += (currentRow->val*currentCol->val);
			currentRow = currentRow->next;
			currentCol = currentCol->next;
		}
	}

	return sum;
}
Node* findRow(Node*header, int targetRow) {
	Node* rowLine= (struct Node*)malloc(sizeof(Node));
	//�켱 rowLine�� ������ �ش��� ������ִ� ���� �� ���ϴ�.

	rowLine->next = NULL;

	//rowLine�� Ž���ϴ� �������̴�.
	Node* rowLineCurrent=rowLine;
	Node* current=header->next;

	//���ο� ��带 �������ϴ� �������̴�.
	Node* newNode;

	//��� ����� ���鿡 ���ؼ� Ž���Ѵ�.
	for (; current != NULL; current = current->next) {

		//���� ã�����ϴ� row�� ���� ���� ��带 �߰��ϸ� rowLine�� �߰�
		if (current->row == targetRow) {

			//�� ��带 �����Ѵ�.
			newNode = (struct Node*)malloc(sizeof(Node));
			newNode->row = current->row;
			newNode->col = current->col;
			newNode->val = current->val;
			newNode->next = NULL;

			//������ ��带 rowLine�� �߰��ϰ�, rowLineCurrent�� �ѱ��.
			rowLineCurrent->next = newNode;
			rowLineCurrent = rowLineCurrent->next;
		}
	}
	return rowLine;
}
Node* findCol(Node*header, int targetCol) {

	//�켱 colLine�� ������ �ش��� ������ִ� ���� �� ���ϴ�.
	Node* colLine = (struct Node*)malloc(sizeof(Node));
	colLine->next = NULL;

	//colLine�� Ž���ϴ� �������̴�.
	Node* colLineCurrent = colLine;
	Node* current = header->next;

	//���ο� ��带 �������ϴ� �������̴�.
	Node* newNode;

	//��� ����� ���鿡 ���ؼ� Ž���Ѵ�.
	for (; current != NULL; current = current->next) {

		//���� ã�����ϴ� col�� ���� ���� ��带 �߰��ϸ� colLine�� �߰�
		if (current->col == targetCol) {

			//�� ��带 �����Ѵ�.
			newNode = (struct Node*)malloc(sizeof(Node));
			newNode->row = current->row;
			newNode->col = current->col;
			newNode->val = current->val;
			newNode->next = NULL;

			//������ ��带 colLine�� �߰��ϰ�, colLineCurrent�� �ѱ��.
			colLineCurrent->next = newNode;
			colLineCurrent = colLineCurrent->next;
		}
	}
	return colLine;
}

//X=A*B��� ��������
//header1=A
//header2=B
//�̴�.
void mmult(Node*header1, Node*header2) {
	Node* multHeader=NULL;//������� ����� header
	Node* currentMult;//������� ����� Ž���ϴ� ������
	Node* newNode;//���ο� ��带 ��Ī�ϴ� header
	Node* currentRow=NULL;//������� ����� �ϳ��� element�� ���Ͽ� �����Ǵ� A�� rowline�̴�.
	Node* currentCol=NULL;//������� ����� �ϳ��� element�� ���Ͽ� �����Ǵ� B�� colline�̴�.

	int totalnum = 0;//������� ����� element�� ���� �����̴�.
	int mul=0;//������� ����� element�� ���̴�.
	int row, col;//������� ����� �ϳ��� element�� row�� col�̴�.

	//��� A�� column�� ������ ��� B�� row�� ������ ���ƾ� ��İ����� �����ϴ�.
	if (header1->col != header2->row) {
		printf("��� ���� ������ �������� �ʽ��ϴ�.");
		exit(0);
	}

	multHeader = (Node*)malloc(sizeof(Node));//multHeader�� �̸� ����� �д�.
	multHeader->next = NULL;
	//�������� ���߿� �Ҵ��Ѵ�.

	currentMult = multHeader;

	for (row = 1; row <= header1->row; row++) {
		for (col = 1; col <= header2->col; col++) {
			currentRow = findRow(header1, row);// �����Ǵ� A�� rowline�� ���Ѵ�.
			currentCol = findCol(header2, col);// �����Ǵ� B�� colline�� ���Ѵ�.

			mul = 0;
			mul = multLine(currentRow, currentCol);
			if (mul != 0) {//���� mul���� 0�̸� multHeader�� �߰����� �ʴ´�.
				totalnum++;//���� ���� ��� ����� ���ڼ��� �ϳ� �߰���Ų��.

				//��� X�� node�� �����Ѵ�.
				newNode = (Node*)malloc(sizeof(Node));
				newNode->row = row; newNode->col = col; newNode->val = mul;
				newNode->next= NULL;

				//multHeader�� ������ ��带 �߰��Ѵ�.
				currentMult->next = newNode;
				currentMult = currentMult->next;
			}
		}
	}

	//multHeader�� ���� ���⼭ �־��ش�.
	//�ֳ��ϸ� ������ �������� totalnum�� ���� �����Ǳ� �����̴�.
	multHeader->row = header1->row;
	multHeader->col = header2->col;
	multHeader->val = totalnum;

	//���� ��� ���
	mwrite(multHeader);
}

//��� ����
void madd(Node*header1, Node*header2) {
	Node* addHeader;//���� ��� ��� ���
	Node* currentAdd;//���� �����ִ� ���� ���
	Node* newNode;//���ο� ��� ��� ������
	Node* currentNode1 = header1->next;
	Node* currentNode2 = header2->next;

	int valueNumber = 0; //���� ����� ���ڵ��� �����̴�.

	//�� ����� ��, ���� ũ�Ⱑ �ٸ��� �������� ���� 
	if (header1->row != header2->row || header1->col != header2->col) {
		printf("���� ������ �� ����� ũ�Ⱑ ���ƾ� �մϴ�.");
		exit(0);
	}

	//���� ����� ��带 ����
	addHeader = (struct Node*)malloc(sizeof(Node));
	addHeader->row = header1->row;
	addHeader->col = header1->col;
	addHeader->val = header1->val;
	addHeader->next = NULL;
	currentAdd = addHeader;

	//���� operation
	while (currentNode1!=NULL&& currentNode2!= NULL) {
		if (currentNode1->row < currentNode2->row) {//ù��° ����� ���� �ι�° ����� �ຸ�� ���� ���
			
			//ù��° ����� ���θ� ���δ�.
			newNode = (struct Node*)malloc(sizeof(Node));
			newNode->row = currentNode1->row;//������ �־��ش�.
			newNode->col = currentNode1->col;
			newNode->val = currentNode1->val;
			newNode->next = NULL;

			currentAdd->next = newNode;//newNode�� �߰��ϰ�
			valueNumber++;//���������� ���� �ϳ��� �þ��.

			currentAdd = currentAdd->next;//���� ���� �ǳʰ���
			currentNode1 = currentNode1->next;//currentNode1�� ���� �������Ѿ� �Ѵ�.
			//�̹� �ش��ϴ� ���� �߰��Ǿ��� �����̴�!
		}
		else if (currentNode1->row > currentNode2->row) {//ù��° ����� ���� �ι�° ����� �ຸ�� Ŭ ���
				//�ι�° ����� ���Ҹ� ���δ�.

			newNode = (struct Node*)malloc(sizeof(Node));
			newNode->row = currentNode2->row;//���� �־��ְ�
			newNode->col = currentNode2->col;
			newNode->val = currentNode2->val;
			newNode->next = NULL;

			currentAdd->next = newNode;//��带 �ٿ��ְ�
			valueNumber++;//���������� ���� �ϳ��� �þ��.

			currentAdd = currentAdd->next;
			currentNode2 = currentNode2->next;//currentNode2�� �������� �����Ѵ�.
		}
		else {//ù��° ����� ��� �ι�° ����� ���� ���� ���
			//�׶����ʹ� ���� ���Ѵ�.

			if (currentNode1->col < currentNode2->col) {//ù��° ����� ���� �ι�° ����� ������ ���� ���
				//ù��° ����� ���Ҹ� �״�� ���δ�.

				newNode = (struct Node*)malloc(sizeof(Node));
				newNode->row = currentNode1->row;
				newNode->col = currentNode1->col;
				newNode->val = currentNode1->val;
				newNode->next = NULL;

				currentAdd->next = newNode;
				valueNumber++;//���������� ���� �ϳ��� �þ��.

				currentAdd = currentAdd->next;
				currentNode1 = currentNode1->next;
			}
			else if (currentNode1->col > currentNode2->col) {//ù��° ����� ���� �ι�° ����� ������ Ŭ ���
				//�ι�° ����� ���Ҹ� �״�� ���δ�.

				newNode = (struct Node*)malloc(sizeof(Node));
				newNode->row = currentNode2->row;
				newNode->col = currentNode2->col;
				newNode->val = currentNode2->val;
				newNode->next = NULL;

				currentAdd->next = newNode;
				valueNumber++;//���������� ���� �ϳ��� �þ��.

				currentAdd = currentAdd->next;
				currentNode2 = currentNode2->next;
			}
			else { //�� ����� ���� ���� ������ ��ġ�� ��!
				//�� ����� ���ҵ��� ���� ����� ���δ�.

				int sum;
				sum = currentNode1->val + currentNode2->val;//�� ������ ��������� �����Ѵ�. 

				if (sum != 0) {//������ ����� 0�� �ƴ� ��쿡�� ��Ŀ� �ٿ��ش�.
					newNode = (struct Node*)malloc(sizeof(Node));
					newNode->row = currentNode2->row;//���currentNode1, currentNode2 �� �߿� �ƹ��ų� ��� ����.
					newNode->col = currentNode2->col;
					newNode->val = sum;//sum���� value ���� �ȴ�.
					newNode->next = NULL;

					currentAdd->next = newNode;//��带 �ٿ��ش�.
					valueNumber++;//���������� ���� �ϳ��� �þ��.

					currentAdd = currentAdd->next;
					currentNode1 = currentNode1->next;//
					currentNode2 = currentNode2->next;//�̹����� currentNode1, currentNode2 �Ѵ� �ϳ��� �Ű��ش�.
				}
				else {//������ ������ ����� 0�̶�� ���� �� ����� ��Ŀ� �ٿ��� �ʿ�� ����.

					//�׳� ���� ���ҷ� �Ѿ��.
					//currentNode1, currentNode2 �� �� �ϳ��� �Ű��ش�.
					currentNode1 = currentNode1->next;
					currentNode2 = currentNode2->next;
				}
			}
		}
	}
	//�� �輱�� ������ �������� �ݵ�� ù��° ���, �Ǵ� �ι�° ����� ���ڰ��� ������ ������ִ�.

	//���� ���� ����� ���� �ڿ��� ù��° ��Ŀ� ���ڵ��� ���� �����ִٸ�
	//ù��° ����� ���ڰ� �������� ���� ������ ��� ���ڵ��� �ٿ��ش�.
	while (currentNode1!=NULL) {
		newNode = (struct Node*)malloc(sizeof(Node));
		newNode->row = currentNode1->row;
		newNode->col = currentNode1->col;
		newNode->val = currentNode1->val;
		newNode->next = NULL;

		currentAdd->next = newNode;
		valueNumber++;//���������� ���� �ϳ��� �þ��.

		currentAdd = currentAdd->next;
		currentNode1 = currentNode1->next;
	}

	//���� ���� ����� ���� �ڿ��� �ι�° ��Ŀ� ���ڵ��� ���� �����ִٸ�
	//�ι�° ����� ���ڰ� �������� ���� ������ ��� ���ڵ��� �ٿ��ش�.
	while (currentNode2!=NULL) {
		newNode = (struct Node*)malloc(sizeof(Node));
		newNode->row = currentNode2->row;
		newNode->col = currentNode2->col;
		newNode->val = currentNode2->val;
		newNode->next = NULL;

		currentAdd->next = newNode;
		valueNumber++;//���������� ���� �ϳ��� �þ��.

		currentAdd = currentAdd->next;
		currentNode2 = currentNode2->next;
	}

	
	(addHeader->val)=valueNumber;

	//����� ����Ѵ�.
	mwrite(addHeader);
}

//����� �����ϴ� �Լ��̴�.
void merase(Node*header) {
	Node* temp;

	//header�� �ƹ��͵� ���� ���� ���������� ���������� �����Ѵ�.
	while (header != NULL)
	{
		temp = header;//���� ������ ���ڸ� �����Ѵ�.
		header = header->next;//header�� ���� header�� �ѱ��.
		free(temp);//���ڸ� �����Ѵ�.
	}
}

//����� ������ ����ϴ� �Լ��̴�.
void mwrite(Node*header) {
	int i, j;

	//���� ����ؾ� �� ���ڸ� ��Ī�ϴ� �������̴�.
	Node* currentPrint = header->next;//header�� ������ ���ڰ��� ����ؾ� �Ѵ�.


	//�� �κ��� header�� ���� ��������̴�. ��, ��� ��ü�� ���� �����̴�.
	printf("**�Է��Ͻ� ���(Ȥ�� ������) <���� ��:%d, ���Ǽ�:%d, ���ڼ�:%d>**\n\n", header->row, header->col, header->val);
	printf("�Է���(Ȥ�� ������) ����� ���-------->>\n\n");

	//���⼭ ���ʹ� ���ڰ��� ���� �����̴�.
	for (i = 0; i < header->row; i++) { //��� rows�� ���Ͽ� ���, 
		for (j = 0;  j< header->col; j++) {// ��� columns�鿡 ���Ͽ� ����Ѵ�.

			if (currentPrint == NULL) {//����, �̹� ��� ����� ���ڿ� ���� ����� ��������,
				printf("	0");//0�� ����Ѵ�.
			}
			else {
				//����, ���� ����� ������ �ʾҰ�, ���� ��Ī�ϰ� �ִ� ������ row, column���� ���� i��°,j��°�� ��ġ�ϸ�
				if (currentPrint->row == (i + 1) && currentPrint->col == (j + 1)) {
					printf("	%d",currentPrint->val);//������ value���� ����ϰ�
					currentPrint = currentPrint->next;//���� ���ڷ� �������Ѵ�.
				}
				else {
					//�� �������� ��µ� ���ڰ� �ƴ϶��, 0�� ����Ѵ�.
					printf("	0");
				}
			}
		}
		printf("\n");
	}
}

//row�� ����, col�� ������ �������� ��� sort�̴�.
void bubbleSort(struct Node *start)
{
	int swapped, i;
	struct Node *ptr1;
	struct Node *ptr2;
	struct Node *lptr = NULL;

	//Ȥ���� ����� ����ִ��� Ȯ���Ѵ�.
	if (start == NULL)
		return;

	//Ȥ���� ����� ����� ���� 1������ Ȯ���Ѵ�.
	if (start->next == NULL)
		return;

	do
	{
		//swapped�� �ɶ����� �Ѵ�.
		swapped = 0;
		ptr1 = start->next;
		ptr2 = ptr1->next;

		//ptr1�� ������ ���(lptr)�� ������ ������ ������ �����Ѵ�.
		while (ptr1->next != lptr)
		{
			if (ptr1->row > ptr2->row)//row�� ���� ����Ѵ�.
			{
				swap(ptr1, ptr1->next);//�� ��带 �ٲ۴�.
				swapped = 1;//�ٲپ��ٴ� ǥ���̴�.
			}
			else if (ptr1->row == ptr2->row) {//row�� ������ col�� ����Ѵ�.
				if (ptr1->col > ptr2->col)
				{
					swap(ptr1, ptr1->next);//�� ��带 �ٲ۴�.
					swapped = 1;//�ٲپ��ٴ� ǥ���̴�.
				}
			}
			ptr1 = ptr1->next;//���� ��带 �θ���.
			ptr2 = ptr2->next;//���� ��带 �θ���.
		}
		lptr = ptr1;
	} while (swapped);
}

//������ ���� ��ȯ�ϴ� �Լ��̴�.
void swap(struct Node *a, struct Node *b)
{
	//row�� �ٲ۴�.
	int row = a->row;
	a->row = b->row;
	b->row = row;

	//col�� �ٲ۴�.
	int col = a->col;
	a->col = b->col;
	b->col = col;

	//val�� �ٲ۴�.
	int val = a->val;
	a->val = b->val;
	b->val = val;
}

//����� ���� ����ڷκ��� �޾ƿ��� �Լ��̴�.
Node* mread(Node* header) {
	int inputRow, inputCol, inputVal;
	int i;
	int row, col;
	Node* currentNode;
	Node* newNode;

	//header��带 �켱 �����.
	printf("**��, �� �׸��� 0�� �ƴ� ���� ���� �Է�(����:3/2/4). �ݵ�� ���Ŀ� ���� �ּ���**\n\n");
	printf("------------------------------>> ");
	scanf("%d/%d/%d", &inputRow, &inputCol, &inputVal);
	header = (struct Node*)malloc(sizeof(Node));
	header->row = inputRow; header->col = inputCol;  header->val = inputVal;
	header->next = NULL;
	currentNode = header;

	//���� ����� ũ�⺸�� ������ ���� �� �������� �ȵ�����, exceptionó���Ѵ�.
	if ((inputRow*inputCol) < inputVal) {
		printf("����� ũ�⺸�� �� ���� ���ڸ� ���� ���� �����ϴ�.");
		exit(0);
	}

	for (i = 0; i < (header->val); i++) {
		printf("%d��°����------------------------->> ",i+1);
		scanf("%d/%d/%d", &inputRow, &inputCol, &inputVal);

		//���� �Է��ϴ� row, col���� ����� ũ�⺸�� ũ��, exceptionó���Ѵ�.
		if (inputRow > header->row || inputCol > header->col) {
			printf("�ִ� ���ũ�⸦ �ʰ��߽��ϴ�.");
			exit(0);
		}

		//����� value���� 0�� ���� ���� ���ǹ��ϴ�.
		//�׷��Ƿ�, exceptionó���Ѵ�.
		if (inputVal == 0) {
			printf("������ 0�� �� ���� �����ϴ�.");
			exit(0);
		}

		//�Է°��� �޾� ����� ���ڸ� �޾��ش�.
		newNode = (struct Node*)malloc(sizeof(Node));
		newNode->row = inputRow; newNode->col = inputCol;  newNode->val = inputVal;
		newNode->next = NULL;
		currentNode->next = newNode;
		currentNode = currentNode->next;
	}

	//������� ���� �������ش�.
	bubbleSort(header);

	//�Է¹��� ����� ����Ѵ�.
	mwrite(header);
}

//����� transpose�� ����ϴ� �Լ��̴�.
Node* mtranspose(Node*header) {
	Node*currentTrans = header;
	int temp;
	
	//��� ������ row�� col�� ���� ���� ��ȯ�Ѵ�.
	for (; currentTrans != NULL; currentTrans = currentTrans->next) {
		temp = currentTrans->col;
		currentTrans->col = currentTrans->row;
		currentTrans->row = temp;
	}

	//��ȯ�� �����Ͽ� ������ �°� ���ش�.
	bubbleSort(header);

	//����� ����Ѵ�.
	mwrite(header);
}

