#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define INFINITY 65535
#define MAX_VERTEX_NUM 7
#define ERROR -1
#include<stdio.h>
#include<stdlib.h>

typedef enum { DG, DN, UDG, UDN }GraphKind;//有向图，有向网，无向图，无向网
typedef int VRType;//VR表示两个顶点的关系，1/0表示为图，若为带权图为权的类型
typedef char Elemtype;//定义顶点的类型
typedef struct ArcCell
{
	VRType adj; //1/0表示为图，若为带权图为权的值
	char* info; //该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	Elemtype vexs[MAX_VERTEX_NUM];//顶点的数组
	AdjMatrix arcs;               //领接矩阵
	int vexnum, arcnum;           //图的顶点数和弧数
	GraphKind kind;               //图的类型
}MGraph;

//下面为需要用到的函数
void CreateGraph(MGraph* G);//选择图的类型来创建一个图
int LocateVex(MGraph* G, Elemtype point);//确定顶点point在图G（顶点数组）中的序号
void CreateUDG(MGraph* G);//创建无向图
void CreateUDN(MGraph* G);//创建无向网
void CreateDG(MGraph* G);//创建有向图
void CreateDN(MGraph* G);//创建有向网
void PrintGraph(MGraph* G);//打印领接矩阵


void CreateGraph(MGraph* G)//选择图的类型来创建一个图
{
	int kind;
	printf("请输入图的类型对应的序号(0.有向图/1.有向网/2.无向图/3.无向网)：");
	scanf(" %d", &kind);
	switch (kind)
	{
	case 0:CreateDG(G); break;
	case 1:CreateDN(G); break;
	case 2:CreateUDG(G); break;
	case 3:CreateUDN(G); break;
	default: return;
	}
}

int LocateVex(MGraph* G, Elemtype point)//确定顶点point在图G（顶点数组）中的序号
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (G->vexs[i] == point) return i;
		else
		{
			return -1;
		}
	}
	
}

void CreateUDG(MGraph* G)//创建无向图
{
	Elemtype origin, terminus;//边的起点，终点
	printf("请输入图的顶点数，弧数：");
	scanf(" %d  %d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("请输入第%d个顶点：", i + 1);
		scanf(" %c", &(G->vexs[i]));//存储顶点的值
	}

	for (int i = 0; i < G->vexnum; i++)//初始化领接矩阵
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = 0;
		}
	}
	for (int k = 0; k < G->arcnum; k++)
	{
		printf("输入一条弧的两个顶点：");
		scanf(" %c  %c", &origin, &terminus);
		int i = LocateVex(G, origin);//在顶点的数组中找到起点和终点的位置
		int j = LocateVex(G, terminus);
		G->arcs[i][j].adj = 1;
		G->arcs[j][i].adj = 1;
	}
	printf("创建无向图成功\n");

}

void CreateUDN(MGraph* G)//创建无向网
{
	int weight;                   //边的权值
	Elemtype origin, terminus;    //弧的起点终点
	printf("请输入顶点数与弧数：");
	scanf(" %d  %d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("请输入顶点值：");
		scanf(" %c", &(G->vexs[i]));
	}

	for (int i = 0; i < G->vexnum; i++)//初始化领接矩阵
	{
		for (int j = 0; j < G->arcnum; j++)
		{
			G->arcs[i][j].adj = 0;
		}
	}

	for (int k = 0; k < G->arcnum; k++)
	{
		printf("请依次输入该弧的起点，终点，权值");
		scanf(" %c  %c  %d", &origin, &terminus, &weight);
		int i = LocateVex(G, origin);
		int j = LocateVex(G, terminus);
		G->arcs[i][j].adj = weight;
		G->arcs[j][i].adj = weight;
	}
	printf("创建无向网成功\n");

}

void CreateDG(MGraph* G)//有向图
{
	int origin, terminus;
	printf("输入图的顶点数，弧数:\n");
	scanf(" %d %d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i < G->vexnum; i++)    //顶点赋值
	{
		printf("输入顶点值：");
		scanf(" %c", &(G->vexs[i]));
	}

	for (int i = 0; i < G->vexnum; i++)    //初始化邻接矩阵
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = 0;
		}
	}

	for (int k = 0; k < G->arcnum; k++)
	{
		printf("输入一条边的起点终点");
		scanf(" %c  %c", &origin, &terminus);
		int i = LocateVex(G, origin);
		int j = LocateVex(G, terminus);
		G->arcs[i][j].adj = 1;
	}
	printf("创建成功\n");
}


void CreateDN(MGraph* G)		//有向网
{
	int origin, terminus, weight; 	//边的起点,终点,权值
	printf("输入图的顶点数 弧数");
	scanf(" %d  %d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i < G->vexnum; i++)	//将顶点值存储进去
	{
		printf("输入顶点值：");
		scanf(" %c", &(G->vexs[i]));
	}

	for (int i = 0; i < G->vexnum; i++)	//初始化邻接矩阵
		for (int j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = INFINITY;
		}
	for (int k = 0; k < G->arcnum; k++)
	{
		printf("输入一条边的起点、终点以及权值");
		scanf( "%c %c %d", &origin, &terminus, &weight);
		int i = LocateVex(G, origin);
		int j = LocateVex(G, terminus);
		G->arcs[i][j].adj = weight;
	}
	printf("创建成功\n");
}

void PrintGraph(MGraph* G)//打印领接矩阵
{
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			printf("%d\t", G->arcs[i][j].adj);
		}
		printf("\n");
	}
}









