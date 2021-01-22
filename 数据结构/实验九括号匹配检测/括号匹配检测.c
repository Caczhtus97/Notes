#include<stdio.h>
#include<stdlib.h>

//******宏定义参数******
#define OK 1
#define NO 0
#define STACK_MAX_SIZE 10001

//******定义数据类型别名******
typedef int Status;
typedef char ElemType;

//******声明数据结构******
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
		printf("头结点内存申请失败!\n");
		return p;
	}
	p->base=NULL;
	p->base=(StackPoint)malloc(STACK_MAX_SIZE*sizeof(SqStack));
	p->StackSize=0;
	if(!(p->base))
		printf("栈内存申请失败!\n");
	else
	{
		p->top=p->base;
		p->StackSize=STACK_MAX_SIZE;
		printf("栈内存申请成功!\n");
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
		printf("动态内存申请失败！\n");
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
		printf("警告!该栈为空栈!\n");
		return NO;
	}
	return (Head->top-1)->ch;
}

void StackPush(StackPoint Head,ElemType ch)
{
	if(Head->top-Head->base>=Head->StackSize && !Extend(Head))
	{
		printf("\"%c\"入栈失败!\n",ch);
		return ;
	}
	Head->top++->ch=ch;
	return ;
}

void StackPop(StackPoint Head)
{
	if(StackEmpty(Head))
	{
		printf("警告！当前栈为空,出栈失败!\n");
		return ;
	}
	Head->top--;
	return ;
}

Status Stringjudge(StackPoint Head,ElemType *book)
{
	int i;
	for(i=0;book[i]!=0;i++)
	{
		if(book[i]==')')
		{
			if(getTop(Head)!='(')
				return NO;
			else
				StackPop(Head);
		}
		else if(book[i]==']')
		{
			if(getTop(Head)!='[')
				return NO;
			else
				StackPop(Head);
		}
		else
			StackPush(Head,book[i]);
	}
	if(StackEmpty(Head))
		return OK;
	return NO;
}

int main()
{
	StackPoint Head;
	ElemType ch,book[10001];
	int i;
	Head=InitStack();
	printf("输入0结束括号匹配检测!\n");
	while(scanf("%s",book) && book[0]!='0')
	{
		printf("%s\n",book);
		if(Stringjudge(Head,book))
			printf("Yes\n");
		else
			printf("No\n");
		Head->top=Head->base;
	}
	free(Head->base);
	free(Head);
	printf("顺序栈操作结束!\n");
	return 0;
}

