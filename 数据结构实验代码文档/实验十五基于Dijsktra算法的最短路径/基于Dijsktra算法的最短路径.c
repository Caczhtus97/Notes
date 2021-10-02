#include<stdio.h>
#include<stdlib.h>

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
}ArcCell,*ImageTable;

typedef struct
{
	ImageTable *Matrix; //�ٽӾ���
	ArcCell vexs[MAX_SIZE]; //�����
	int vexnum,arcnum; //ͳ�ƶ���ͱ�(��)�ĸ���
	Status Tag; //ͼ������ 1,2,3,4�ֱ��Ӧ����ͼ��������������ͼ��������
}MGraph;

Status InitMatrix(MGraph *Node)
{
	int i;
	Node->Matrix=(ImageTable *)malloc(Node->vexnum*sizeof(ImageTable));
	for(i=0;i<Node->vexnum;i++)
	{
		Node->Matrix[i]=(ImageTable)malloc(Node->vexnum*sizeof(ArcCell));
		if(Node->Matrix[i]==NULL)
			return NO;
	}
	return OK;
}

Status CreatGraph(MGraph *Node)
{
	int i,j,w;
	int v1,v2;

	for(i=0;i<Node->vexnum;i++)
	{
		for(j=0;j<Node->vexnum;j++)
			Node->Matrix[i][j].Vertex=INF;
	}

	printf("����%d������i,j��w:\n",Node->arcnum);
	for(i=0;i<Node->arcnum;i++)
	{
		getchar();
		scanf("%d,%d,%d",&v1,&v2,&w);
		Node->Matrix[v1-1][v2-1].Vertex=w;
	}

	printf("\n���ٽӾ�����:\n");
	for(i=0;i<Node->vexnum;i++)
	{
		for(j=0;j<Node->vexnum;j++)
			if(Node->Matrix[i][j].Vertex==INF)
				printf("��%c"," \n"[j+1==Node->vexnum]);
			else
				printf("%2d%c",Node->Matrix[i][j].Vertex," \n"[j+1==Node->vexnum]);
	}

	return OK;
}

void dijkstra(MGraph *Node,int start)
{
	int i,v,u;
	int *vis=(int *)malloc(Node->vexnum*sizeof(int));
	int *mincost=(int *)malloc(Node->vexnum*sizeof(int));
	int *previs=(int *)malloc(Node->vexnum*sizeof(int));

	for(i=0;i<Node->vexnum;i++)
	{
		vis[i]=0;
		mincost[i]=Node->Matrix[start-1][i].Vertex;
		previs[i]=start-1;
	}

	vis[start-1]=1;
	mincost[start-1]=0;
	
	for(i=2;i<=Node->vexnum;i++)
	{
		v=-1;
		for(u=0;u<Node->vexnum;u++)
			if(!vis[u] && (v == -1 || mincost[u]<mincost[v]))
				v=u;

		vis[v]=1;

		for(u=0;u<Node->vexnum;u++)
			if(mincost[u]>mincost[v]+Node->Matrix[v][u].Vertex)
			{
				mincost[u]=mincost[v]+Node->Matrix[v][u].Vertex;
				previs[u]=v;
			}
	}
	
	printf("·������  ·��\n");
	for(i=0;i<Node->vexnum;i++)
	{
		if(mincost[i]!=INF)
			printf("%5d    ",mincost[i]);
		else
			printf("%5s    ","��");
		for(u=i;;u=previs[u])
		{
			printf("%d",u+1);
			if(u==start-1)
				break;
			printf("<-");
		}
		printf("\n");
	}
	
	free(vis);
	free(mincost);
	free(previs);
}

int main()
{
	MGraph image;
	int v;
	printf("����ͼ�ж�����ͻ���:");
	scanf("%d,%d",&image.vexnum,&image.arcnum);
	image.Tag=4;
	InitMatrix(&image);
	CreatGraph(&image);
	while(1)
	{
		printf("\n��Դ·��,����Դ��v:");
		scanf("%d",&v);
		if(v==-1)
			break;
		dijkstra(&image,v);
	}
	return 0;
}

/*
Matrix input:
1,3,13
1,7,17
7,6,76
7,4,74
3,2,32
6,1,61
6,4,64
4,5,45
5,6,56
2,6,26
*/

