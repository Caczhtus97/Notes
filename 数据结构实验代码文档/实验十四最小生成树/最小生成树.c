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
	char v1,v2;

	for(i=0;i<Node->vexnum;i++)
	{
		printf("����%d:%c\n",i+1,'A'+i);
		for(j=0;j<Node->vexnum;j++)
			Node->Matrix[i][j].Vertex=INF;
	}

	printf("�����(vi,vj)�ϵĶ���vi��vj��Ȩֵw:\n");
	for(i=0;i<Node->arcnum;i++)
	{
		getchar();
		scanf("%c %c %d",&v1,&v2,&w);
		Node->Matrix[v1-'A'][v2-'A'].Vertex=Node->Matrix[v2-'A'][v1-'A'].Vertex=w;
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

void prime(MGraph *Node,char start)
{
	int i,v,u;
	int *vis=(int *)malloc(Node->vexnum*sizeof(int));
	int *mincost=(int *)malloc(Node->vexnum*sizeof(int));
	int *previs=(int *)malloc(Node->vexnum*sizeof(int));
	
	for(i=0;i<Node->vexnum;i++)
	{
		vis[i]=0;
		mincost[i]=Node->Matrix[start-'A'][i].Vertex;
		previs[i]=start-'A';
	}
	
	vis[start-'A']=1;
	for(i=2;i<=Node->vexnum;i++)
	{
		v=-1;
		for(u=0;u<Node->vexnum;u++)
			if(!vis[u] && (v==-1 || mincost[u]<mincost[v]))
				v=u;
			
		printf("(%c,%c)%c",previs[v]+'A',v+'A'," \n"[i==Node->vexnum]);
		vis[v]=1;
		
		for(u=0;u<Node->vexnum;u++)
			if(mincost[u]>Node->Matrix[v][u].Vertex)
			{
				mincost[u]=Node->Matrix[v][u].Vertex;
				previs[u]=v;
			}
	}
	free(vis);
	free(mincost);
	free(previs);
}

int main()
{
	MGraph image;
	char u;
	printf("���붥�����ͱ���:\n");
	scanf("%d,%d",&image.vexnum,&image.arcnum);
	image.Tag=2;
	InitMatrix(&image);
	CreatGraph(&image);
	while(1)
	{
		printf("\n��������Ķ���u:");
		getchar();
		u=getchar();
		if(u=='^')
			break;
		prime(&image,u);
	}
	return 0;
}

/*
Matrix input:
A B 6
A C 1
A D 6
B C 6
C D 5
B E 3
C E 6
C F 4
E F 6
D F 2
*/
