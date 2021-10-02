#include<stdio.h>
#include<stdlib.h>

//******宏定义参数******
#define OK 1
#define NO 0
#define EORRO 0

//******声明数据类型别名******
typedef int Status;
typedef char ElemType;
typedef double db;

//******声明数据结构******
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
		printf("对不起,该队列为空!\n");
		return NO;
	}
	return Head->front->next->ch;
}

void QueuePop(HeadPoint Head)
{
	QueuePoint p=Head->front;
	if(QueueEmpty(Head))
	{
		printf("对不起,该队列为空!无可出队元素!\n");
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
		printf("对不起，系统内存不足!入队失败!\n");
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
	printf("%s\n",QueueEmpty(Head)?"该队列为空!":"该队列非空!");
	while((ch=getchar())!='\n')
		QueuePush(Head,ch);
	printf("%s\n",QueueEmpty(Head)?"该队列为空!":"该队列非空!");
	while(!QueueEmpty(Head))
	{
		printf("%c",getFront(Head));
		QueuePop(Head);
	}
	printf("\n%s\n",QueueEmpty(Head)?"该队列为空!":"该队列非空!");
	QueueDelete(Head);
	free(Head);
	printf("链队列操作结束!\n");
	return 0;
}
