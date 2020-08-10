#include"graph.h"

int s[MAX_VERTEX_NUM];//定义已经纳入s的和未纳入s的顶点
int dist[MAX_VERTEX_NUM];//和该点项链的弧
int path[MAX_VERTEX_NUM];//最短路径


int LocateVex(MGraph* G, Elemtype point);//确定顶点point在图G（顶点数组）中的序号
void PrintGraph(MGraph* G);//打印领接矩阵
int findMinNum(int test0[MAX_VERTEX_NUM]);//找到最小数字的下表
int locateNum(int test0[MAX_VERTEX_NUM], int num);//定位最小数字在数组中的位置

void initializeGraph(MGraph* G);//初始化领接矩阵
void Dijkstra(MGraph* G, int startVex);//使用迪杰斯特拉算法
void showPath();//根据path数组打印出全部路径
void showOnePath(int n);





void Dijkstra(MGraph* G,int startVex) {
	int n = startVex;
	for (int i = 0; i < G->vexnum; i++)//利用循环把是，path数组初始化为0
	{
		s[i] = 0;
		path[i] = 0;
	}
	for (int j = 0; j < G->vexnum; j++)
	{
		dist[j] = G->arcs[n][j].adj;//把领接矩阵的第n行转移到dist中
	}


	for (int i = 0; i < MAX_VERTEX_NUM-1; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)  //得到dist数组
		{
			if ((G->arcs[n][j].adj) + dist[n] < dist[j])
			{
				dist[j] = (G->arcs[n][j].adj) + dist[n];
				path[j] = n;
			}
		}

		s[n] = 1;
		int test[MAX_VERTEX_NUM] = { 0 };
		for (int m = 0; m < MAX_VERTEX_NUM; m++)  //得到s数组
		{
			if (s[m] == 1);
			else
			{
				test[m] = dist[m];
			}
		}
		
		n = findMinNum(test);
	}


}

int locateNum(int test0[MAX_VERTEX_NUM], int num) {
	int test[MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		test[i] = test0[i];
		if (test[i]==num)
		{
			return i;
		}
	}
	return -1;
}

int findMinNum(int test0[MAX_VERTEX_NUM]) {
	int test[MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM ; i++)
	{
		test[i] = test0[i];
		if (test[i]==0)
		{
			test[i] = INFINITY;
		}
	}

	int min = test[0];
	int k = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		if (min>test[i])
		{
			min = test[i];
		}
	}
	return locateNum(test, min);

}

void initializeGraph(MGraph* G) {
	int test[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {
		0,4,6,6,INFINITY,INFINITY,INFINITY,
		INFINITY,0,1,INFINITY,7,INFINITY,INFINITY,
		INFINITY,INFINITY,0,INFINITY,6,4,INFINITY,
		INFINITY,INFINITY,2,0,INFINITY,5,INFINITY,
		INFINITY,INFINITY,INFINITY,INFINITY,0,INFINITY,6,
		INFINITY,INFINITY,INFINITY,INFINITY,1,0,8,
		INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,0
	};
	//初始化图的邻接矩阵
	G->vexnum = MAX_VERTEX_NUM;
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			G->arcs[i][j].adj = test[i][j];
		}
	}
	//初始化顶点数组
	for (int i = 0; i < G->vexnum; i++)
	{
		G->vexs[i] = '0' + i;
	}
}

void showPath() {
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		printf("%d<-", i);
		showOnePath(i);
		printf("\n");
	}

}

void showOnePath(int n) {
	if (path[n] == 0){
		printf("%d", path[n]);
		return;
	}
	else {
		printf("%d<-", path[n]);
		showOnePath(path[n]);
	}

}

void main() {
	MGraph* G = (MGraph*)malloc(sizeof(MGraph));
	initializeGraph(G);//初始化数组，移除复杂的输入数据过程
	
	//PrintGraph(G);//打印邻接矩阵
	Dijkstra(G, 0);//运行Dijkstra算法
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		printf("%d\t", dist[i]);
	}
	printf("\n");
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		printf("%d\t", path[i]);
	}
	printf("\n");
	showPath();
	
}