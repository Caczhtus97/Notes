#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define NO 0

typedef int Status;
typedef int ElemType;

typedef struct
{
	ElemType *Table;
	int length;
}List,*ListPoint;

Status Init(ListPoint Head)
{
	Head->Table=(ElemType *)malloc((Head->length+1)*sizeof(ElemType));
	if(Head->Table == NULL)
		return NO;
	return OK;
}

void Data_In(ListPoint Head)
{
	int i;
	for(i=1;i<=Head->length;i++)
		scanf("%d",&Head->Table[i]);
}

int Search_Seq(ListPoint Head,ElemType Key)
{
	int i;
	Head->Table[0]=Key;
	for(i=Head->length;Key!=Head->Table[i];i--) ;
	return i;
}

int Search_Bin(ListPoint Head,ElemType Key)
{
	int left,right,mid;
	left=1;  right=Head->length;
	while(left<=right)
	{
		mid=(left+right)/2;
		if(Key==Head->Table[mid])
			return mid;
		else if(Key>Head->Table[mid])
			left=mid+1;
		else
			right=mid-1;
	}
	return 0;
}

int main()
{
	int flag;
	ElemType Key;
	List Tb,Tc;
	if(Init(&Tb))
	{
		puts("�������ĳ���:");
		scanf("%d",&Tb.length);
		Data_In(&Tb);
		puts("��������Ҫ���ҵ�Key:");
		scanf("%d",&Key);
		puts("��Ԫ�����ڵ�λ��Ϊ:");
		flag=Search_Seq(&Tb,Key);
		if(flag)
			printf("%d\n",flag);
		else
			puts("�����ڸ�Ԫ��!");
	}
	puts("");
	if(Init(&Tc))
	{
		puts("�������ĳ���:");
		scanf("%d",&Tc.length);
		Data_In(&Tc);
		puts("��������Ҫ���ҵ�Key:");
		scanf("%d",&Key);
		puts("��Ԫ�����ڵ�λ��Ϊ:");
		flag=Search_Seq(&Tc,Key);
		if(flag)
			printf("%d\n",flag);
		else
			puts("�����ڸ�Ԫ��!");
	}
	free(Tc.Table);
	free(Tb.Table);
	return 0;
}

/*
input1:
10
3 6 2 10 1 8 5 7 4 9
5
input2:
10
1 2 3 4 5 6 7 8 9 10
9
*/
