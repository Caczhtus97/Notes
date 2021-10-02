#include<stdio.h>
#include<stdlib.h>

/*
    ����˳��ջ�ķ�������һ����ջ�Ľṹ��
    ��ջ�����ʾ�����ջ����
*/

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
	struct node *next;
}SqStack,*StackPoint;

typedef struct
{
	int StackSize;
	StackPoint base;
	StackPoint top;
}HeadNode,*HeadPoint;

HeadPoint InitStack()
{
	HeadPoint Head=(HeadPoint)malloc(sizeof(HeadNode));
	Head->StackSize=0;
	Head->base=Head->top=(StackPoint)malloc(sizeof(SqStack));
	return Head;
}

Status StackEmpty(HeadPoint Head)
{
	if(Head->base == Head->top)
		return OK;
	return NO;
}

ElemType getTop(HeadPoint Head)
{
	if(StackEmpty(Head))
	{
		printf("�Բ���,��ջΪ��!\n");
		return NO;
	}
	return (Head->top->next)->ch;
}

void StackPush(HeadPoint Head,ElemType ch)
{
	StackPoint p=(StackPoint)malloc(sizeof(SqStack));
	if(p==NULL)
	{
		printf("�Բ���ϵͳ�ڴ治��!��ջʧ��!\n");
		return ;
	}
	Head->top->ch=ch;
	p->next=Head->top;
	Head->top=p;
	Head->StackSize++;
	return ;
}

void StackPop(HeadPoint Head)
{
	StackPoint p=Head->top;
	if(StackEmpty(Head))
	{
		printf("�Բ���,��ǰջΪ�գ������ݿɳ�ջ!\n");
		return ;
	}
	Head->StackSize--;
	Head->top=p->next;
	free(p);
	return ;
}

void StackDelete(HeadPoint Head)
{
	while(!StackEmpty(Head))
		StackPop(Head);
	free(Head->base);
	return ;
}

/*
	void f(int data,int m)//���������������Ԥ����
	{
		if(data==0)
			return ;
		f(data/m);
		printf("%d",data%m);
		return ;
	}
*/

int main()
{
	ElemType ch;
	int n,m,t;
	HeadPoint Head;
	Head=InitStack();
	printf("%s\n",StackEmpty(Head)?"��ջΪ��!":"��ջ�ǿ�!");
	do
	{
		printf("����һ��ʮ������n,��0�˳�:");
		scanf("%d",&n);
		if(n==0)
			break;
		printf("��������Ҫ��ɵĽ���:");
		scanf("%d",&m);
		if(n<0)
		{
			n=-n;
			printf("-");
		}
		while(n)
		{
			t=n%m;
			if(t>=10)
				ch='A'+t-10;
			else
				ch='0'+t;
			StackPush(Head,ch);
			n/=m;
		}
		while(!StackEmpty(Head))
		{
			printf("%c",getTop(Head));
			StackPop(Head);
		}
		printf("\n");
	}while(1);
	StackDelete(Head);
	free(Head);
	printf("˳��ջ��������!\n");
	return 0;
}

