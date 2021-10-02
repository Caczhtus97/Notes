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
		puts("请输入表的长度:");
		scanf("%d",&Tb.length);
		Data_In(&Tb);
		puts("请输入您要查找的Key:");
		scanf("%d",&Key);
		puts("该元素所在的位置为:");
		flag=Search_Seq(&Tb,Key);
		if(flag)
			printf("%d\n",flag);
		else
			puts("不存在该元素!");
	}
	puts("");
	if(Init(&Tc))
	{
		puts("请输入表的长度:");
		scanf("%d",&Tc.length);
		Data_In(&Tc);
		puts("请输入您要查找的Key:");
		scanf("%d",&Key);
		puts("该元素所在的位置为:");
		flag=Search_Seq(&Tc,Key);
		if(flag)
			printf("%d\n",flag);
		else
			puts("不存在该元素!");
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
