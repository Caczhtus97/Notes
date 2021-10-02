#include<stdio.h>
#include<stdlib.h>

//******宏定义参数******
#define OK 1
#define NO 0
#define DATA_MAX_SIZE 20

//******定义数据类型别名******
typedef int Status;
typedef char Excelelem;
typedef int Numelem;

//******声明数据结构******
typedef struct Node
{
	Excelelem book;
	struct Node *next;
}LNode,*LinkList;

typedef struct
{
	Excelelem name[100];
	Numelem length;
	LinkList next;
}HeadList,*HeadLinkList;

//******初始化链表******
LinkList init(int *i)
{
	LinkList Head,p,q;
	Excelelem ch;
	Head=q=NULL;
	while((ch=getchar())!='\n')
	{
		p=(LinkList)malloc(sizeof(LNode));
		p->book=ch;
		if (!(*i)) Head=q=p,(*i)++;
		else
		{
			q->next=p;
			q=p;
			(*i)++;
		}
	}
	if(p) p->next=NULL;
	return Head;
}

HeadLinkList HeadInit()
{
	//省略表头信息  Head->name
	HeadLinkList Head;
	Head=(HeadLinkList)malloc(sizeof(HeadList));
	Head->length=0;
	Head->next=init(&Head->length);
	return Head;
}

//******输出链表中的信息******
void DATA_cout(HeadLinkList Head)
{
	LinkList p=Head->next;
	while(p!=NULL)
	{
		printf("%c",p->book);
		p=p->next;
	}
	printf("\n");
	return ;
}

//******返还内存******
void DATA_Free(HeadLinkList Head)
{
	LinkList q=Head->next,p;
	while (q!=NULL)
	{
		p=q;
		q=q->next;
		free(p);
	}
	Head->length=0;
	Head->next=NULL;
	return ;
}

//******在i位置之前插入一个元素ch******
void DATA_Insert(HeadLinkList Head,Numelem k,Excelelem ch)
{
	int i=1;
	LinkList q=Head->next,p,t;
	if(Head->length && (Head->length<k || k<1))
	{
		printf("警告！%d位置不合法\n",k);
		return ;
	}
	while(p && i++ < k)
		p=q,q=q->next;
	t=(LinkList)malloc(sizeof(LNode));
	t->book=ch;
	if(k==1)
	{
		Head->next=t;
		t->next=q;
	}
	else
	{
		t->next=p;
		q->next=t;
	}
	Head->length++;
	return ;
}

//******查找是否出现字符ch******
int DATA_find(HeadLinkList Head,Excelelem ch)
{
	LinkList q=Head->next;
	while(q!=NULL && q->book!=ch)
		q=q->next;
	if(q==NULL)
		return NO;
	return OK;
}

//******AB******
void SetJiao(HeadLinkList A,HeadLinkList B,HeadLinkList C)
{
	LinkList q=A->next;
	DATA_Free(C); //初始化结果集合C，防止内存泄漏
	while (q!=NULL)
	{
		if(DATA_find(B,q->book) && !DATA_find(C,q->book))
			DATA_Insert(C,1,q->book);
		q=q->next;
	}
	return ;
}

//******A+B******
void SetBing(HeadLinkList A,HeadLinkList B,HeadLinkList C)
{
	LinkList q=A->next;
	DATA_Free(C);
	while(q!=NULL)
	{
		if(!DATA_find(C,q->book))
			DATA_Insert(C,1,q->book);
		q=q->next;
	}
	q=B->next;
	while(q!=NULL)
	{
		if(!DATA_find(C,q->book))
			DATA_Insert(C,1,q->book);
		q=q->next;
	}
	return ;
}

//******A-B******
void SetCha(HeadLinkList A,HeadLinkList B,HeadLinkList C)
{
	LinkList q=A->next;
	DATA_Free(C);
	while(q!=NULL)
	{
		if(!DATA_find(B,q->book) && !DATA_find(C,q->book))
			DATA_Insert(C,1,q->book);
		q=q->next;
	}
	return ;
}

/***************************
以上为O(n*n)算法
还有一种为O(n)算法,即在构建集合时预处理，把集合的信息映射到一张ASCLL表中，之后直接查表，免去了遍历链表的步骤,为了之后
的查表不做多余判断，在预处理的时候，要记录数据的边界

交运算:
if book[ch]==2
	C.Insert(ch);
并运算:
if book[ch]!=0
	C.Insert(ch);
差运算:
if book[ch]==1
	C.Insert(ch);

*****************************/

int main()
{
	HeadLinkList A,B,C;
	C=(HeadLinkList)malloc(sizeof(HeadList));
	C->next=NULL;
	C->length=0;
	printf("******初始化集合A******\n");
	A=HeadInit();
	printf("******初始化集合B******\n");
	B=HeadInit();
	printf("*****集合AB的结果*****\n");
	SetJiao(A,B,C);
	DATA_cout(C);
	printf("*****集合A+B的结果*****\n");
	SetBing(A,B,C);
	DATA_cout(C);
	printf("*****集合A-B的结果*****\n");
	SetCha(A,B,C);
	DATA_cout(C);
	printf("***********************\n");
	printf("*******释放内存*******\n");
	DATA_Free(A),DATA_Free(B),DATA_Free(C);
	free(A),free(B),free(C);
	printf("**********End!**********\n");
	return 0;
}
