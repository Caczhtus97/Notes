#include<stdio.h>
#include<stdlib.h>

//******宏定义参数******
#define OK 1
#define NO 0
#define QUEUE_MAX_SIZE 20

//******定义数据类型别名******
typedef int Status;
typedef char ElemType;

//******声明数据结构******
typedef struct node
{
	ElemType *book;
	int front;
	int rear;
	int QueSize;
}SqQueue,*QueuePoint;

QueuePoint InitQueue()
{
	QueuePoint p=(QueuePoint)malloc(sizeof(SqQueue));
	if(p==NULL)
	{
		printf("系统无足够内存申请循环队列头结点!\n");
		return p;
	}
	p->book=(ElemType *)malloc(QUEUE_MAX_SIZE*sizeof(ElemType));
	p->front=p->rear=0;
	p->QueSize=QUEUE_MAX_SIZE;
	if(p->book == NULL)
		printf("循环队列内存分配失败!\n");
	return p;
}

Status QueueEmpty(QueuePoint Head)
{
	if(Head->front == Head->rear)
		return OK;
	return NO;
}

Status QueuePush(QueuePoint Head,ElemType ch)
{
	if((Head->rear+1)%Head->QueSize == Head->front)
	{
	//	printf("\n对不起,该队列已满,无法再插入数据!\n");
		return NO;
	}
	Head->book[Head->rear]=ch;
	Head->rear=(Head->rear+1)%Head->QueSize;
	return OK;
}

Status QueuePop(QueuePoint Head,ElemType *ch)
{
	if(Head->front == Head->rear)
	{
	//	printf("\n对不起,队列已空!\n");
		return NO;
	}
	*ch=Head->book[Head->front];
	Head->front=(Head->front+1)%Head->QueSize;
	return OK;
}

int main()
{
	QueuePoint Head;
	ElemType ch;
	Head=InitQueue();
	printf("%s\n",QueueEmpty(Head)?"该栈为空!":"该栈非空!");
	while((ch=getchar())!='\n')
		QueuePush(Head,ch);
//	printf("%s\n",QueueEmpty(Head)?"该栈为空!":"该栈非空!");
	QueuePop(Head,&ch);
	printf("%c\n",ch);
	while((ch=getchar())!='\n')
		QueuePush(Head,ch);
	while(QueuePop(Head,&ch))
		printf("%c",ch);
	free(Head->book);
	free(Head);
	printf("\n循环队列操作结束!\n");
	return 0;
}

