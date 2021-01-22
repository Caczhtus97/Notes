#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//******宏定义参数******
#define OK 1
#define NO 0
#define DATA_MAX_SIZE 20

//******定义数据类型别名******
typedef int Status;
typedef char Excelelem;
typedef int Numelem;
typedef double db;

//******声明数据结构******
typedef struct Node
{
	db xishu;
	db mi;
	struct Node *next;
}LNode,*LinkList;

typedef struct
{
	Excelelem name[100];
	Numelem length;
	LinkList next;
}HeadList,*HeadLinkList;

//******声明函数******
LinkList Init(Numelem *n); //初始化链表体
HeadLinkList HeadInit(char a[]); //初始化链表头
LinkList DATA_UPPER_FIND(LinkList Head,db ans); //查找链表中第一个系数大于ans的结点的前驱
void DATA_ADD(HeadLinkList A,HeadLinkList B,HeadLinkList C); //多项式加法 O(n)
void DATA_SUB(HeadLinkList A,HeadLinkList B,HeadLinkList C); //多项式减法 O(n)
void DATA_Free(HeadLinkList Head); //释放链表体内存
void DATA_cout(HeadLinkList Head); //将链表数据域以多项式形势输出
void DATA_MUL(HeadLinkList A,HeadLinkList B,HeadLinkList C); //多项式乘法 O(n^3),能到O(n^2)

int main()
{
	HeadLinkList A,B,C;
	Numelem n;
	printf("**********start!**********\n");
	A=HeadInit("A多项式");
	printf("请输入%s:\n",A->name);
	A->next=Init(&A->length);
	B=HeadInit("B多项式");
	printf("请输入%s:\n",B->name);
	B->next=Init(&B->length);
	C=HeadInit("C多项式");
	C->next=NULL;
	printf("请输出%s的内容:\n",A->name);
	DATA_cout(A);
	printf("请输出%s的内容\n",B->name);
	DATA_cout(B);
	printf("%s+%s:\n",A->name,B->name);
	DATA_ADD(A,B,C);
	DATA_cout(C);
	printf("%s-%s:\n",A->name,B->name);
	DATA_SUB(A,B,C);
	DATA_cout(C);
	printf("%s*%s:\n",A->name,B->name);
	DATA_MUL(A,B,C);
	DATA_cout(C);
	printf("操作结束，释放内存!\n");
	DATA_Free(A);DATA_Free(B);DATA_Free(C);
	free(A),free(B),free(C);
	printf("***********End!***********\n");
	return 0;
}

//******查找插入的位置******
LinkList DATA_UPPER_FIND(LinkList Head,db ans)
{
	if(Head->next == NULL || Head->next->mi > ans)
		return Head;
	return DATA_UPPER_FIND(Head->next,ans);
}

LinkList Init(Numelem *n)
{
	//以系数=0为输入结束标志,以下为输入的多项式默认为已合并同类项，否则在查找的时候多一项特判
	LinkList Head,p,q;
	Numelem i=0;
	db a,b;
	Head=NULL;
	while(~scanf("%lf",&a) && a!=0.0)
	{
		scanf("%lf",&b);
		q=(LinkList)malloc(sizeof(LNode));
		q->xishu=a;
		q->mi=b;
		if(*n==0 || Head->mi>b) q->next=Head,Head=q;
		else
		{
			p=DATA_UPPER_FIND(Head,b);
			//if p->mi==b ...  未合并同类项的情况
			q->next=p->next;
			p->next=q;
		}
		*n++;
	}
	return Head;
}

HeadLinkList HeadInit(char *a)
{
	HeadLinkList Head;
	Head=(HeadLinkList)malloc(sizeof(HeadList));
	strcpy(Head->name,a);
	Head->length=0;
	return Head;
}

void DATA_ADD(HeadLinkList A,HeadLinkList B,HeadLinkList C)
{
	LinkList qa=A->next,qb=B->next,p,q=NULL;
	DATA_Free(C);
	while(qa || qb)
	{
		p=(LinkList)malloc(sizeof(LNode));
		if(qb==NULL || qa && qa->mi<qb->mi)
		{
			*p=*qa;
			qa=qa->next;
		}
		else if(qa==NULL || qb && qa->mi>qb->mi)
		{
			*p=*qb;
			qb=qb->next;
		}
		else
		{
			p->xishu=qb->xishu+qa->xishu;
			p->mi=qb->mi;
			qa=qa->next;
			qb=qb->next;
		}
		if(q==NULL) p->next=q,C->next=q=p;
		else
			p->next=q->next,q->next=p,q=p;
		C->length++;
	}
}

void DATA_SUB(HeadLinkList A,HeadLinkList B,HeadLinkList C)
{
	LinkList qa=A->next,qb=B->next,p,q=NULL;
	DATA_Free(C);
	while(qa!=NULL || qb!=NULL)
	{
		p=(LinkList)malloc(sizeof(LNode));
		if(qb==NULL || qa && qa->mi<qb->mi)
		{
			*p=*qa;
			qa=qa->next;
		}
		else if(qa==NULL || qb && qa->mi>qb->mi)
		{
			*p=*qb;
			p->xishu*=-1;
			qb=qb->next;
		}
		else
		{
			*p=*qa;
			p->xishu-=qb->xishu;
			qa=qa->next;
			qb=qb->next;
			if(p->xishu==0)
			{
				free(p);
				continue;
			}
		}
		if(q==NULL) p->next=q,C->next=q=p;
		else
			q->next=p->next,q->next=p,q=p;
		C->length++;
	}
}

void DATA_MUL(HeadLinkList A,HeadLinkList B,HeadLinkList C)
{
	LinkList qa,qb,p,q;
	db a,b;
	DATA_Free(C);
	for(qa=A->next;qa;qa=qa->next)
	{
		for(qb=B->next;qb;qb=qb->next)
		{
			a=qa->xishu*qb->xishu;
			b=qa->mi+qb->mi;
			if(C->length)
			{
				p=DATA_UPPER_FIND(C->next,b);
				if(p->mi == b)
					p->xishu+=a;
				else
				{
					q=(LinkList)malloc(sizeof(LNode));
					q->xishu=a;
					q->mi=b;
					q->next=p->next;
					p->next=q;
					C->length++;
				}
			}
			else
			{
				p=(LinkList)malloc(sizeof(LNode));
				p->xishu=a;
				p->mi=b;
				p->next=C->next;
				C->next=p;
				C->length++;
			}
		}
	}
}

void DATA_Free(HeadLinkList Head)
{
	LinkList q=Head->next,p;
	while (q)
	{
		p=q;
		q=q->next;
		free(p);
	}
	Head->length=0;
	Head->next=NULL;
	return ;
}

void DATA_cout(HeadLinkList Head)
{
	LinkList q=Head->next;
	while(q)
	{
		if(q->xishu>0 && q!=Head->next)
			printf("+");
		printf("%.1lfx^(%.1lf)",q->xishu,q->mi);
		q=q->next;
	}
	printf("\n");
	return ;
}
