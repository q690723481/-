#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define INFINITY 65535
#define MAX_VERTEX_NUM 7
#define ERROR -1
#include<stdio.h>
#include<stdlib.h>

typedef enum { DG, DN, UDG, UDN }GraphKind;//����ͼ��������������ͼ��������
typedef int VRType;//VR��ʾ��������Ĺ�ϵ��1/0��ʾΪͼ����Ϊ��ȨͼΪȨ������
typedef char Elemtype;//���嶥�������
typedef struct ArcCell
{
	VRType adj; //1/0��ʾΪͼ����Ϊ��ȨͼΪȨ��ֵ
	char* info; //�û������Ϣ��ָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	Elemtype vexs[MAX_VERTEX_NUM];//���������
	AdjMatrix arcs;               //��Ӿ���
	int vexnum, arcnum;           //ͼ�Ķ������ͻ���
	GraphKind kind;               //ͼ������
}MGraph;

//����Ϊ��Ҫ�õ��ĺ���
void CreateGraph(MGraph* G);//ѡ��ͼ������������һ��ͼ
int LocateVex(MGraph* G, Elemtype point);//ȷ������point��ͼG���������飩�е����
void CreateUDG(MGraph* G);//��������ͼ
void CreateUDN(MGraph* G);//����������
void CreateDG(MGraph* G);//��������ͼ
void CreateDN(MGraph* G);//����������
void PrintGraph(MGraph* G);//��ӡ��Ӿ���


void CreateGraph(MGraph* G)//ѡ��ͼ������������һ��ͼ
{
	int kind;
	printf("������ͼ�����Ͷ�Ӧ�����(0.����ͼ/1.������/2.����ͼ/3.������)��");
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

int LocateVex(MGraph* G, Elemtype point)//ȷ������point��ͼG���������飩�е����
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

void CreateUDG(MGraph* G)//��������ͼ
{
	Elemtype origin, terminus;//�ߵ���㣬�յ�
	printf("������ͼ�Ķ�������������");
	scanf(" %d  %d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("�������%d�����㣺", i + 1);
		scanf(" %c", &(G->vexs[i]));//�洢�����ֵ
	}

	for (int i = 0; i < G->vexnum; i++)//��ʼ����Ӿ���
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = 0;
		}
	}
	for (int k = 0; k < G->arcnum; k++)
	{
		printf("����һ�������������㣺");
		scanf(" %c  %c", &origin, &terminus);
		int i = LocateVex(G, origin);//�ڶ�����������ҵ������յ��λ��
		int j = LocateVex(G, terminus);
		G->arcs[i][j].adj = 1;
		G->arcs[j][i].adj = 1;
	}
	printf("��������ͼ�ɹ�\n");

}

void CreateUDN(MGraph* G)//����������
{
	int weight;                   //�ߵ�Ȩֵ
	Elemtype origin, terminus;    //��������յ�
	printf("�����붥�����뻡����");
	scanf(" %d  %d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i < G->vexnum; i++)
	{
		printf("�����붥��ֵ��");
		scanf(" %c", &(G->vexs[i]));
	}

	for (int i = 0; i < G->vexnum; i++)//��ʼ����Ӿ���
	{
		for (int j = 0; j < G->arcnum; j++)
		{
			G->arcs[i][j].adj = 0;
		}
	}

	for (int k = 0; k < G->arcnum; k++)
	{
		printf("����������û�����㣬�յ㣬Ȩֵ");
		scanf(" %c  %c  %d", &origin, &terminus, &weight);
		int i = LocateVex(G, origin);
		int j = LocateVex(G, terminus);
		G->arcs[i][j].adj = weight;
		G->arcs[j][i].adj = weight;
	}
	printf("�����������ɹ�\n");

}

void CreateDG(MGraph* G)//����ͼ
{
	int origin, terminus;
	printf("����ͼ�Ķ�����������:\n");
	scanf(" %d %d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i < G->vexnum; i++)    //���㸳ֵ
	{
		printf("���붥��ֵ��");
		scanf(" %c", &(G->vexs[i]));
	}

	for (int i = 0; i < G->vexnum; i++)    //��ʼ���ڽӾ���
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = 0;
		}
	}

	for (int k = 0; k < G->arcnum; k++)
	{
		printf("����һ���ߵ�����յ�");
		scanf(" %c  %c", &origin, &terminus);
		int i = LocateVex(G, origin);
		int j = LocateVex(G, terminus);
		G->arcs[i][j].adj = 1;
	}
	printf("�����ɹ�\n");
}


void CreateDN(MGraph* G)		//������
{
	int origin, terminus, weight; 	//�ߵ����,�յ�,Ȩֵ
	printf("����ͼ�Ķ����� ����");
	scanf(" %d  %d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i < G->vexnum; i++)	//������ֵ�洢��ȥ
	{
		printf("���붥��ֵ��");
		scanf(" %c", &(G->vexs[i]));
	}

	for (int i = 0; i < G->vexnum; i++)	//��ʼ���ڽӾ���
		for (int j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = INFINITY;
		}
	for (int k = 0; k < G->arcnum; k++)
	{
		printf("����һ���ߵ���㡢�յ��Լ�Ȩֵ");
		scanf( "%c %c %d", &origin, &terminus, &weight);
		int i = LocateVex(G, origin);
		int j = LocateVex(G, terminus);
		G->arcs[i][j].adj = weight;
	}
	printf("�����ɹ�\n");
}

void PrintGraph(MGraph* G)//��ӡ��Ӿ���
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









