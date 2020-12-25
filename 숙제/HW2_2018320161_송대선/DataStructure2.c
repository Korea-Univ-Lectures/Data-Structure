#include <stdio.h>
#include <stdlib.h>

//행렬의 노드 구조체이다.
typedef struct Node {
	int row;
	int col;
	int val;
	struct node* next;
}Node;

//////////////////////
Node* mread(Node* header); //행렬입력을 받는 함수
void mwrite(Node*header); //행렬값을 출력하는 함수
void merase(Node*header); //행렬을 제거하는 함수
Node* mtranspose(Node*header); //행렬의 transpose
void madd(Node*header1, Node*header2); //행렬 덧셈
void mmult(Node*header1, Node*header2); //행렬 곱셈

Node* findRow(Node*header, int targetRow); //targetRow번째 row를 찾는 함수
Node* findCol(Node*header, int targetCol); //targetCol번째 col을 찾는 함수
int multLine(Node*rowLine, Node*colLine); //하나의 row와 하나의 col을 대상으로 곱셈을 진행하는 함수

void bubbleSort(struct Node *start); //행렬 linkedlist를 순서대로 정렬하는 함수
void swap(struct Node *a, struct Node *b); //행렬값을 swap하는 함수

////////////////////
void main() {
	Node* head1 = NULL;//첫번째 행렬의 header
	Node* head2 = NULL;//두번째 행렬의 header

	int inputInt=0;//메뉴선택을 결정하는 값

	printf("***************************************************************************\n\n\n");
	printf("                                                         자료구조 2차 Assignment\n");
	printf("                                                        컴퓨터학과 송대선\n\n\n\n\n");
	printf("*****************************************************************************\n\n");
	printf("메뉴선택---------------------------------------------------------------------\n\n");
	printf("     [1]희소 행렬 입력하기 [2]끝내기     \n\n");
	printf("----------------------------------------------------------------------------\n\n");
	printf("---(원하는 메뉴를 선택해 주세요)--->> ");
	scanf("%d",&inputInt);

	if (inputInt == 1) {
		head1= mread(head1);//첫번째 희소행렬을 입력

		printf("두번째 메뉴선택--------------------------------------------------------------\n\n");
		printf("     [1]두번때 희소 행렬 입력하기(덧셈, 곱셈) [2]첫번째 입력 행렬 Transpose [3]끝내기\n\n");
		printf("----------------------------------------------------------------------------\n\n");
		printf("---(원하는 메뉴를 선택해 주세요)--->> ");
		scanf("%d", &inputInt);

		if (inputInt == 1) {
			head2 = mread(head2);//두번째 희소행렬을 입력

			printf("세번째 메뉴선택--------------------------------------------------------------\n\n");
			printf("     [1]두 행렬 간의 덧셈 연산 [2]두 행렬 간의 곱셈 연산 [3]끝내기\n\n");
			printf("----------------------------------------------------------------------------\n\n");
			printf("---(원하는 메뉴를 선택해 주세요)--->> ");
			scanf("%d", &inputInt);

			if (inputInt == 1) {
				madd(head1, head2);//행렬 덧셈
				printf("행렬 덧셈이 끝났습니다. 프로그램을 종료합니다.");
				return;
			}
			else if (inputInt == 2) {
				mmult(head1, head2);//행렬 곱셈
				printf("행렬 곱셈이 끝났습니다. 프로그램을 종료합니다.");
				return;
			}
			else if (inputInt == 3) {
				printf("프로그램을 종료합니다.");
				return;
			}
			else {
				printf("오류가 발생했습니다. 프로그램을 강제종료합니다.");
				exit(1);
			}
		}
		else if (inputInt == 2) {
			head1=mtranspose(head1);//행렬 transpose
		}
		else if (inputInt == 3)
		{
			printf("프로그램을 종료합니다.");
			return;
		}
		else {
			printf("오류가 발생했습니다. 프로그램을 강제종료합니다.");
			exit(1);
		}
	}
	else if (inputInt==2) {
		printf("프로그램을 종료합니다.");
		return;
	}
	else {
		printf("오류가 발생했습니다. 프로그램을 강제종료합니다.");
		exit(1);
	}

}

int multLine(Node*rowLine, Node*colLine) {
	//rowLine은 동일한 row값, colLine은 동일한 col값을 가진다.
	Node* currentRow= rowLine->next;
	Node* currentCol = colLine->next;
	int sum = 0;

	//곱셈은 rowline의 element의 col값과 colline의 element의 row값이 동일해야
	//곱해지고, 곱해진 값을 모두 더한다.
	while( currentRow != NULL&&currentCol != NULL ) {

		//만일 rowline의 element의 col값이
		//colline의 element의 row값보다 작으면
		//다음번째 currentRow을 불러온다.
		if (currentRow->col < currentCol->row) {
			currentRow = currentRow->next;
		}

		//만일 rowline의 element의 col값이
		//colline의 element의 row값보다 작으면
		//다음번째 currentCol을 불러온다.
		else if (currentRow->col > currentCol->row) {
			currentCol = currentCol->next;
		}

		//만일 rowline의 element의 col값이
		//colline의 element의 row값과 같으면
		//둘을 곱하여 더한다.
		//그리고 다음번을 각각 구한다.
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
	//우선 rowLine의 쓰레기 해더를 만들어주는 것이 더 편하다.

	rowLine->next = NULL;

	//rowLine을 탐색하는 포인터이다.
	Node* rowLineCurrent=rowLine;
	Node* current=header->next;

	//새로운 노드를 포인팅하는 포인터이다.
	Node* newNode;

	//모든 행렬의 노드들에 대해서 탐색한다.
	for (; current != NULL; current = current->next) {

		//만일 찾고자하는 row의 값을 가진 노드를 발견하면 rowLine에 추가
		if (current->row == targetRow) {

			//그 노드를 복사한다.
			newNode = (struct Node*)malloc(sizeof(Node));
			newNode->row = current->row;
			newNode->col = current->col;
			newNode->val = current->val;
			newNode->next = NULL;

			//복사한 노드를 rowLine에 추가하고, rowLineCurrent를 넘긴다.
			rowLineCurrent->next = newNode;
			rowLineCurrent = rowLineCurrent->next;
		}
	}
	return rowLine;
}
Node* findCol(Node*header, int targetCol) {

	//우선 colLine의 쓰레기 해더를 만들어주는 것이 더 편하다.
	Node* colLine = (struct Node*)malloc(sizeof(Node));
	colLine->next = NULL;

	//colLine을 탐색하는 포인터이다.
	Node* colLineCurrent = colLine;
	Node* current = header->next;

	//새로운 노드를 포인팅하는 포인터이다.
	Node* newNode;

	//모든 행렬의 노드들에 대해서 탐색한다.
	for (; current != NULL; current = current->next) {

		//만일 찾고자하는 col의 값을 가진 노드를 발견하면 colLine에 추가
		if (current->col == targetCol) {

			//그 노드를 복사한다.
			newNode = (struct Node*)malloc(sizeof(Node));
			newNode->row = current->row;
			newNode->col = current->col;
			newNode->val = current->val;
			newNode->next = NULL;

			//복사한 노드를 colLine에 추가하고, colLineCurrent를 넘긴다.
			colLineCurrent->next = newNode;
			colLineCurrent = colLineCurrent->next;
		}
	}
	return colLine;
}

//X=A*B라고 생각하자
//header1=A
//header2=B
//이다.
void mmult(Node*header1, Node*header2) {
	Node* multHeader=NULL;//곱셈결과 행렬의 header
	Node* currentMult;//곱셈결과 행렬을 탐색하는 포인터
	Node* newNode;//새로운 노드를 지칭하는 header
	Node* currentRow=NULL;//곱셈결과 행렬의 하나의 element에 대하여 대응되는 A의 rowline이다.
	Node* currentCol=NULL;//곱셈결과 행렬의 하나의 element에 대하여 대응되는 B의 colline이다.

	int totalnum = 0;//곱셈결과 행렬의 element의 값의 갯수이다.
	int mul=0;//곱셈결과 행렬의 element의 값이다.
	int row, col;//곱셈결과 행렬의 하나의 element의 row와 col이다.

	//행렬 A의 column의 갯수와 행렬 B의 row의 갯수가 같아야 행렬곱셈이 가능하다.
	if (header1->col != header2->row) {
		printf("행렬 곱의 조건이 만족되지 않습니다.");
		exit(0);
	}

	multHeader = (Node*)malloc(sizeof(Node));//multHeader를 미리 만들어 둔다.
	multHeader->next = NULL;
	//실제값은 나중에 할당한다.

	currentMult = multHeader;

	for (row = 1; row <= header1->row; row++) {
		for (col = 1; col <= header2->col; col++) {
			currentRow = findRow(header1, row);// 대응되는 A의 rowline을 구한다.
			currentCol = findCol(header2, col);// 대응되는 B의 colline을 구한다.

			mul = 0;
			mul = multLine(currentRow, currentCol);
			if (mul != 0) {//만일 mul값이 0이면 multHeader에 추가하지 않는다.
				totalnum++;//곱셈 연산 결과 행렬의 인자수를 하나 추가시킨다.

				//행렬 X의 node를 생성한다.
				newNode = (Node*)malloc(sizeof(Node));
				newNode->row = row; newNode->col = col; newNode->val = mul;
				newNode->next= NULL;

				//multHeader에 생성된 노드를 추가한다.
				currentMult->next = newNode;
				currentMult = currentMult->next;
			}
		}
	}

	//multHeader의 값을 여기서 넣어준다.
	//왜냐하면 곱셈이 끝나야지 totalnum의 값이 결정되기 때문이다.
	multHeader->row = header1->row;
	multHeader->col = header2->col;
	multHeader->val = totalnum;

	//곱셈 결과 출력
	mwrite(multHeader);
}

//행렬 덧셈
void madd(Node*header1, Node*header2) {
	Node* addHeader;//덧셈 결과 행렬 헤드
	Node* currentAdd;//현제 보고있는 더셈 결과
	Node* newNode;//새로운 행렬 노드 포인터
	Node* currentNode1 = header1->next;
	Node* currentNode2 = header2->next;

	int valueNumber = 0; //덧셈 행렬의 인자들의 갯수이다.

	//두 행렬의 행, 열의 크기가 다르면 실행하지 않음 
	if (header1->row != header2->row || header1->col != header2->col) {
		printf("덧셈 연산은 두 행렬의 크기가 같아야 합니다.");
		exit(0);
	}

	//덧셈 행렬의 헤드를 설정
	addHeader = (struct Node*)malloc(sizeof(Node));
	addHeader->row = header1->row;
	addHeader->col = header1->col;
	addHeader->val = header1->val;
	addHeader->next = NULL;
	currentAdd = addHeader;

	//덧셈 operation
	while (currentNode1!=NULL&& currentNode2!= NULL) {
		if (currentNode1->row < currentNode2->row) {//첫번째 행렬의 행이 두번째 행렬의 행보다 작을 경우
			
			//첫번째 행렬의 원로를 붙인다.
			newNode = (struct Node*)malloc(sizeof(Node));
			newNode->row = currentNode1->row;//값들을 넣어준다.
			newNode->col = currentNode1->col;
			newNode->val = currentNode1->val;
			newNode->next = NULL;

			currentAdd->next = newNode;//newNode를 추가하고
			valueNumber++;//덧셈인자의 값이 하나더 늘어난다.

			currentAdd = currentAdd->next;//다음 노드로 건너간다
			currentNode1 = currentNode1->next;//currentNode1을 노드로 설정시켜야 한다.
			//이미 해당하는 노드는 추가되었기 때문이다!
		}
		else if (currentNode1->row > currentNode2->row) {//첫번째 행렬의 행이 두번째 행렬의 행보다 클 경우
				//두번째 행렬의 원소를 붙인다.

			newNode = (struct Node*)malloc(sizeof(Node));
			newNode->row = currentNode2->row;//값을 넣어주고
			newNode->col = currentNode2->col;
			newNode->val = currentNode2->val;
			newNode->next = NULL;

			currentAdd->next = newNode;//노드를 붙여주고
			valueNumber++;//덧셈인자의 값이 하나더 늘어난다.

			currentAdd = currentAdd->next;
			currentNode2 = currentNode2->next;//currentNode2의 다음으로 가야한다.
		}
		else {//첫번째 행렬의 행과 두번째 행렬의 행이 같은 경우
			//그때부터는 열을 비교한다.

			if (currentNode1->col < currentNode2->col) {//첫번째 행렬의 열이 두번째 행렬의 열보다 작은 경우
				//첫번째 행렬의 원소를 그대로 붙인다.

				newNode = (struct Node*)malloc(sizeof(Node));
				newNode->row = currentNode1->row;
				newNode->col = currentNode1->col;
				newNode->val = currentNode1->val;
				newNode->next = NULL;

				currentAdd->next = newNode;
				valueNumber++;//덧셈인자의 값이 하나더 늘어난다.

				currentAdd = currentAdd->next;
				currentNode1 = currentNode1->next;
			}
			else if (currentNode1->col > currentNode2->col) {//첫번째 행렬의 열이 두번째 행렬의 열보다 클 경우
				//두번째 행렬의 원소를 그대로 붙인다.

				newNode = (struct Node*)malloc(sizeof(Node));
				newNode->row = currentNode2->row;
				newNode->col = currentNode2->col;
				newNode->val = currentNode2->val;
				newNode->next = NULL;

				currentAdd->next = newNode;
				valueNumber++;//덧셈인자의 값이 하나더 늘어난다.

				currentAdd = currentAdd->next;
				currentNode2 = currentNode2->next;
			}
			else { //두 행렬의 열과 행이 완전히 일치할 때!
				//두 행렬의 원소들을 더한 결과를 붙인다.

				int sum;
				sum = currentNode1->val + currentNode2->val;//두 원소의 덧셈결과를 저장한다. 

				if (sum != 0) {//덧셈의 결과가 0이 아닌 경우에만 행렬에 붙여준다.
					newNode = (struct Node*)malloc(sizeof(Node));
					newNode->row = currentNode2->row;//사실currentNode1, currentNode2 둘 중에 아무거나 상관 없다.
					newNode->col = currentNode2->col;
					newNode->val = sum;//sum값이 value 값이 된다.
					newNode->next = NULL;

					currentAdd->next = newNode;//노드를 붙여준다.
					valueNumber++;//덧셈인자의 값이 하나더 늘어난다.

					currentAdd = currentAdd->next;
					currentNode1 = currentNode1->next;//
					currentNode2 = currentNode2->next;//이번에는 currentNode1, currentNode2 둘다 하나씩 옮겨준다.
				}
				else {//만약의 덧셈의 결과가 0이라면 굳이 그 결과를 행렬에 붙여줄 필요는 없다.

					//그냥 다음 원소로 넘어간다.
					//currentNode1, currentNode2 둘 다 하나씩 옮겨준다.
					currentNode1 = currentNode1->next;
					currentNode2 = currentNode2->next;
				}
			}
		}
	}
	//이 계선이 끝나고난 다음에는 반드시 첫번째 행렬, 또는 두번째 행렬의 인자값이 완전히 사라져있다.

	//위와 같은 계산이 끝난 뒤에도 첫번째 행렬에 인자들이 아직 남아있다면
	//첫번째 행렬의 인자가 남아있지 않을 때까지 계속 인자들을 붙여준다.
	while (currentNode1!=NULL) {
		newNode = (struct Node*)malloc(sizeof(Node));
		newNode->row = currentNode1->row;
		newNode->col = currentNode1->col;
		newNode->val = currentNode1->val;
		newNode->next = NULL;

		currentAdd->next = newNode;
		valueNumber++;//덧셈인자의 값이 하나더 늘어난다.

		currentAdd = currentAdd->next;
		currentNode1 = currentNode1->next;
	}

	//위와 같은 계산이 끝난 뒤에도 두번째 행렬에 인자들이 아직 남아있다면
	//두번째 행렬의 인자가 남아있지 않을 때까지 계속 인자들을 붙여준다.
	while (currentNode2!=NULL) {
		newNode = (struct Node*)malloc(sizeof(Node));
		newNode->row = currentNode2->row;
		newNode->col = currentNode2->col;
		newNode->val = currentNode2->val;
		newNode->next = NULL;

		currentAdd->next = newNode;
		valueNumber++;//덧셈인자의 값이 하나더 늘어난다.

		currentAdd = currentAdd->next;
		currentNode2 = currentNode2->next;
	}

	
	(addHeader->val)=valueNumber;

	//행렬을 출력한다.
	mwrite(addHeader);
}

//행렬을 삭제하는 함수이다.
void merase(Node*header) {
	Node* temp;

	//header에 아무것도 남아 있지 않을때까지 다음과정을 진행한다.
	while (header != NULL)
	{
		temp = header;//당장 삭제할 인자를 지정한다.
		header = header->next;//header를 다음 header로 넘긴다.
		free(temp);//인자를 삭제한다.
	}
}

//행렬의 정보를 출력하는 함수이다.
void mwrite(Node*header) {
	int i, j;

	//현제 출력해야 할 인자를 지칭하는 포인터이다.
	Node* currentPrint = header->next;//header를 제외한 인자값을 출력해야 한다.


	//이 부분은 header에 대한 정보출력이다. 즉, 행렬 전체에 대한 정보이다.
	printf("**입력하신 행렬(혹은 연산한) <행의 수:%d, 열의수:%d, 인자수:%d>**\n\n", header->row, header->col, header->val);
	printf("입력한(혹은 연산한) 행렬의 모습-------->>\n\n");

	//여기서 부터는 인자값에 대한 정보이다.
	for (i = 0; i < header->row; i++) { //모든 rows에 대하여 출력, 
		for (j = 0;  j< header->col; j++) {// 모든 columns들에 대하여 출력한다.

			if (currentPrint == NULL) {//만일, 이미 모든 행렬의 인자에 대한 출력이 끝났으면,
				printf("	0");//0을 출력한다.
			}
			else {
				//만일, 아직 출력이 끝나지 않았고, 현재 지칭하고 있는 인자의 row, column값이 각각 i번째,j번째와 일치하면
				if (currentPrint->row == (i + 1) && currentPrint->col == (j + 1)) {
					printf("	%d",currentPrint->val);//인자의 value값을 출력하고
					currentPrint = currentPrint->next;//다음 인자로 포인팅한다.
				}
				else {
					//이 시점에서 출력될 인자가 아니라면, 0을 출력한다.
					printf("	0");
				}
			}
		}
		printf("\n");
	}
}

//row를 먼저, col을 나중의 기준으로 삼는 sort이다.
void bubbleSort(struct Node *start)
{
	int swapped, i;
	struct Node *ptr1;
	struct Node *ptr2;
	struct Node *lptr = NULL;

	//혹여나 행렬이 비어있는지 확인한다.
	if (start == NULL)
		return;

	//혹여나 행렬의 노드의 수가 1개인지 확인한다.
	if (start->next == NULL)
		return;

	do
	{
		//swapped이 될때까지 한다.
		swapped = 0;
		ptr1 = start->next;
		ptr2 = ptr1->next;

		//ptr1가 마지막 노드(lptr)의 직전에 도착할 때까지 진행한다.
		while (ptr1->next != lptr)
		{
			if (ptr1->row > ptr2->row)//row를 먼저 고려한다.
			{
				swap(ptr1, ptr1->next);//두 노드를 바꾼다.
				swapped = 1;//바꾸었다는 표시이다.
			}
			else if (ptr1->row == ptr2->row) {//row가 같으면 col을 고려한다.
				if (ptr1->col > ptr2->col)
				{
					swap(ptr1, ptr1->next);//두 노드를 바꾼다.
					swapped = 1;//바꾸었다는 표시이다.
				}
			}
			ptr1 = ptr1->next;//다음 노드를 부른다.
			ptr2 = ptr2->next;//다음 노드를 부른다.
		}
		lptr = ptr1;
	} while (swapped);
}

//인자의 값을 교환하는 함수이다.
void swap(struct Node *a, struct Node *b)
{
	//row를 바꾼다.
	int row = a->row;
	a->row = b->row;
	b->row = row;

	//col을 바꾼다.
	int col = a->col;
	a->col = b->col;
	b->col = col;

	//val을 바꾼다.
	int val = a->val;
	a->val = b->val;
	b->val = val;
}

//노드의 값을 사용자로부터 받아오는 함수이다.
Node* mread(Node* header) {
	int inputRow, inputCol, inputVal;
	int i;
	int row, col;
	Node* currentNode;
	Node* newNode;

	//header노드를 우선 만든다.
	printf("**행, 열 그리고 0이 아닌 값의 개수 입력(예시:3/2/4). 반드시 형식에 맞춰 주세요**\n\n");
	printf("------------------------------>> ");
	scanf("%d/%d/%d", &inputRow, &inputCol, &inputVal);
	header = (struct Node*)malloc(sizeof(Node));
	header->row = inputRow; header->col = inputCol;  header->val = inputVal;
	header->next = NULL;
	currentNode = header;

	//만일 행렬의 크기보다 인자의 수가 더 많아지면 안됨으로, exception처리한다.
	if ((inputRow*inputCol) < inputVal) {
		printf("행렬의 크기보다 더 많은 인자를 넣을 수는 없습니다.");
		exit(0);
	}

	for (i = 0; i < (header->val); i++) {
		printf("%d번째원소------------------------->> ",i+1);
		scanf("%d/%d/%d", &inputRow, &inputCol, &inputVal);

		//만일 입력하는 row, col값이 행렬의 크기보다 크면, exception처리한다.
		if (inputRow > header->row || inputCol > header->col) {
			printf("최대 행렬크기를 초과했습니다.");
			exit(0);
		}

		//행렬의 value값에 0이 들어가는 것은 무의미하다.
		//그러므로, exception처리한다.
		if (inputVal == 0) {
			printf("값으로 0을 쓸 수는 없습니다.");
			exit(0);
		}

		//입력값을 받아 행렬의 인자를 받아준다.
		newNode = (struct Node*)malloc(sizeof(Node));
		newNode->row = inputRow; newNode->col = inputCol;  newNode->val = inputVal;
		newNode->next = NULL;
		currentNode->next = newNode;
		currentNode = currentNode->next;
	}

	//순서대로 버블 소팅해준다.
	bubbleSort(header);

	//입력받은 행렬을 출력한다.
	mwrite(header);
}

//행렬의 transpose를 계산하는 함수이다.
Node* mtranspose(Node*header) {
	Node*currentTrans = header;
	int temp;
	
	//모든 노드들의 row와 col의 값을 서로 교환한다.
	for (; currentTrans != NULL; currentTrans = currentTrans->next) {
		temp = currentTrans->col;
		currentTrans->col = currentTrans->row;
		currentTrans->row = temp;
	}

	//교환후 소팅하여 순서가 맞게 해준다.
	bubbleSort(header);

	//행렬을 출력한다.
	mwrite(header);
}

