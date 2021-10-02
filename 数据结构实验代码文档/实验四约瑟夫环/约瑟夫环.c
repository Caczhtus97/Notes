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
	Numelem book;
	struct Node *next;
}LNode,*LinkList;

typedef struct
{
	Excelelem name[100];
	Numelem length;
	LinkList next;
}HeadList,*HeadLinkList;

//******��ʼ������******
LinkList init(Numelem *n)
{
	LinkList Head,p,q;
	Numelem i;
	Head=p=NULL;
	for(i=1;i<=*n;i++)
	{
		q=(LinkList)malloc(sizeof(LNode));
		q->book=i;
		if(i==1) Head=p=q;
		else
		{
			p->next=q;
			p=q;
		}
	}
	if(p) p->next=Head;
	return Head;
}

HeadLinkList HeadInit(int n)
{
	//ʡ�Ա�ͷ��Ϣ  Head->name
	HeadLinkList Head;
	Head=(HeadLinkList)malloc(sizeof(HeadList));
	Head->length=n;
	Head->next=init(&Head->length);
	return Head;
}

void DATA_Joseph(HeadLinkList Head,int n,int k)
{
	LinkList p=Head->next,q;
	Excelelem i,cnt=1;
	if(!Head->length)
	{
		printf("��Լɪ�����޲���Ԫ��!\n");
		return ;
	}
	while(n!=p->book)
	{
		p=p->next;
		if(p==Head->next)
		{
			printf("�����ڱ��Ϊ%d�����!\n",n);
			return ;
		}
	}
	while(1)
	{
		for(i=1;i<k;i++)
			q=p,p=p->next;
		printf("��%d��ʱ,��%d��Ԫ�س���!\n",cnt++,p->book);
		Head->length--;
		if(Head->length==0)
		{
			Head->next=NULL;
			free(p);
			break;
		}
		else
		{
			q->next=p->next;
			free(p);
			p=q->next;
		}
	}
	printf("��Լɪ�����޲���Ԫ��!\n");
	return ;
}

int main()
{
	HeadLinkList Head;
	Numelem n,m;
	printf("**********start!**********\n");
	printf("������Լɪ�򻷵Ĺ�ģ!\n");
	scanf("%d",&n);
	Head=HeadInit(n);
	printf("������Լɪ�򻷵����!\n");
	scanf("%d",&m);
	printf("������Լɪ��ÿ�εĳ�����ģ!\n");
	scanf("%d",&n);
	printf("����Լɪ�򻷵Ĳ������!\n");
	DATA_Joseph(Head,m,n);
	free(Head);
	printf("**********End!**********\n");
	return 0;
}
