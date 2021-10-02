#include<stdio.h>
#include<stdlib.h>

//******�궨�����******
#define OK 1
#define NO 0
#define QUEUE_MAX_SIZE 20

//******�����������ͱ���******
typedef int Status;
typedef char ElemType;

//******�������ݽṹ******
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
		printf("ϵͳ���㹻�ڴ�����ѭ������ͷ���!\n");
		return p;
	}
	p->book=(ElemType *)malloc(QUEUE_MAX_SIZE*sizeof(ElemType));
	p->front=p->rear=0;
	p->QueSize=QUEUE_MAX_SIZE;
	if(p->book == NULL)
		printf("ѭ�������ڴ����ʧ��!\n");
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
	//	printf("\n�Բ���,�ö�������,�޷��ٲ�������!\n");
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
	//	printf("\n�Բ���,�����ѿ�!\n");
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
	printf("%s\n",QueueEmpty(Head)?"��ջΪ��!":"��ջ�ǿ�!");
	while((ch=getchar())!='\n')
		QueuePush(Head,ch);
//	printf("%s\n",QueueEmpty(Head)?"��ջΪ��!":"��ջ�ǿ�!");
	QueuePop(Head,&ch);
	printf("%c\n",ch);
	while((ch=getchar())!='\n')
		QueuePush(Head,ch);
	while(QueuePop(Head,&ch))
		printf("%c",ch);
	free(Head->book);
	free(Head);
	printf("\nѭ�����в�������!\n");
	return 0;
}

