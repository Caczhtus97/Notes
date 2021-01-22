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

//******顺序表数据结构******
typedef struct
{
	Excelelem *book;
	Numelem Lenght;
	Numelem Listsize;
}Liststruct;

//******初始化顺序表******
Liststruct* init()
{
	Liststruct* Head;
	Head=(Liststruct *)malloc(sizeof(Liststruct));
	Head->book=(Excelelem *)malloc(DATA_SIZE*sizeof(Excelelem));
	if(Head==NULL)
		printf("内存申请失败！\n");
	else
	{
		Head->Listsize=DATA_SIZE;
		Head->Lenght=0;
	}
	return Head;
}

/******拓展顺序表******/
Status Extend(Liststruct *Head)
{
	Liststruct *p;
	int size=Head->Listsize;
	p=(Liststruct *)realloc(Head,EXTEND_DATA_SIZE*sizeof(Excelelem));
	if(p==NULL)
	{
		printf("动态内存申请失败！\n");
		return NO;
	}
	else
	{
		Head=p;
		Head->Listsize=size+EXTEND_DATA_SIZE;
	}
	return OK;
}

/******压入数据******/
void DATA_cin(Liststruct *Head)
{
	Excelelem ch;
	Numelem Length=0;
	while((ch=getchar())!='\n')
	{
		if(Head->Listsize<Length)
		{
			if(!Extend(Head))  //内存申请失败数据读入截止
				break;
		}
		Head->book[Length++]=ch;
	}
	Head->Lenght=Length;
	return ;
}

/******打印表中数据内容******/
void DATA_cout(Liststruct *Head)
{
	int i;
	for(i=0;i<Head->Lenght;i++)
		printf("%c",Head->book[i]);
	printf("\n");
	return ;
}
 /******打印表中local位置元素内容******/
void Local(Liststruct* Head,int local)
{
	if(Head->Lenght<local && local<1)
	{
		printf("警告！不存在%d位置的元素\n",local);
		return ;
	}
	printf("%c\n",Head->book[local-1]);
	return ;
}

/******找到表中出现的字符ch的首位置******/
Status DATA_find(Liststruct* Head,char ch)
{
	int i;
	for(i=0;i<Head->Lenght;i++)
		if(ch==Head->book[i])
			break;
	if(i==Head->Lenght)
	{
		printf("未能找到您想要元素的位置！\n");
		return NO;
	}
	return i+1;
}

/******在第k个元素前插入一个元素******/
void DATA_Insert(Liststruct *Head,int k,Excelelem ch)
{
	if(Head->Lenght<k && k<1)
	{
		printf("警告！不存在%d位置的元素\n",k);
		return ;
	}
	int i;
	for(i=Head->Lenght;i>=k;i--)
		Head->book[i]=Head->book[i-1];
	Head->book[k-1]=ch;
	Head->Lenght++;
	return ;
}

/******删除第k个元素******/
void DATA_Delete(Liststruct *Head,int k)
{
	if(Head->Lenght<k && k<1)
	{
		printf("警告！不存在%d位置的元素\n",k);
		return ;
	}
	int i;
	for(i=k-1;i<Head->Lenght-1;i++)
		Head->book[i]=Head->book[i+1];
	Head->Lenght--;
	return ;
}

int main()
{
	Liststruct *Head;
	Numelem i;
	Excelelem ch;
	puts("");
	puts("******等待顺序表Head初始化!******");
	Head=init();
	puts("******顺序表Head初始化完成!******");
	printf("请输入顺序表Head的内容:\n");
	DATA_cin(Head);
	printf("顺序表中的内容为:\n");
	DATA_cout(Head);
	printf("顺序表Head的长度为:\n");
	printf("%d\n",Head->Lenght);
	printf("顺序表第%d个元素是:\n",i=2);
	Local(Head,i);
	printf("顺序表中出现%c元素的第一个位置在:\n",ch='6');
	i=DATA_find(Head,ch);
	if(i) printf("%d\n",i);
	printf("请在第%d个元素之前插上%c\n",i=4,ch='f');
	DATA_Insert(Head,i,ch);
	printf("顺序表中的内容为:\n");
	DATA_cout(Head);
	printf("请将顺序表中第%d个元素删除\n",i=3);
	DATA_Delete(Head,i);
	printf("顺序表中的内容为:\n");
	DATA_cout(Head);
	puts("******顺序表Head使用完毕!******\n");
	free(Head->book);
	free(Head);
	return 0;
}
