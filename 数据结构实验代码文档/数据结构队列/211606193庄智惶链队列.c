#include<stdio.h>
#include<stdlib.h>

//******�궨�����******
#define OK 1
#define NO 0
#define EORRO 0

//******�����������ͱ���******
typedef int Status;
typedef char ElemType;
typedef double db;

//******�������ݽṹ******
typedef struct node
{
	ElemType ch;
	struct node *next;
}QueueNode,*QueuePoint;

typedef struct
{
	int QueueSize;
	QueuePoint front;
	QueuePoint rear;
}HeadNode,*HeadPoint;

HeadPoint InitQueue()
{
	HeadPoint Head=(HeadPoint)malloc(sizeof(HeadNode));
	Head->QueueSize=0;
	Head->front=Head->rear=(QueuePoint)malloc(sizeof(QueueNode));
	Head->rear->next=NULL;
	Head->front->ch=NO;
	return Head;
}

Status QueueEmpty(HeadPoint Head)
{
	if(Head->front == Head->rear)
		return OK;
	return NO;
}

ElemType getFront(HeadPoint Head)
{
	if(QueueEmpty(Head))
	{
		printf("�Բ���,�ö���Ϊ��!\n");
		return NO;
	}
	return Head->front->next->ch;
}

void QueuePop(HeadPoint Head)
{
	QueuePoint p=Head->front;
	if(QueueEmpty(Head))
	{
		printf("�Բ���,�ö���Ϊ��!�޿ɳ���Ԫ��!\n");
		return ;
	}
	Head->front=p->next;
	Head->QueueSize--;
	free(p);
	return ;
}

void QueuePush(HeadPoint Head,ElemType ch)
{
	QueuePoint p=(QueuePoint)malloc(sizeof(QueueNode));
	if(p==NULL)
	{
		printf("�Բ���ϵͳ�ڴ治��!���ʧ��!\n");
		return ;
	}
	p->next=Head->rear->next;
	p->ch=ch;
	Head->rear->next=p;
	Head->rear=p;
	Head->QueueSize++;
	return ;
}

void QueueDelete(HeadPoint Head)
{
	while(!QueueEmpty(Head))
		QueuePop(Head);
	free(Head->front);
	return ;
}

int main()
{
	ElemType ch;
	HeadPoint Head=InitQueue();
	printf("%s\n",QueueEmpty(Head)?"�ö���Ϊ��!":"�ö��зǿ�!");
	while((ch=getchar())!='\n')
		QueuePush(Head,ch);
	printf("%s\n",QueueEmpty(Head)?"�ö���Ϊ��!":"�ö��зǿ�!");
	while(!QueueEmpty(Head))
	{
		printf("%c",getFront(Head));
		QueuePop(Head);
	}
	printf("\n%s\n",QueueEmpty(Head)?"�ö���Ϊ��!":"�ö��зǿ�!");
	QueueDelete(Head);
	free(Head);
	printf("�����в�������!\n");
	return 0;
}
