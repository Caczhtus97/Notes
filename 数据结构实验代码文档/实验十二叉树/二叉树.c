#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

//******�궨�����******
#define NO 0
#define OK 1
#define EORRO 0

//******�����������ͱ���******
typedef char ElemType;
typedef int Status;

//******�������ݽṹ******
typedef struct TNode
{
	ElemType data;
	struct TNode *lchild;
	struct TNode *rchild;
}BinaryTree,*BiTreePoint;

typedef struct SNode
{
	BiTreePoint *data;
	struct SNode *next;
}StackNode,*StackPoint;

typedef struct
{
	int StackSize;
	StackPoint base;
	StackPoint top;
}StackHead,*StackHeadPoint;

typedef struct QNode
{
	BiTreePoint *data;
	struct QNode *next;
}QueueNode,*QueuePoint;

typedef struct
{
	int QueueSize;
	QueuePoint front;
	QueuePoint rear;
}QueueHead,*QueueHeadPoint;

//******����Ϊ��ջ�����ݽṹ����******
StackHeadPoint InitStack()
{
	StackHeadPoint Head=(StackHeadPoint)malloc(sizeof(StackHead));
	Head->StackSize=0;
	Head->base=Head->top=(StackPoint)malloc(sizeof(StackNode));
	return Head;
}

Status StackEmpty(StackHeadPoint Head)
{
	if(Head->base == Head->top)
		return OK;
	return NO;
}

BiTreePoint* getTop(StackHeadPoint *Head)
{
	if(StackEmpty(*Head))
		return NULL;
	return (*Head)->top->next->data;
}

Status StackPush(StackHeadPoint *Head,BiTreePoint *data)
{
	StackPoint p=(StackPoint)malloc(sizeof(StackNode));
	if(p==NULL)
	{
		printf("�Բ���ϵͳ�ڴ治��!��ջʧ��!\n");
		return NO;
	}
	(*Head)->top->data=data;
	p->next=(*Head)->top;
	(*Head)->top=p;
	(*Head)->StackSize++;
	return OK;
}

Status StackPop(StackHeadPoint *Head)
{
	StackPoint p=(*Head)->top;
	if(StackEmpty(*Head))
		return NO;
	(*Head)->top=p->next;
	(*Head)->StackSize--;
	free(p);
	return OK;
}

Status StackDelete(StackHeadPoint *Head)
{
	while(!StackEmpty(*Head))
		StackPop(Head);
	free((*Head)->base);
	return OK;
}
//******����Ϊ��ջ���ݽṹ����******

//******����Ϊ���������ݽṹ����******
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

BiTreePoint* getFront(QueueHeadPoint *Head)
{
	if(QueueEmpty(*Head))
		return NULL;
	return (*Head)->front->next->data;
}

Status QueuePush(QueueHeadPoint *Head,BiTreePoint *data)
{
	QueuePoint p=(QueuePoint)malloc(sizeof(QueueNode));
	if(p==NULL)
	{
		printf("�Բ���ϵͳ�ڴ治��!��ջʧ��!\n");
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
//******����Ϊ���������ݽṹ����******

//******����Ϊ���������ݽṹ����******
BiTreePoint InitBiTree()
{
	return NULL;
}

Status BiTreeEmpty(BiTreePoint T)
{
	if(T==NULL)
		return OK;
	return NO;
}

BiTreePoint CreatBiTree()  //�ǵݹ������������
{
	BiTreePoint *temp,T;
	ElemType ch;
	StackHeadPoint Head=InitStack();
	temp=&T;
	do
	{
		ch=getchar();
		if(ch=='^')
			(*temp)=NULL;
		else
		{
			(*temp)=(BiTreePoint)malloc(sizeof(BinaryTree));
			if(*temp==NULL)
			{
				printf("�Բ���,ϵͳ�ڴ治��,��������ʧ��,������!\n");
				system("pause");
			}
			(*temp)->data=ch;
			StackPush(&Head,&(*temp)->rchild);
			StackPush(&Head,&(*temp)->lchild);
		}
		temp=getTop(&Head);
	}while(!StackEmpty(Head) && StackPop(&Head));
	StackDelete(&Head);
	return T;
}

Status PreOrderTraverse(BiTreePoint T) //�ǵݹ������������
{
	BiTreePoint *temp;
	StackHeadPoint Head=InitStack();
	temp=&T;
	while(*temp || !StackEmpty(Head))
	{
		if(*temp)
		{
			printf("%c",(*temp)->data);
			if(!StackPush(&Head,temp))
			{
				printf("�Բ���,��ǰϵͳ�ڴ治��,����������ʧ��!\n");
				return NO;
			}
			temp=&(*temp)->lchild;
		}
		else
		{
			temp=getTop(&Head);
			StackPop(&Head);
			temp=&(*temp)->rchild;
		}
	}
	StackDelete(&Head);
	printf("\n");
	return OK;
}

Status InOrderTraverse(BiTreePoint T) //�ǵݹ������������
{
	BiTreePoint *temp;
	StackHeadPoint Head=InitStack();
	temp=&T;
	while(*temp || !StackEmpty(Head))
	{
		if(*temp)
		{
			if(!StackPush(&Head,temp))
			{
				printf("�Բ���,��ǰϵͳ�ڴ治��,����������ʧ��!\n");
				return NO;
			}
			temp=&(*temp)->lchild;
		}
		else
		{
   			temp=getTop(&Head);
			printf("%c",(*temp)->data);
  			StackPop(&Head);
			temp=&(*temp)->rchild;
		}
	}
	StackDelete(&Head);
	printf("\n");
	return OK;
}

Status PostOrderTraverse(BiTreePoint T)  //�ǵݹ�����������
{
	BiTreePoint *temp;
	Status flag=1;
	StackHeadPoint Head=InitStack();
	if(T==NULL || !StackPush(&Head,&T))
	{
		printf("\n");
		return OK;
	}
	temp=&T->lchild;
	while(!StackEmpty(Head))
	{
		if(*temp && flag)
		{
  			if(!StackPush(&Head,temp))
			{
				printf("�Բ���,��ǰϵͳ�ڴ治��,����������ʧ��!\n");
				return NO;
			}
			temp=&(*temp)->lchild;
		}
		else if(temp==&(*(getTop(&Head)))->lchild)
		{
			temp=&(*(getTop(&Head)))->rchild;
			flag=1;
		}
		else
		{
			temp=getTop(&Head);
			StackPop(&Head);
			printf("%c",(*temp)->data);
			while(temp!=&T && temp==&(*(getTop(&Head)))->rchild)
			{
				temp=getTop(&Head);
				StackPop(&Head);
				printf("%c",(*temp)->data);
			}
			flag=0;
		}
	}
	StackDelete(&Head);
	printf("\n");
	return OK;
}

Status PostOrderTraverse2(BiTreePoint T) //�ǵݹ�����������2
{
	BiTreePoint *temp,*before;
	StackHeadPoint Head=InitStack();
	if(T==NULL || !StackPush(&Head,&T))
	{
		printf("\n");
		return OK;
	}
	before=NULL;
	while(!StackEmpty(Head))
	{
		temp=getTop(&Head);
		if( (*temp)->lchild==NULL && (*temp)->rchild==NULL || before && (before==&(*temp)->lchild || before==&(*temp)->rchild) )
		{
			printf("%c",(*temp)->data);
			StackPop(&Head);
			before=temp;
		}
		else
		{
			if((*temp)->rchild)
			{
				if(!StackPush(&Head,&(*temp)->rchild))
				{
					printf("�Բ���,��ǰϵͳ�ڴ治��,����������ʧ��!\n");
					return NO;
				}
			}
			if((*temp)->lchild)
			{
				if(!StackPush(&Head,&(*temp)->lchild))
				{
					printf("�Բ���,��ǰϵͳ�ڴ治��,����������ʧ��!\n");
					return NO;
				}
			}
		}
	}
	StackDelete(&Head);
	printf("\n");
	return OK;
}

Status LevelOrderTraverse(BiTreePoint T) //�����������
{
	BiTreePoint *temp;
	QueueHeadPoint Head=InitQueue();
	if(T==NULL || !QueuePush(&Head,&T))
	{
		printf("\n");
		return OK;
	}
	while(!QueueEmpty(Head))
	{
		temp=getFront(&Head);
		QueuePop(&Head);
		printf("%c",(*temp)->data);
		if((*temp)->lchild)
		{
			if(!QueuePush(&Head,&(*temp)->lchild))
			{
				printf("�Բ���,��ǰϵͳ�ڴ治��,����������ʧ��!\n");
					return NO;
			}
		}
		if((*temp)->rchild)
		{
			if(!QueuePush(&Head,&(*temp)->rchild))
			{
				printf("�Բ���,��ǰϵͳ�ڴ治��,����������ʧ��!\n");
				return NO;
			}
		}
	}
	QueueDelete(&Head);
	printf("\n");
	return OK;
}

int MAX(int a,int b)
{
	return a>b?a:b;
}

int CountBiTreeDep(BiTreePoint T)
{
 	if(T==NULL)
		return 0;
	return MAX(CountBiTreeDep(T->lchild),CountBiTreeDep(T->rchild))+1;
}

int CountBiTreeleaf(BiTreePoint T)
{
	if(T==NULL)
		return 0;
	else if(T->lchild==NULL && T->rchild==NULL)
		return 1;
	return CountBiTreeleaf(T->rchild)+CountBiTreeleaf(T->lchild);
}
//******����Ϊ���������ݽṹ����******

int main()
{
	BiTreePoint T;
	printf("�����򹹽�������(^:��ʾ��,���б�ʾ���һ���������!):\n");
	T=CreatBiTree();
    printf("�������������Ϊ:\n");
	PreOrderTraverse(T);
	printf("�������������Ϊ:\n");
	InOrderTraverse(T);
	printf("�����ĺ������Ϊ:\n");
	PostOrderTraverse(T);
	printf("�����ĺ��������2Ϊ:\n");
	PostOrderTraverse2(T);
	printf("�����İ������Ϊ:\n");
	LevelOrderTraverse(T);
	printf("���������Ϊ:\n");
	printf("%d\n",CountBiTreeDep(T));
	printf("������Ҷ�Ӹ���Ϊ:\n");
	printf("%d\n",CountBiTreeleaf(T));
	return 0;
}
