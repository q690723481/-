#include"graph.h"

int s[MAX_VERTEX_NUM];//�����Ѿ�����s�ĺ�δ����s�Ķ���
int dist[MAX_VERTEX_NUM];//�͸õ������Ļ�
int path[MAX_VERTEX_NUM];//���·��


int LocateVex(MGraph* G, Elemtype point);//ȷ������point��ͼG���������飩�е����
void PrintGraph(MGraph* G);//��ӡ��Ӿ���
int findMinNum(int test0[MAX_VERTEX_NUM]);//�ҵ���С���ֵ��±�
int locateNum(int test0[MAX_VERTEX_NUM], int num);//��λ��С�����������е�λ��

void initializeGraph(MGraph* G);//��ʼ����Ӿ���
void Dijkstra(MGraph* G, int startVex);//ʹ�õϽ�˹�����㷨
void showPath();//����path�����ӡ��ȫ��·��
void showOnePath(int n);





void Dijkstra(MGraph* G,int startVex) {
	int n = startVex;
	for (int i = 0; i < G->vexnum; i++)//����ѭ�����ǣ�path�����ʼ��Ϊ0
	{
		s[i] = 0;
		path[i] = 0;
	}
	for (int j = 0; j < G->vexnum; j++)
	{
		dist[j] = G->arcs[n][j].adj;//����Ӿ���ĵ�n��ת�Ƶ�dist��
	}


	for (int i = 0; i < MAX_VERTEX_NUM-1; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)  //�õ�dist����
		{
			if ((G->arcs[n][j].adj) + dist[n] < dist[j])
			{
				dist[j] = (G->arcs[n][j].adj) + dist[n];
				path[j] = n;
			}
		}

		s[n] = 1;
		int test[MAX_VERTEX_NUM] = { 0 };
		for (int m = 0; m < MAX_VERTEX_NUM; m++)  //�õ�s����
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
	//��ʼ��ͼ���ڽӾ���
	G->vexnum = MAX_VERTEX_NUM;
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			G->arcs[i][j].adj = test[i][j];
		}
	}
	//��ʼ����������
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
	initializeGraph(G);//��ʼ�����飬�Ƴ����ӵ��������ݹ���
	
	//PrintGraph(G);//��ӡ�ڽӾ���
	Dijkstra(G, 0);//����Dijkstra�㷨
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