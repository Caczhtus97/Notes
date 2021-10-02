#include<stdio.h>
#include<stdlib.h>

//******�궨�����******
#define OK 1
#define NO 0
#define DATA_MAX_SIZE 20

//******�����������ͱ���******
typedef int Status;
typedef char Excelelem;
typedef int Numelem;

//******�������ݽṹ******
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

//******��ʼ������******
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
	//ʡ�Ա�ͷ��Ϣ  Head->name
	HeadLinkList Head;
	Head=(HeadLinkList)malloc(sizeof(HeadList));
	Head->length=0;
	Head->next=init(&Head->length);
	return Head;
}

//******��������е���Ϣ******
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

//******�����ڴ�******
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

//******��iλ��֮ǰ����һ��Ԫ��ch******
void DATA_Insert(HeadLinkList Head,Numelem k,Excelelem ch)
{
	int i=1;
	LinkList q=Head->next,p,t;
	if(Head->length && (Head->length<k || k<1))
	{
		printf("���棡%dλ�ò��Ϸ�\n",k);
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

//******�����Ƿ�����ַ�ch******
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
	DATA_Free(C); //��ʼ���������C����ֹ�ڴ�й©
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
����ΪO(n*n)�㷨
����һ��ΪO(n)�㷨,���ڹ�������ʱԤ�����Ѽ��ϵ���Ϣӳ�䵽һ��ASCLL���У�֮��ֱ�Ӳ����ȥ�˱�������Ĳ���,Ϊ��֮��
�Ĳ���������жϣ���Ԥ�����ʱ��Ҫ��¼���ݵı߽�

������:
if book[ch]==2
	C.Insert(ch);
������:
if book[ch]!=0
	C.Insert(ch);
������:
if book[ch]==1
	C.Insert(ch);

*****************************/

int main()
{
	HeadLinkList A,B,C;
	C=(HeadLinkList)malloc(sizeof(HeadList));
	C->next=NULL;
	C->length=0;
	printf("******��ʼ������A******\n");
	A=HeadInit();
	printf("******��ʼ������B******\n");
	B=HeadInit();
	printf("*****����AB�Ľ��*****\n");
	SetJiao(A,B,C);
	DATA_cout(C);
	printf("*****����A+B�Ľ��*****\n");
	SetBing(A,B,C);
	DATA_cout(C);
	printf("*****����A-B�Ľ��*****\n");
	SetCha(A,B,C);
	DATA_cout(C);
	printf("***********************\n");
	printf("*******�ͷ��ڴ�*******\n");
	DATA_Free(A),DATA_Free(B),DATA_Free(C);
	free(A),free(B),free(C);
	printf("**********End!**********\n");
	return 0;
}
