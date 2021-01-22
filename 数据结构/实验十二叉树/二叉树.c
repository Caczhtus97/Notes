#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

//******宏定义参数******
#define NO 0
#define OK 1
#define EORRO 0

//******定义数据类型别名******
typedef char ElemType;
typedef int Status;

//******声明数据结构******
typedef struct TNode
{
	ElemType data;
	struct TNode *lchild;
	struct TNode *rchild;
}BinaryTree,*BiTreePoint;

typedef struct SNode
{
	BiTreePoint *data;
	struct SNode *next;
}StackNode,*StackPoint;

typedef struct
{
	int StackSize;
	StackPoint base;
	StackPoint top;
}StackHead,*StackHeadPoint;

typedef struct QNode
{
	BiTreePoint *data;
	struct QNode *next;
}QueueNode,*QueuePoint;

typedef struct
{
	int QueueSize;
	QueuePoint front;
	QueuePoint rear;
}QueueHead,*QueueHeadPoint;

//******以下为链栈的数据结构操作******
StackHeadPoint InitStack()
{
	StackHeadPoint Head=(StackHeadPoint)malloc(sizeof(StackHead));
	Head->StackSize=0;
	Head->base=Head->top=(StackPoint)malloc(sizeof(StackNode));
	return Head;
}

Status StackEmpty(StackHeadPoint Head)
{
	if(Head->base == Head->top)
		return OK;
	return NO;
}

BiTreePoint* getTop(StackHeadPoint *Head)
{
	if(StackEmpty(*Head))
		return NULL;
	return (*Head)->top->next->data;
}

Status StackPush(StackHeadPoint *Head,BiTreePoint *data)
{
	StackPoint p=(StackPoint)malloc(sizeof(StackNode));
	if(p==NULL)
	{
		printf("对不起，系统内存不足!入栈失败!\n");
		return NO;
	}
	(*Head)->top->data=data;
	p->next=(*Head)->top;
	(*Head)->top=p;
	(*Head)->StackSize++;
	return OK;
}

Status StackPop(StackHeadPoint *Head)
{
	StackPoint p=(*Head)->top;
	if(StackEmpty(*Head))
		return NO;
	(*Head)->top=p->next;
	(*Head)->StackSize--;
	free(p);
	return OK;
}

Status StackDelete(StackHeadPoint *Head)
{
	while(!StackEmpty(*Head))
		StackPop(Head);
	free((*Head)->base);
	return OK;
}
//******以上为链栈数据结构操作******

//******以下为链队列数据结构操作******
QueueHeadPoint InitQueue()
{
	QueueHeadPoint Head=(QueueHeadPoint)malloc(sizeof(QueueHead));
	Head->QueueSize=0;
	Head->front=Head->rear=(QueuePoint)malloc(sizeof(QueueNode));
	Head->rear->next=NULL;
	return Head;
}

Status QueueEmpty(QueueHeadPoint Head)
{
	if(Head->front == Head->rear)
		return OK;
	return NO;
}

BiTreePoint* getFront(QueueHeadPoint *Head)
{
	if(QueueEmpty(*Head))
		return NULL;
	return (*Head)->front->next->data;
}

Status QueuePush(QueueHeadPoint *Head,BiTreePoint *data)
{
	QueuePoint p=(QueuePoint)malloc(sizeof(QueueNode));
	if(p==NULL)
	{
		printf("对不起，系统内存不足!入栈失败!\n");
		return NO;
	}
	p->data=data;
	p->next=(*Head)->rear->next;
	(*Head)->rear->next=p;
	(*Head)->rear=p;
	(*Head)->QueueSize++;
	return OK;
}

Status QueuePop(QueueHeadPoint *Head)
{
	QueuePoint p=(*Head)->front;
	if(QueueEmpty(*Head))
		return NO;
	(*Head)->front=p->next;
	(*Head)->QueueSize--;
	free(p);
	return OK;
}

Status QueueDelete(QueueHeadPoint *Head)
{
	while(!QueueEmpty(*Head))
		QueuePop(Head);
	free((*Head)->front);
	return OK;
}
//******以上为链队列数据结构操作******

//******以下为二叉树数据结构操作******
BiTreePoint InitBiTree()
{
	return NULL;
}

Status BiTreeEmpty(BiTreePoint T)
{
	if(T==NULL)
		return OK;
	return NO;
}

BiTreePoint CreatBiTree()  //非递归先序构造二叉树
{
	BiTreePoint *temp,T;
	ElemType ch;
	StackHeadPoint Head=InitStack();
	temp=&T;
	do
	{
		ch=getchar();
		if(ch=='^')
			(*temp)=NULL;
		else
		{
			(*temp)=(BiTreePoint)malloc(sizeof(BinaryTree));
			if(*temp==NULL)
			{
				printf("对不起,系统内存不足,子树构造失败,请扩容!\n");
				system("pause");
			}
			(*temp)->data=ch;
			StackPush(&Head,&(*temp)->rchild);
			StackPush(&Head,&(*temp)->lchild);
		}
		temp=getTop(&Head);
	}while(!StackEmpty(Head) && StackPop(&Head));
	StackDelete(&Head);
	return T;
}

Status PreOrderTraverse(BiTreePoint T) //非递归先序遍历方法
{
	BiTreePoint *temp;
	StackHeadPoint Head=InitStack();
	temp=&T;
	while(*temp || !StackEmpty(Head))
	{
		if(*temp)
		{
			printf("%c",(*temp)->data);
			if(!StackPush(&Head,temp))
			{
				printf("对不起,当前系统内存不足,二叉树遍历失败!\n");
				return NO;
			}
			temp=&(*temp)->lchild;
		}
		else
		{
			temp=getTop(&Head);
			StackPop(&Head);
			temp=&(*temp)->rchild;
		}
	}
	StackDelete(&Head);
	printf("\n");
	return OK;
}

Status InOrderTraverse(BiTreePoint T) //非递归中序遍历方法
{
	BiTreePoint *temp;
	StackHeadPoint Head=InitStack();
	temp=&T;
	while(*temp || !StackEmpty(Head))
	{
		if(*temp)
		{
			if(!StackPush(&Head,temp))
			{
				printf("对不起,当前系统内存不足,二叉树遍历失败!\n");
				return NO;
			}
			temp=&(*temp)->lchild;
		}
		else
		{
   			temp=getTop(&Head);
			printf("%c",(*temp)->data);
  			StackPop(&Head);
			temp=&(*temp)->rchild;
		}
	}
	StackDelete(&Head);
	printf("\n");
	return OK;
}

Status PostOrderTraverse(BiTreePoint T)  //非递归后序遍历方法
{
	BiTreePoint *temp;
	Status flag=1;
	StackHeadPoint Head=InitStack();
	if(T==NULL || !StackPush(&Head,&T))
	{
		printf("\n");
		return OK;
	}
	temp=&T->lchild;
	while(!StackEmpty(Head))
	{
		if(*temp && flag)
		{
  			if(!StackPush(&Head,temp))
			{
				printf("对不起,当前系统内存不足,二叉树遍历失败!\n");
				return NO;
			}
			temp=&(*temp)->lchild;
		}
		else if(temp==&(*(getTop(&Head)))->lchild)
		{
			temp=&(*(getTop(&Head)))->rchild;
			flag=1;
		}
		else
		{
			temp=getTop(&Head);
			StackPop(&Head);
			printf("%c",(*temp)->data);
			while(temp!=&T && temp==&(*(getTop(&Head)))->rchild)
			{
				temp=getTop(&Head);
				StackPop(&Head);
				printf("%c",(*temp)->data);
			}
			flag=0;
		}
	}
	StackDelete(&Head);
	printf("\n");
	return OK;
}

Status PostOrderTraverse2(BiTreePoint T) //非递归后序遍历方法2
{
	BiTreePoint *temp,*before;
	StackHeadPoint Head=InitStack();
	if(T==NULL || !StackPush(&Head,&T))
	{
		printf("\n");
		return OK;
	}
	before=NULL;
	while(!StackEmpty(Head))
	{
		temp=getTop(&Head);
		if( (*temp)->lchild==NULL && (*temp)->rchild==NULL || before && (before==&(*temp)->lchild || before==&(*temp)->rchild) )
		{
			printf("%c",(*temp)->data);
			StackPop(&Head);
			before=temp;
		}
		else
		{
			if((*temp)->rchild)
			{
				if(!StackPush(&Head,&(*temp)->rchild))
				{
					printf("对不起,当前系统内存不足,二叉树遍历失败!\n");
					return NO;
				}
			}
			if((*temp)->lchild)
			{
				if(!StackPush(&Head,&(*temp)->lchild))
				{
					printf("对不起,当前系统内存不足,二叉树遍历失败!\n");
					return NO;
				}
			}
		}
	}
	StackDelete(&Head);
	printf("\n");
	return OK;
}

Status LevelOrderTraverse(BiTreePoint T) //按层遍历方法
{
	BiTreePoint *temp;
	QueueHeadPoint Head=InitQueue();
	if(T==NULL || !QueuePush(&Head,&T))
	{
		printf("\n");
		return OK;
	}
	while(!QueueEmpty(Head))
	{
		temp=getFront(&Head);
		QueuePop(&Head);
		printf("%c",(*temp)->data);
		if((*temp)->lchild)
		{
			if(!QueuePush(&Head,&(*temp)->lchild))
			{
				printf("对不起,当前系统内存不足,二叉树遍历失败!\n");
					return NO;
			}
		}
		if((*temp)->rchild)
		{
			if(!QueuePush(&Head,&(*temp)->rchild))
			{
				printf("对不起,当前系统内存不足,二叉树遍历失败!\n");
				return NO;
			}
		}
	}
	QueueDelete(&Head);
	printf("\n");
	return OK;
}

int MAX(int a,int b)
{
	return a>b?a:b;
}

int CountBiTreeDep(BiTreePoint T)
{
 	if(T==NULL)
		return 0;
	return MAX(CountBiTreeDep(T->lchild),CountBiTreeDep(T->rchild))+1;
}

int CountBiTreeleaf(BiTreePoint T)
{
	if(T==NULL)
		return 0;
	else if(T->lchild==NULL && T->rchild==NULL)
		return 1;
	return CountBiTreeleaf(T->rchild)+CountBiTreeleaf(T->lchild);
}
//******以上为二叉树数据结构操作******

int main()
{
	BiTreePoint T;
	printf("请先序构建二叉树(^:表示空,换行表示结点一个输入完毕!):\n");
	T=CreatBiTree();
    printf("该树的先序遍历为:\n");
	PreOrderTraverse(T);
	printf("该树的中序遍历为:\n");
	InOrderTraverse(T);
	printf("该树的后序遍历为:\n");
	PostOrderTraverse(T);
	printf("该树的后序序遍历2为:\n");
	PostOrderTraverse2(T);
	printf("该树的按层遍历为:\n");
	LevelOrderTraverse(T);
	printf("该树的深度为:\n");
	printf("%d\n",CountBiTreeDep(T));
	printf("该树的叶子个数为:\n");
	printf("%d\n",CountBiTreeleaf(T));
	return 0;
}
