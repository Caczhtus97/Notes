#include<stdio.h>
#include<stdlib.h>

//******�궨���������******
#define DATA_SIZE 200
#define EXTEND_DATA_SIZE 50
#define NO 0
#define OK 1
#define ERROR -1

//******�����������ͱ���******
typedef int Status;
typedef char Excelelem;
typedef int Numelem;

//******˳������ݽṹ******
typedef struct
{
	Excelelem *book;
	Numelem Lenght;
	Numelem Listsize;
}Liststruct;

//******��ʼ��˳���******
Liststruct* init()
{
	Liststruct* Head;
	Head=(Liststruct *)malloc(sizeof(Liststruct));
	Head->book=(Excelelem *)malloc(DATA_SIZE*sizeof(Excelelem));
	if(Head==NULL)
		printf("�ڴ�����ʧ�ܣ�\n");
	else
	{
		Head->Listsize=DATA_SIZE;
		Head->Lenght=0;
	}
	return Head;
}

/******��չ˳���******/
Status Extend(Liststruct *Head)
{
	Liststruct *p;
	int size=Head->Listsize;
	p=(Liststruct *)realloc(Head,EXTEND_DATA_SIZE*sizeof(Excelelem));
	if(p==NULL)
	{
		printf("��̬�ڴ�����ʧ�ܣ�\n");
		return NO;
	}
	else
	{
		Head=p;
		Head->Listsize=size+EXTEND_DATA_SIZE;
	}
	return OK;
}

/******ѹ������******/
void DATA_cin(Liststruct *Head)
{
	Excelelem ch;
	Numelem Length=0;
	while((ch=getchar())!='\n')
	{
		if(Head->Listsize<Length)
		{
			if(!Extend(Head))  //�ڴ�����ʧ�����ݶ����ֹ
				break;
		}
		Head->book[Length++]=ch;
	}
	Head->Lenght=Length;
	return ;
}

/******��ӡ������������******/
void DATA_cout(Liststruct *Head)
{
	int i;
	for(i=0;i<Head->Lenght;i++)
		printf("%c",Head->book[i]);
	printf("\n");
	return ;
}
 /******��ӡ����localλ��Ԫ������******/
void Local(Liststruct* Head,int local)
{
	if(Head->Lenght<local && local<1)
	{
		printf("���棡������%dλ�õ�Ԫ��\n",local);
		return ;
	}
	printf("%c\n",Head->book[local-1]);
	return ;
}

/******�ҵ����г��ֵ��ַ�ch����λ��******/
Status DATA_find(Liststruct* Head,char ch)
{
	int i;
	for(i=0;i<Head->Lenght;i++)
		if(ch==Head->book[i])
			break;
	if(i==Head->Lenght)
	{
		printf("δ���ҵ�����ҪԪ�ص�λ�ã�\n");
		return NO;
	}
	return i+1;
}

/******�ڵ�k��Ԫ��ǰ����һ��Ԫ��******/
void DATA_Insert(Liststruct *Head,int k,Excelelem ch)
{
	if(Head->Lenght<k && k<1)
	{
		printf("���棡������%dλ�õ�Ԫ��\n",k);
		return ;
	}
	int i;
	for(i=Head->Lenght;i>=k;i--)
		Head->book[i]=Head->book[i-1];
	Head->book[k-1]=ch;
	Head->Lenght++;
	return ;
}

/******ɾ����k��Ԫ��******/
void DATA_Delete(Liststruct *Head,int k)
{
	if(Head->Lenght<k && k<1)
	{
		printf("���棡������%dλ�õ�Ԫ��\n",k);
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
	puts("******�ȴ�˳���Head��ʼ��!******");
	Head=init();
	puts("******˳���Head��ʼ�����!******");
	printf("������˳���Head������:\n");
	DATA_cin(Head);
	printf("˳����е�����Ϊ:\n");
	DATA_cout(Head);
	printf("˳���Head�ĳ���Ϊ:\n");
	printf("%d\n",Head->Lenght);
	printf("˳����%d��Ԫ����:\n",i=2);
	Local(Head,i);
	printf("˳����г���%cԪ�صĵ�һ��λ����:\n",ch='6');
	i=DATA_find(Head,ch);
	if(i) printf("%d\n",i);
	printf("���ڵ�%d��Ԫ��֮ǰ����%c\n",i=4,ch='f');
	DATA_Insert(Head,i,ch);
	printf("˳����е�����Ϊ:\n");
	DATA_cout(Head);
	printf("�뽫˳����е�%d��Ԫ��ɾ��\n",i=3);
	DATA_Delete(Head,i);
	printf("˳����е�����Ϊ:\n");
	DATA_cout(Head);
	puts("******˳���Headʹ�����!******\n");
	free(Head->book);
	free(Head);
	return 0;
}
