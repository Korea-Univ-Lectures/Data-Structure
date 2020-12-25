//�� ���α׷��� heap sort�� �̿��Ͽ� edge�� �����Ѵ�.
#include <stdio.h>
#include <stdlib.h>

//edge ����ü�� �����Ѵ�.
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
	int nodeNumber;//����ڰ� �Է��ϴ� node�� �����̴�.
	int edgeNumber;//����ڰ� �Է��ϴ� edge�� �����̴�.
	int i;
	int hasSpanTree; //����ڰ� �Է��� Graph���� spannedTree�� ���� �� �ִ� �� �Ǵ��Ѵ�.
	
	//����ڷκ��� node�� ������ �Է¹޴´�.
	printf("Node�� � ����ðڽ��ϱ�? (Node�� 1�� �̻��̾�� �մϴ�.): ");
	scanf("%d",&nodeNumber);

	if (nodeNumber <= 0){
		printf("Node�� 1�� �̻��̾�� �մϴ�!\n");
		return 1;
	}

	//������� ��带 ������ݴϴ�.
	for (i = 0; i < nodeNumber; i++) {
		if (i == 0)
			printf("Node 0");
		else
			printf(", %d", i);
	}
	printf("�� ����� �����ϴ�.\n");

	//����ڷκ��� ���� edge�� ������ �Է¹޴´�.
	printf("Edge�� � ����ðڽ��ϱ�? (Edge�� 0�� �̻��̾�� �մϴ�.): ");
	scanf("%d", &edgeNumber);

	if (edgeNumber < 0) {
		printf("Edge�� 0�� �̻��̾�� �մϴ�!\n");
		return 1;
	}

	//edge�� �迭�� �ʱ�ȭ��Ų��.
	edge* graphEdges = (edge*)malloc(sizeof(edge) * (edgeNumber + 1));
	for (i = 0; i <= edgeNumber; i++)
		graphEdges[i].weight = -1;

	int* spannedGraphNodes = (int*)malloc(sizeof(int) * nodeNumber);
	int* spannedGraphEdges = (int*)malloc(sizeof(int) * (nodeNumber - 1));

	for (i = 1; i < edgeNumber+1; i++) {
		printf("%d��° edge (node1/node2/weight): ", i);
		scanf("%d/%d/%d", &graphEdges[i].node1, &graphEdges[i].node2, &graphEdges[i].weight);

		//edge�� �̹� ������� Node���� �̿��ؼ��� ������ �Ѵ�.
		if (graphEdges[i].node1 >= nodeNumber || graphEdges[i].node2 >= nodeNumber
			|| graphEdges[i].node1 < 0 || graphEdges[i].node2 < 0) {
			printf("�����ϴ� Node�鸸�� �Է��Ͽ� �ֽʽÿ�");

			free(spannedGraphEdges);
			free(spannedGraphNodes);
			free(graphEdges);
			return 1;
		}

		//edge�� �̾��ִ� Node���� ascent�ϰ� �迭�Ѵ�.
		//�̴� �ߺ��Ǵ� edge�� �ɷ����� �����̴�.
		if (graphEdges[i].node1 > graphEdges[i].node2) {
			int temp = graphEdges[i].node2;
			graphEdges[i].node2 = graphEdges[i].node1;
			graphEdges[i].node1 = temp;
		}

		//����, ���� Vertex�� �� Vertex�� �����ϴٸ�, self edge�̹Ƿ�, ���ܽ��Ѿ� �Ѵ�.
		if (graphEdges[i].node1 == graphEdges[i].node2) {
			printf("self edge�� ������� �ʽ��ϴ�.");

			free(spannedGraphEdges);
			free(spannedGraphNodes);
			free(graphEdges);
			return 1;
		}

		//�ߺ��Ǵ� edge�� �ִ��� �˻��Ѵ�.
		int j;
		for (j = 1; j < i; j++)
		{
			if ((graphEdges[j].node1 == graphEdges[i].node1) && (graphEdges[j].node2 == graphEdges[i].node2))
			{
				printf("�ߺ��Ǵ� edge�� ������� �ʽ��ϴ�.");

				free(spannedGraphEdges);
				free(spannedGraphNodes);
				free(graphEdges);
				return 1;
			}
		}

		//�Էµ� edge�� weight�� non-negative�� ���̴�.
		if (graphEdges[i].weight < 0) {
			printf("weight�� ������ �ƴ� ������ �մϴ�.");

			free(spannedGraphEdges);
			free(spannedGraphNodes);
			free(graphEdges);
			return 1;
		}
			
	}


	//����ڷκ��� ��� edge�� ���� ������, ����ڰ� �Է��� Graph�� Connected �Ǿ����� �Ǵ��Ѵ�.
	//Kruskal's Algorithm�� ���� Spanning Tree�� ����� �˰����� graph�� connected�Ǿ��ִٴ� ������ �ִ�.
	int hasConnectedGraph = isConnected(graphEdges, nodeNumber, edgeNumber);
	if (!hasConnectedGraph) {
		printf("Graph�� Connected���� �ʾҽ��ϴ�.");

		free(spannedGraphEdges);
		free(spannedGraphNodes);
		free(graphEdges);
		return 1;
	}

	printf("\n");

	//spanned�� graph�� Node���� �ʱ�ȭ ���ݴϴ�.
	//spannedGraphNodes���� �ڽ��� parent�� index�� ���ϴ�.
	//-1�� �� node�� root��� ���� �ǹ��մϴ�.
	for (i = 0; i < nodeNumber; i++) {
		spannedGraphNodes[i] = -1;
	}

	//spanned�� graph�� Edge���� �ʱ�ȭ ���ݴϴ�.
	for (i = 0; i < nodeNumber-1; i++) {
		spannedGraphEdges[i] = -1;
	}

	//�� ù��° Edge�� �ʱ�ȭ (graphEdges[0]�� ���� �������� ����.)
	graphEdges[0].node1 = -1; graphEdges[0].node2 = -1; graphEdges[0].weight = -1;

	//graphEdges�� weigth�� ���������� ������������ ����
	heapSort(graphEdges, edgeNumber);

	//spanned tree�� �ִ����� ���θ� Ȯ��
	hasSpanTree = KRUSKALSALGORITHM(graphEdges, spannedGraphEdges,
		edgeNumber, nodeNumber-1, spannedGraphNodes);

	//spanned tree�� ������ ���õ� edge���� ����Ѵ�.
	//������ ���ٰ� ����Ѵ�.
	if (hasSpanTree) {
		printf("Spanned Tree�� edges�� ������ �����ϴ�. \n");
		printf("(Node1, Node2)->weight\n");
		for (i = 0; i < nodeNumber - 1; i++)
			printf("(%d, %d)->%d\n", graphEdges[spannedGraphEdges[i]].node1, graphEdges[spannedGraphEdges[i]].node2, graphEdges[spannedGraphEdges[i]].weight);
	}
	else
		printf("No spanning tre...\n");

	//�޸𸮸� ��ü���ְ� ����
	free(spannedGraphEdges);
	free(spannedGraphNodes);
	free(graphEdges);
	return 0;
}

//�������� �䱸�ϴ� Kruskal`s Algorithm
//edges�� ����ڰ� �Է��� ���ĵ� edge��, spannedEdges�� spanned tree�� �ʿ��� edge���� index�����̴�.
//maximumEdges�� edges�� edge ���� maximumSpannedEdges�� spannedEdges�� edge �����̴�.
//nodes�� ����ڰ� �Է��� node�� �ǹ��Ѵ�. -> ���⼭�� node���� Set Representation by Trees���� �����Ѵ�.
int KRUSKALSALGORITHM(edge edges[], int spannedEdges[], 
	int maximumEdges, int maximumSpannedEdges, int nodes[]) {

	int graphEdgeIndex = 0;//edges�� index�� �ǹ��Ѵ�.
	int spannedEgdeIndex = 0;//spannedEdges�� index�� �ǹ��Ѵ�. -> "T= {};"�� �ǹ��Ѵ�.

	//"while ( T contains less than n-1 edges && E is not empty )"�� �ǹ��Ѵ�.
	//spannedEdges�� n-1���� �ǰų�, edges�� �� �̻� �����ִ� edge�� ���� ������ ��� while loop�� ������.
	while (spannedEdges[maximumSpannedEdges - 1] == -1 && graphEdgeIndex < maximumEdges) {

		//"choose a least cost edge (v, w) from E; 
		//delete (v, w) from E;" 
		//��� edge�� 1���� �����̴�.
		graphEdgeIndex++;

		//"if ( (v,w) does not create a cycle in T ) "�� �ǹ��Ѵ�. 
		//Before adding an edge (v, w), use the find operation to determine if v and w are in the same set (or tree) 
		//(v,w)�� cycle�� �����ϴ����� ���δ� find�Լ��� �����Ѵ�.
		if (find(nodes, edges[graphEdgeIndex].node1) != find(nodes, edges[graphEdgeIndex].node2)) {

			//"add (v, w) to T"�� �ǹ��Ѵ�.
			// If not in the same set, use the union operation to add into T, resulting an extended set.
			//spannedEdges�� �����ϴ� edges�� �߰��ϰ� �� edge�� ���ؼ� union�Ѵ�.
			spannedEdges[spannedEgdeIndex++]= graphEdgeIndex;
			_union(nodes, find(nodes, edges[graphEdgeIndex].node1),
				find(nodes, edges[graphEdgeIndex].node2));
		}
	}

	//"if ( T contains fewer than n-1 edges )"�� �ǹ��Ѵ�.
	//if�� ���� ���̸� 0, �ƴϸ� 1�� ��ȯ�Ѵ�.
	if (spannedEdges[maximumSpannedEdges - 1] == -1)

		//"printf(��No spanning tree��\n��);"�� �ǹ��Ѵ�.
		//���������� ����Ʈ�� �Ǵ� ���� main�Լ��̴�.
		return 0;

	return 1;
}

//Representation of Disjoint Sets�� �̿��Ѵ�.
//element�� root�� �˰� ���� node�̴�.
int find(int disjointSets[], int element) {
	int header = element;

	//���� element�� parent�� root�� �ƴ϶��, �� ������ parent�� ã�´�.
	//root�� ���� ������ ����Ѵ�.
	while (disjointSets[header]!=-1) 
		header = disjointSets[header];
	
	return header;
}

//Representation of Disjoint Sets�� �̿��Ѵ�.
//�� node�� union�ϴ� �Լ��̴�.
void _union(int disjointSets[], int rootHeader, int leafheader) {

	//���� �� node�� root���߸� union�� �����ϴ�.
	if (disjointSets[rootHeader] == -1 && disjointSets[leafheader] == -1)
		disjointSets[leafheader] = rootHeader;
	else
		printf("Error! you can union only roots!");

}

//�־��� �迭a�� binary tree��� �����ϰ� heap�� ������ִ� �Լ��̴�.
//heap�� weight�� �������� ���ĵȴ�.
void adjust(edge a[], int root, int n) { 

	int child, rootweight;
	edge temp; 
	temp = a[root]; 
	rootweight = a[root].weight;
	child = 2 * root;  //left child�� ����Ѵ�.

	while (child <= n) { 
		if ((child < n) && (a[child].weight < a[child + 1].weight)) //�� ū �� �������� ��´�.
			child++; 
		if (rootweight > a[child].weight) //���� heap�� ������ �����Ѵٸ�
			break; //�����.
		else {//�ƴϸ� child�� ���� parent�� �ѱ��.
			a[child / 2].node1 = a[child].node1;  
			a[child / 2].node2 = a[child].node2;
			a[child / 2].weight = a[child].weight;
			child *= 2; 
		} 
	} 
	
	//root�� ���� child/2�� �ѱ�
	a[child / 2].node1 = temp.node1; 
	a[child / 2].node2 = temp.node2;
	a[child / 2].weight = temp.weight;
}

void heapSort(edge a[], int n) { 
	// a[1:n]�� ���� heap sort 
	int i; 
	edge temp= a[0];
	for ( i=n/2; i>0; i-- ) adjust(a, i, n);//�� �������ش�.

	//max�� �̾Ƽ� �� �ڷ� �����Ѵ�.
	for ( i = n-1; i>0; i-- ) { 
		temp = a[i + 1];
		a[i + 1] = a[1];
		a[1] = temp;
		adjust( a, 1, i ); 
	} 
}

//�־��� graph�� connected�Ǿ������� ���θ� �Ǵ��Ѵ�.
//disjoint set�� �̿��Ѵ�.
//root�� 2�� �̻� ������ connected graph�� �ƴϴ�.
int isConnected (edge edges[], int nodeNumber, int edgeNumber) {
	int* nodes = (int*)malloc(sizeof(int) * nodeNumber);
	int i;
	int headerNumber=0;

	for (i = 0; i < nodeNumber; i++) {
		nodes[i] = -1;
	}

	//��� edges�� ���ؼ� union�Ѵ�.
	for (i = 1; i <= edgeNumber; i++) 
		if (find(nodes, edges[i].node1) != find(nodes, edges[i].node2))
			_union(nodes, find(nodes,edges[i].node1), find(nodes,edges[i].node2));
	
	//root�� ������ ����Ѵ�.
	for (i = 0; i < nodeNumber; i++)
		if (nodes[i] == -1) headerNumber++;

	//1���̸� true, 1�̰�
	if (headerNumber == 1)
		return 1;
	//2�� �̻��̸� false, 0�� ����Ѵ�.
	else if (headerNumber >= 2)
		return 0;
	else
	{
		printf("Error�� �߻��߽��ϴ�.");
		exit(-1);
	}
}