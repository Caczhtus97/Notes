#include<stdio.h>
#include<stdlib.h>

//******�궨�����******
#define OK 1
#define NO 0
#define STACK_MAX_SIZE 20

//******�����������ͱ���******
typedef int Status;
typedef char ElemType;
typedef double db;

//******�������ݽṹ******
typedef struct node
{
	ElemType ch;
	int StackSize;
	struct node *base;
	struct node *top;
}SqStack,*StackPoint;

StackPoint InitStack()
{
	StackPoint p=NULL;
	p=(StackPoint)malloc(sizeof(SqStack));
	if(!p)
	{
		printf("ͷ����ڴ�����ʧ��!\n");
		return p;
	}
	p->base=NULL;
	p->base=(StackPoint)malloc(STACK_MAX_SIZE*sizeof(SqStack));
	p->StackSize=0;
	if(!(p->base))
		printf("ջ�ڴ�����ʧ��!\n");
	else
	{
		p->top=p->base;
		p->StackSize=STACK_MAX_SIZE;
		printf("ջ�ڴ�����ɹ�!\n");
	}
	return p;
}

Status StackEmpty(StackPoint Head)
{
	if(Head->base == Head->top)
		return OK;
	return NO;
}

Status Extend(StackPoint Head)
{
	StackPoint p;
	int size=Head->StackSize;
	p=(StackPoint)realloc(Head->base,(size+STACK_MAX_SIZE)*sizeof(SqStack));
	if(p==NULL)
	{
		printf("��̬�ڴ�����ʧ�ܣ�\n");
		return NO;
	}
	else
	{
		Head->base=p;
		Head->StackSize=size+STACK_MAX_SIZE;
	}
	return OK;
}

ElemType getTop(StackPoint Head)
{
	if(StackEmpty(Head))
	{
		printf("��ջΪ��ջ!\n");
		return NO;
	}
	return (Head->top-1)->ch;
}

void StackPush(StackPoint Head,ElemType ch)
{
	if(Head->top-Head->base>=Head->StackSize && !Extend(Head))
	{
		printf("\"%c\"��ջʧ��!\n",ch);
		return ;
	}
	Head->top++->ch=ch;
	return ;
}

void StackPop(StackPoint Head)
{
	if(StackEmpty(Head))
	{
		printf("���棡��ǰջΪ��,��ջʧ��!\n");
		return ;
	}
	Head->top--;
	printf("��ջ�ɹ�!\n");
	return ;
}

int main()
{
	StackPoint Head;
	int i;
	Head=InitStack();
	for(i=0;i<4;i++)
		StackPush(Head,'A'+i);
	for(i=0;i<4;i++)
	{
		printf("%c\n",getTop(Head));
		StackPop(Head);
	}
	free(Head->base);
	free(Head);
	return 0;
}
