#include<stdio.h>
#include<stdlib.h>

//******宏定义参数内容******
#define DATA_SIZE 200
#define EXTEND_DATA_SIZE 50
#define NO 0
#define OK 1
#define ERROR -1

//******基本数据类型别名******
typedef int Status;
typedef char Excelelem;
typedef int Numelem;

//******链表数据结构******
typedef struct Node
{
	Excelelem book;
	struct Node *next;
}Liststruct;

/******链表表头信息******/
typedef struct
{
	Excelelem book[100]; //表头信息
	Liststruct *next;
	Numelem Length;
}ListHead;

//******初始化链表******
Liststruct *init(int *i)
{
	Liststruct *Head,*p,*q;
	Excelelem ch;
	Head=q=NULL;
	printf("请输入顺序表Head的内容:\n");
	while((ch=getchar())!='\n')
	{
		p=(Liststruct *)malloc(sizeof(Liststruct));
		p->book=ch;
		if(!(*i)) Head=q=p,(*i)++;
		else
		{
			q->next=p;
			q=p;
			(*i)++;
		}
	}//注意*q++与(*q)++,有区别！
	if(q) q->next=NULL;
	return Head;
}

ListHead *Headinit()
{
	ListHead *Head;
	Head=(ListHead *)malloc(sizeof(ListHead));
	Head->Length=0;
	Head->next=init(&Head->Length);
	return Head;
}

/******打印表中数据内容******/
void DATA_cout(ListHead *Head)
{
	Liststruct *p=Head->next;
	while(p!=NULL)
	{
		printf("%c",p->book);
		p=p->next;
	}
	printf("\n");
	return ;
}
 /******打印表中local位置元素内容******/
void Local(ListHead* Head,int local)
{
	if(Head->Length<local && local<1)
	{
		printf("警告！不存在%d位置的元素\n",local);
		return ;
	}
	Liststruct *p=Head->next;
	int i=1;
	while(p && i++!=local)
		p=p->next;
	printf("%c\n",p->book);
	return ;
}

/******找到表中出现的字符ch的位置******/
void DATA_find(ListHead* Head,char ch)
{
	int i=1,flag=0,count=1;
	Liststruct *p=Head->next;
	while(p)
	{
		if(p->book==ch)
		{
			flag=1;
			printf("%d.在第%d个位置出现元素%c\n",count++,i,ch);
		}
		p=p->next;
		i++;
	}
	if(!flag)
		printf("未能找到%c元素！\n",ch);
	return ;
}

/******在第k个元素前插入一个元素******/
void DATA_Insert(ListHead *Head,int k,Excelelem ch)
{
	if(Head->Length<k && k<1)
	{
		printf("警告！不存在%d位置的元素\n",k);
		return ;
	}
	Liststruct *p=Head->next,*q,*t;
	int i=1;
	while(p && i++!=k)
		t=p,p=p->next;
	q=(Liststruct *)malloc(sizeof(Liststruct));
	q->book=ch;
	if(k==1)
	{
		Head->next=q;
		q->next=p;
	}
	else
	{
		q->next=p;
		t->next=q;
	}
	Head->Length++;
	return ;
}

/******删除第k个元素******/
void DATA_Delete(ListHead *Head,int k)
{
	if(Head->Length<k && k<1)
	{
		printf("警告！不存在%d位置的元素\n",k);
		return ;
	}
	int i=1;
	Liststruct *p=Head->next,*q;
	while(p && i++!=k)
		q=p,p=p->next;
	if(k==1)
		Head->next=p->next;
	else
		q->next=p->next;
	free(p);
	Head->Length--;
	return ;
}

/******逆置链表******/
void DATA_UN(ListHead *Head)
{
	Liststruct *p,*q;
	p=Head->next;
	Head->next=NULL;
	while(p!=NULL)
	{
		q=p;
		p=p->next;
		q->next=Head->next;
		Head->next=q;
	}
	return ;
}

/******返还内存******/
void List_FREE(ListHead *Head)
{
	Liststruct *p=Head->next,*q;
	free(Head);
	while(p)
	{
		q=p;
		p=p->next;
		free(q);
	}
	return ;
}

int main()
{
	ListHead *Head;
	Numelem i;
	Excelelem ch;
	puts("");
	puts("******等待链表Head初始化!******");
	Head=Headinit();
	puts("******链表Head初始化完成!******");
	printf("链表中的内容为:\n");
	DATA_cout(Head);
	printf("链表Head的长度为:\n");
	printf("%d\n",Head->Length);
	printf("链表第%d个元素是:\n",i=2);
	Local(Head,i);
	printf("链表中出现%c元素的位置分别是:\n",ch='6');
	DATA_find(Head,ch);
	printf("在链表的第%d个元素之前插上%c\n",i=4,ch='9');
	DATA_Insert(Head,i,ch);
	printf("链表中的内容为:\n");
	DATA_cout(Head);
	printf("将链表中第%d个元素删除\n",i=3);
	DATA_Delete(Head,i);
	printf("链表中的内容为:\n");
	DATA_cout(Head);
	printf("将链表所有元素逆置，请稍后...\n\n");  //多种方法
	DATA_UN(Head);
	printf("链表中的内容为:\n");
	DATA_cout(Head);
	puts("******链表Head使用完毕!******\n");
	List_FREE(Head);
	return 0;
}

