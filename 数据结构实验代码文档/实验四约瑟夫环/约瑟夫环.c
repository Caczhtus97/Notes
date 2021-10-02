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
	Numelem book;
	struct Node *next;
}LNode,*LinkList;

typedef struct
{
	Excelelem name[100];
	Numelem length;
	LinkList next;
}HeadList,*HeadLinkList;

//******初始化链表******
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
	//省略表头信息  Head->name
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
		printf("该约瑟夫环已无操作元素!\n");
		return ;
	}
	while(n!=p->book)
	{
		p=p->next;
		if(p==Head->next)
		{
			printf("不存在编号为%d的入口!\n",n);
			return ;
		}
	}
	while(1)
	{
		for(i=1;i<k;i++)
			q=p,p=p->next;
		printf("第%d次时,第%d个元素出环!\n",cnt++,p->book);
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
	printf("该约瑟夫环已无操作元素!\n");
	return ;
}

int main()
{
	HeadLinkList Head;
	Numelem n,m;
	printf("**********start!**********\n");
	printf("请输入约瑟夫环的规模!\n");
	scanf("%d",&n);
	Head=HeadInit(n);
	printf("请输入约瑟夫环的入口!\n");
	scanf("%d",&m);
	printf("请输入约瑟夫环每次的出环规模!\n");
	scanf("%d",&n);
	printf("请检查约瑟夫环的操作情况!\n");
	DATA_Joseph(Head,m,n);
	free(Head);
	printf("**********End!**********\n");
	return 0;
}
