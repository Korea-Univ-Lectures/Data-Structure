//이 프로그램은 heap sort를 이용하여 edge를 정렬한다.
#include <stdio.h>
#include <stdlib.h>

//edge 구조체를 정의한다.
typedef struct _edge {
	int node1;
	int node2;
	int weight;
}edge;

//////////////////
void adjust(edge a[], int root, int n);
void heapSort(edge a[], int n);
int KRUSKALSALGORITHM(edge edges[], int spannedEdges[], 
	int maximumEdges, int maximumSpannedEdges, int nodes[]);
int find(int disjointSets[], int element);
void _union(int disjointSets[], int rootHeader, int leafheader);
int isConnected(edge edges[], int nodeNumber, int edgeNumber);
//////////////////

int main() {
	int nodeNumber;//사용자가 입력하는 node의 갯수이다.
	int edgeNumber;//사용자가 입력하는 edge의 갯수이다.
	int i;
	int hasSpanTree; //사용자가 입려간 Graph에서 spannedTree가 나올 수 있는 지 판단한다.
	
	//사용자로부터 node의 갯수를 입력받는다.
	printf("Node를 몇개 만드시겠습니까? (Node는 1개 이상이어야 합니다.): ");
	scanf("%d",&nodeNumber);

	if (nodeNumber <= 0){
		printf("Node는 1개 이상이어야 합니다!\n");
		return 1;
	}

	//만들어진 노드를 출력해줍니다.
	for (i = 0; i < nodeNumber; i++) {
		if (i == 0)
			printf("Node 0");
		else
			printf(", %d", i);
	}
	printf("이 만들어 졌습니다.\n");

	//사용자로부터 만들 edge의 갯수를 입력받는다.
	printf("Edge를 몇개 만드시겠습니까? (Edge는 0개 이상이어야 합니다.): ");
	scanf("%d", &edgeNumber);

	if (edgeNumber < 0) {
		printf("Edge는 0개 이상이어야 합니다!\n");
		return 1;
	}

	//edge의 배열을 초기화시킨다.
	edge* graphEdges = (edge*)malloc(sizeof(edge) * (edgeNumber + 1));
	for (i = 0; i <= edgeNumber; i++)
		graphEdges[i].weight = -1;

	int* spannedGraphNodes = (int*)malloc(sizeof(int) * nodeNumber);
	int* spannedGraphEdges = (int*)malloc(sizeof(int) * (nodeNumber - 1));

	for (i = 1; i < edgeNumber+1; i++) {
		printf("%d번째 edge (node1/node2/weight): ", i);
		scanf("%d/%d/%d", &graphEdges[i].node1, &graphEdges[i].node2, &graphEdges[i].weight);

		//edge는 이미 만들어진 Node들을 이용해서만 만들어야 한다.
		if (graphEdges[i].node1 >= nodeNumber || graphEdges[i].node2 >= nodeNumber
			|| graphEdges[i].node1 < 0 || graphEdges[i].node2 < 0) {
			printf("존재하는 Node들만을 입력하여 주십시오");

			free(spannedGraphEdges);
			free(spannedGraphNodes);
			free(graphEdges);
			return 1;
		}

		//edge가 이어주는 Node들은 ascent하게 배열한다.
		//이는 중복되는 edge를 걸러내기 위함이다.
		if (graphEdges[i].node1 > graphEdges[i].node2) {
			int temp = graphEdges[i].node2;
			graphEdges[i].node2 = graphEdges[i].node1;
			graphEdges[i].node1 = temp;
		}

		//만일, 시작 Vertex와 끝 Vertex가 동일하다면, self edge이므로, 제외시켜야 한다.
		if (graphEdges[i].node1 == graphEdges[i].node2) {
			printf("self edge는 고려하지 않습니다.");

			free(spannedGraphEdges);
			free(spannedGraphNodes);
			free(graphEdges);
			return 1;
		}

		//중복되는 edge가 있는지 검사한다.
		int j;
		for (j = 1; j < i; j++)
		{
			if ((graphEdges[j].node1 == graphEdges[i].node1) && (graphEdges[j].node2 == graphEdges[i].node2))
			{
				printf("중복되는 edge는 허용하지 않습니다.");

				free(spannedGraphEdges);
				free(spannedGraphNodes);
				free(graphEdges);
				return 1;
			}
		}

		//입력된 edge의 weight은 non-negative한 값이다.
		if (graphEdges[i].weight < 0) {
			printf("weight는 음수가 아닌 수여야 합니다.");

			free(spannedGraphEdges);
			free(spannedGraphNodes);
			free(graphEdges);
			return 1;
		}
			
	}


	//사용자로부터 모든 edge의 값을 받으면, 사용자가 입력한 Graph가 Connected 되었는지 판단한다.
	//Kruskal's Algorithm과 같은 Spanning Tree를 만드는 알고리즘은 graph가 connected되어있다는 가정이 있다.
	int hasConnectedGraph = isConnected(graphEdges, nodeNumber, edgeNumber);
	if (!hasConnectedGraph) {
		printf("Graph가 Connected되지 않았습니다.");

		free(spannedGraphEdges);
		free(spannedGraphNodes);
		free(graphEdges);
		return 1;
	}

	printf("\n");

	//spanned된 graph의 Node들을 초기화 해줍니다.
	//spannedGraphNodes에는 자신의 parent의 index가 들어갑니다.
	//-1은 그 node가 root라는 것을 의미합니다.
	for (i = 0; i < nodeNumber; i++) {
		spannedGraphNodes[i] = -1;
	}

	//spanned된 graph의 Edge들을 초기화 해줍니다.
	for (i = 0; i < nodeNumber-1; i++) {
		spannedGraphEdges[i] = -1;
	}

	//맨 첫번째 Edge를 초기화 (graphEdges[0]은 값을 저장하지 않음.)
	graphEdges[0].node1 = -1; graphEdges[0].node2 = -1; graphEdges[0].weight = -1;

	//graphEdges를 weigth를 기준으로한 오름차순으로 정렬
	heapSort(graphEdges, edgeNumber);

	//spanned tree가 있는지의 여부를 확인
	hasSpanTree = KRUSKALSALGORITHM(graphEdges, spannedGraphEdges,
		edgeNumber, nodeNumber-1, spannedGraphNodes);

	//spanned tree가 있으면 관련된 edge들을 출력한다.
	//없으면 없다고 출력한다.
	if (hasSpanTree) {
		printf("Spanned Tree의 edges는 다음과 같습니다. \n");
		printf("(Node1, Node2)->weight\n");
		for (i = 0; i < nodeNumber - 1; i++)
			printf("(%d, %d)->%d\n", graphEdges[spannedGraphEdges[i]].node1, graphEdges[spannedGraphEdges[i]].node2, graphEdges[spannedGraphEdges[i]].weight);
	}
	else
		printf("No spanning tre...\n");

	//메모리를 해체해주고 종료
	free(spannedGraphEdges);
	free(spannedGraphNodes);
	free(graphEdges);
	return 0;
}

//과제에서 요구하는 Kruskal`s Algorithm
//edges는 사용자가 입력한 정렬된 edge들, spannedEdges는 spanned tree에 필요한 edge들의 index값들이다.
//maximumEdges은 edges의 edge 갯수 maximumSpannedEdges은 spannedEdges의 edge 갯수이다.
//nodes는 사용자가 입력한 node를 의미한다. -> 여기서는 node들을 Set Representation by Trees으로 간주한다.
int KRUSKALSALGORITHM(edge edges[], int spannedEdges[], 
	int maximumEdges, int maximumSpannedEdges, int nodes[]) {

	int graphEdgeIndex = 0;//edges의 index를 의미한다.
	int spannedEgdeIndex = 0;//spannedEdges의 index를 의미한다. -> "T= {};"를 의미한다.

	//"while ( T contains less than n-1 edges && E is not empty )"를 의미한다.
	//spannedEdges가 n-1개가 되거나, edges에 더 이상 남아있는 edge가 없을 때까지 계속 while loop을 돌린다.
	while (spannedEdges[maximumSpannedEdges - 1] == -1 && graphEdgeIndex < maximumEdges) {

		//"choose a least cost edge (v, w) from E; 
		//delete (v, w) from E;" 
		//사실 edge는 1부터 시작이다.
		graphEdgeIndex++;

		//"if ( (v,w) does not create a cycle in T ) "를 의미한다. 
		//Before adding an edge (v, w), use the find operation to determine if v and w are in the same set (or tree) 
		//(v,w)가 cycle을 생성하는지의 여부는 find함수로 결정한다.
		if (find(nodes, edges[graphEdgeIndex].node1) != find(nodes, edges[graphEdgeIndex].node2)) {

			//"add (v, w) to T"를 의미한다.
			// If not in the same set, use the union operation to add into T, resulting an extended set.
			//spannedEdges에 지목하는 edges를 추가하고 그 edge에 대해서 union한다.
			spannedEdges[spannedEgdeIndex++]= graphEdgeIndex;
			_union(nodes, find(nodes, edges[graphEdgeIndex].node1),
				find(nodes, edges[graphEdgeIndex].node2));
		}
	}

	//"if ( T contains fewer than n-1 edges )"를 의미한다.
	//if문 안이 참이면 0, 아니면 1을 반환한다.
	if (spannedEdges[maximumSpannedEdges - 1] == -1)

		//"printf(“No spanning tree…\n”);"를 의미한다.
		//실질적으로 프린트가 되는 쪽은 main함수이다.
		return 0;

	return 1;
}

//Representation of Disjoint Sets을 이용한다.
//element가 root가 알고 싶은 node이다.
int find(int disjointSets[], int element) {
	int header = element;

	//만일 element의 parent가 root가 아니라면, 더 상위의 parent를 찾는다.
	//root가 나올 때까지 계속한다.
	while (disjointSets[header]!=-1) 
		header = disjointSets[header];
	
	return header;
}

//Representation of Disjoint Sets을 이용한다.
//두 node를 union하는 함수이다.
void _union(int disjointSets[], int rootHeader, int leafheader) {

	//만일 두 node가 root여야만 union이 가능하다.
	if (disjointSets[rootHeader] == -1 && disjointSets[leafheader] == -1)
		disjointSets[leafheader] = rootHeader;
	else
		printf("Error! you can union only roots!");

}

//주어진 배열a가 binary tree라고 가정하고 heap을 만들어주는 함수이다.
//heap은 weight를 기준으로 정렬된다.
void adjust(edge a[], int root, int n) { 

	int child, rootweight;
	edge temp; 
	temp = a[root]; 
	rootweight = a[root].weight;
	child = 2 * root;  //left child를 고려한다.

	while (child <= n) { 
		if ((child < n) && (a[child].weight < a[child + 1].weight)) //더 큰 걸 기준으로 삼는다.
			child++; 
		if (rootweight > a[child].weight) //만일 heap의 조건을 만족한다면
			break; //멈춘다.
		else {//아니면 child의 값을 parent에 넘긴다.
			a[child / 2].node1 = a[child].node1;  
			a[child / 2].node2 = a[child].node2;
			a[child / 2].weight = a[child].weight;
			child *= 2; 
		} 
	} 
	
	//root의 값을 child/2에 넘김
	a[child / 2].node1 = temp.node1; 
	a[child / 2].node2 = temp.node2;
	a[child / 2].weight = temp.weight;
}

void heapSort(edge a[], int n) { 
	// a[1:n]에 대한 heap sort 
	int i; 
	edge temp= a[0];
	for ( i=n/2; i>0; i-- ) adjust(a, i, n);//쭉 정렬해준다.

	//max를 뽑아서 맨 뒤로 정렬한다.
	for ( i = n-1; i>0; i-- ) { 
		temp = a[i + 1];
		a[i + 1] = a[1];
		a[1] = temp;
		adjust( a, 1, i ); 
	} 
}

//주어진 graph가 connected되었는지의 여부를 판단한다.
//disjoint set을 이용한다.
//root가 2개 이상 나오면 connected graph가 아니다.
int isConnected (edge edges[], int nodeNumber, int edgeNumber) {
	int* nodes = (int*)malloc(sizeof(int) * nodeNumber);
	int i;
	int headerNumber=0;

	for (i = 0; i < nodeNumber; i++) {
		nodes[i] = -1;
	}

	//모든 edges에 대해서 union한다.
	for (i = 1; i <= edgeNumber; i++) 
		if (find(nodes, edges[i].node1) != find(nodes, edges[i].node2))
			_union(nodes, find(nodes,edges[i].node1), find(nodes,edges[i].node2));
	
	//root의 갯수를 계산한다.
	for (i = 0; i < nodeNumber; i++)
		if (nodes[i] == -1) headerNumber++;

	//1개이면 true, 1이고
	if (headerNumber == 1)
		return 1;
	//2개 이상이면 false, 0을 출력한다.
	else if (headerNumber >= 2)
		return 0;
	else
	{
		printf("Error가 발생했습니다.");
		exit(-1);
	}
}