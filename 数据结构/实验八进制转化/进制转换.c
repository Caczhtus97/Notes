#include<stdio.h>
#include<stdlib.h>

/*
    利用顺序栈的方法声明一个链栈的结构体
    链栈的性质均与链栈相似
*/

//******宏定义参数******
#define OK 1
#define NO 0
#define STACK_MAX_SIZE 20

//******定义数据类型别名******
typedef int Status;
typedef char ElemType;
typedef double db;

//******声明数据结构******
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
		printf("对不起,该栈为空!\n");
		return NO;
	}
	return (Head->top->next)->ch;
}

void StackPush(HeadPoint Head,ElemType ch)
{
	StackPoint p=(StackPoint)malloc(sizeof(SqStack));
	if(p==NULL)
	{
		printf("对不起，系统内存不足!入栈失败!\n");
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
		printf("对不起,当前栈为空，无内容可出栈!\n");
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
	void f(int data,int m)//负数的情况外面先预处理
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
	printf("%s\n",StackEmpty(Head)?"该栈为空!":"该栈非空!");
	do
	{
		printf("输入一个十进制数n,按0退出:");
		scanf("%d",&n);
		if(n==0)
			break;
		printf("输入你想要变成的进制:");
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
	printf("顺序栈操作结束!\n");
	return 0;
}

