#define _CRT_SECURE_NO_WARNINGS
#define MaxVertex 10 //最大顶点数
#define MaxEdge 100 //最大边的数量
#include<stdio.h>
#include<stdlib.h>

//边，边的数据，起点终点权值
typedef struct {
	int from, to;
	int weight;
}EdgeType;

typedef struct {
	char vertex[MaxVertex];//顶点数组
	EdgeType edge[MaxEdge];//边集数组
	int VertexNum;//顶点数
	int EdgeNum;//边数
}Graph;

int parent[MaxVertex];//定义一个判断数组


void fineRoot(int parent[], int n);
Graph* createGraph();
int LocateVex(Graph* G, char point);
void krukaer(Graph* G);



Graph* createGraph() {
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->VertexNum = 6;
	G->EdgeNum = 9;
	for (int i = 0; i < MaxVertex; i++)
	{
		G->vertex[i] = '0' + i;
	}

	int fromNum[9] = { 1,2,0,2,3,4,0,3,0 };
	int toNum[9] = { 4,3,5,5,5,5,1,4,2 };
	int weightNum[9] = { 12,17,19,25,25,26,34,38,46 };
	for (int i = 0; i < G->EdgeNum; i++)
	{
		G->edge[i].from = fromNum[i];
	}

	for (int i = 0; i < G->EdgeNum; i++)
	{
		G->edge[i].to = toNum[i];
	}

	for (int i = 0; i < G->EdgeNum; i++)
	{
		G->edge[i].weight = weightNum[i];
	}

	return G;

}

int LocateVex(Graph* G, char point)//确定顶点point在图G（顶点数组）中的序号
{
	for (int i = 0; i < G->VertexNum; i++)
	{
		if (G->vertex[i] == point) return i;
	}
}

void krukaer(Graph* G) { 

	int n = 0;
	for (int i = 0; i < MaxVertex; i++)//初始化数组
	{
		parent[i] = -1;
	}
	for (int i = 0; i < G->EdgeNum; i++)
	{
		int vex1 = findRoot(parent, G->edge[i].from);
		int vex2 = findRoot(parent, G->edge[i].to);
		if (vex1!=vex2)
		{
			parent[vex2] = vex1;
			if (++n == (G->VertexNum - 1)) break;
		}
		
	}



}

int findRoot(int parent[], int n) {
	while (1)
	{
		if (parent[n] == -1) {
			return n;
		}
		else
		{
			n = parent[n];
		}
	}
	return n;
}

void main()
{
	Graph* G = createGraph();
	printf("Edge\tfrom\tto\tweight\n");
	for (int i = 0; i < G->EdgeNum; i++)
	{
		printf("%d\t%d\t%d\t%d\n",i,G->edge[i].from,
			G->edge[i].to,G->edge[i].weight);
	}
	krukaer(G);
	for (int i = 0; i < G->VertexNum; i++)
	{
		printf("%d\t", parent[i]);
	}


	/*int a[6] = { 2,-1,-1,2,1,0 };
	int root=findRoot(a, 5);
	printf("%d", root);*/



	system("pause");


}