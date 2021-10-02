#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define MAX_SIZE 20
#define OK 1
#define NO 0
#define INF 0x3f3f3f3f

typedef int Status;
typedef int ElemType;
typedef char InfoType;

typedef struct
{
	InfoType *info;
	ElemType Vertex;
}ArcCell,ImageTable[MAX_SIZE][MAX_SIZE];

typedef struct
{
	ImageTable Matrix; //�ٽӾ���
	ArcCell vexs[MAX_SIZE]; //�����
	int vexnum,arcnum; //ͳ�ƶ���ͱ�(��)�ĸ���
	Status Tag; //ͼ������ 1,2,3,4�ֱ��Ӧ����ͼ��������������ͼ��������
}MGraph;

Status CreatUDG(MGraph *Node)
{
	int i,j,v1,v2;

	Node->Tag=3;
	Node->arcnum=Node->vexnum=0;

	for(i=0;i<MAX_SIZE;i++)
	{
		Node->vexs[i].Vertex=0;
		for(j=0;j<MAX_SIZE;j++)
			Node->Matrix[i][j].Vertex=0;
	}

	while(scanf("%d%d",&v1,&v2)!=EOF && v1>=0 && v2>=0)
	{
		if(v1>=MAX_SIZE || v2>=MAX_SIZE)
		{
			printf("�������ݳ������������ɵ����ֵ!����������\n");
			system("peuse");
		}
		else
		{
			Node->Matrix[v1][v2].Vertex=1;
			if(Node->vexs[v1].Vertex==0 && Node->vexs[v2].Vertex==0)
			{
				Node->vexs[v1].Vertex=Node->vexs[v2].Vertex=1;
				Node->vexnum+=2;
			}
			else if(Node->vexs[v1].Vertex==0)
			{
				Node->vexs[v1].Vertex=1;
 				Node->vexnum++;
			}
			else if(Node->vexs[v2].Vertex==0)
			{
				Node->vexs[v2].Vertex=1;
				Node->vexnum++;
			}
			else
				continue;
			Node->arcnum++;
		}
	}
	return OK;
}

Status DFS(MGraph *Node,ElemType start,int *flag)
{
	int i;
	flag[start]=1;
	printf("%d ",start);
	for(i=0;i<MAX_SIZE;i++)
	{
		if(Node->Matrix[start][i].Vertex==1 && flag[i]==0)
			DFS(Node,i,flag);
	}
	return OK;
}

int main()
{
	MGraph image;
	int i,j;
	int flag[MAX_SIZE];
	for(i=0;i<MAX_SIZE;i++)
		flag[i]=0;
	CreatUDG(&image);
	/*  Output MGraph:

	for(i=0;i<6;i++)
		for(j=0;j<6;j++)
			printf("%d%c",image.Matrix[i][j].Vertex," \n"[j==5]);

	*/
	printf("������ȱ���:\n");
	for(i=0;i<MAX_SIZE;i++)
	{
		if(flag[i]==0 && image.vexs[i].Vertex==1)
			DFS(&image,i,flag);
	}
	printf("\n");
	return 0;
}

/**
input:

*/

