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
	ImageTable Matrix; //临接矩阵
	ArcCell vexs[MAX_SIZE]; //顶点表
	int vexnum,arcnum; //统计顶点和边(弧)的个数
	Status Tag; //图的种类 1,2,3,4分别对应无向图、无向网、有向图、有向网
}MGraph;

//以下链队列
typedef struct QNode
{
	ElemType data;
	struct QNode *next;
}QueueNode,*QueuePoint;

typedef struct
{
	int QueueSize;
	QueuePoint front;
	QueuePoint rear;
}QueueHead,*QueueHeadPoint;

QueueHeadPoint InitQueue()
{
	QueueHeadPoint Head=(QueueHeadPoint)malloc(sizeof(QueueHead));
	Head->QueueSize=0;
	Head->front=Head->rear=(QueuePoint)malloc(sizeof(QueueNode));
	Head->rear->next=NULL;
	return Head;
}

Status QueueEmpty(QueueHeadPoint Head)
{
	if(Head->front == Head->rear)
		return OK;
	return NO;
}

ElemType getFront(QueueHeadPoint *Head)
{
	if(QueueEmpty(*Head))
		return NULL;
	return (*Head)->front->next->data;
}

Status QueuePush(QueueHeadPoint *Head,ElemType data)
{
	QueuePoint p=(QueuePoint)malloc(sizeof(QueueNode));
	if(p==NULL)
	{
		printf("对不起，系统内存不足!入栈失败!\n");
		return NO;
	}
	p->data=data;
	p->next=(*Head)->rear->next;
	(*Head)->rear->next=p;
	(*Head)->rear=p;
	(*Head)->QueueSize++;
	return OK;
}

Status QueuePop(QueueHeadPoint *Head)
{
	QueuePoint p=(*Head)->front;
	if(QueueEmpty(*Head))
		return NO;
	(*Head)->front=p->next;
	(*Head)->QueueSize--;
	free(p);
	return OK;
}

Status QueueDelete(QueueHeadPoint *Head)
{
	while(!QueueEmpty(*Head))
		QueuePop(Head);
	free((*Head)->front);
	return OK;
}
//以上为链队列

Status CreatUDG(MGraph *Node)
{
	int i,j,v1,v2;
	
	Node->Tag=1;
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
			printf("输入数据超出矩阵能容纳的最大值!请重新输入\n");
			system("peuse");
		}
		else
		{
			Node->Matrix[v1][v2].Vertex=Node->Matrix[v2][v1].Vertex=1;
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

Status BFS(MGraph *Node,ElemType start)
{
	QueueHeadPoint Head=InitQueue();
	int flag[MAX_SIZE],now,i;
	QueuePush(&Head,start);
	for(i=0;i<MAX_SIZE;i++)
		flag[i]=0;
	printf("广度优先遍历:\n");
	printf("%d ",start);
	flag[start]=1;
	while(!QueueEmpty(Head))
	{
		now=getFront(&Head);
		QueuePop(&Head);
		
		for(i=0;i<MAX_SIZE;i++)
		{
			if(Node->Matrix[now][i].Vertex==1 && flag[i]==0)
			{
				printf("%d ",i);
				QueuePush(&Head,i);
				flag[i]=1;
			}
		}
	}
	printf("\n");
	QueueDelete(&Head);
	return OK;
}

int main()
{
	MGraph image;
	int i,j;
	CreatUDG(&image);
	/*  Output MGraph:
	
	for(i=0;i<6;i++)
		for(j=0;j<6;j++)
			printf("%d%c",image.Matrix[i][j].Vertex," \n"[j==5]);
			
	*/
	BFS(&image,0);
	return 0;
}

/**
input:
0 1
0 2
0 3
0 5
1 2
2 5
3 5
4 5
-1 -1
*/
