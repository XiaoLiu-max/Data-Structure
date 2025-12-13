#include<iostream>
#include<string>
#include<cmath>
using namespace std;
#define Maxsize 50
typedef char Elemtype;

typedef struct node
{
	Elemtype data;
	node *lchild;
	node *rchild;
}BTNode;

void DispBTree(BTNode *b)         //打印二叉树
{
	if(b != NULL)
	{
		cout << b->data;
		if(b->lchild != NULL || b->rchild != NULL)
		{
			cout << "(";
			DispBTree(b->lchild);
			if(b->rchild != NULL)
				cout << ",";
			DispBTree(b->rchild);
			cout << ")";
		}
	}
}

typedef Elemtype SqBTree[Maxsize+1];

//构造二叉树
BTNode *CreateBT1(char *pre,char *in,int n)               //先序和中序
{
	BTNode *b;
	char *p;int k;
	if(n<=0) return NULL;
	b = new BTNode;
	b->data = *pre;
	for(p=in;p<in+n;++p)
	{
		if(*p == *pre)
			break;
	}
	k = p - in;
	b->lchild = CreateBT1(pre+1,in,k);
	b->rchild = CreateBT1(pre+k+1,p+1,n-k-1);
	return b;
}

BTNode *CreateBT2(char *post,char *in,int n)    //后序和中序
{
	BTNode *b;
	b = new BTNode;
	char r,*p;
	int k;
	if(n<=0) return NULL;
	r = *(post+n-1);
	b->data = r;
	for(p=in;p<in+n;p++)
		if(*p == r)
			break;
	k =  p - in;
	b->lchild = CreateBT2(post,in,k);
	b->rchild = CreateBT2(post+k,p+1,n-k-1);
	return b;
}

BTNode *trans(SqBTree a,int i)    //顺序存储转化为链式存储
{
	BTNode *b;
	if(i>Maxsize) return NULL;
	if(a[i] == '#') return NULL;
	b = new BTNode;
	b->data = a[i];
	b->lchild = trans(a,2*i);
	b->rchild = trans(a,2*i+1);
	return b;
}

int main()
{
//	int n;
//	cout << "请输入二叉树的元素个数：";
//	cin >> n;
//	char pre[n+1],post[n+1],in[n+1];
////	cout << "请输入先序序列：";
////	for(int i=0;i<n;++i)
////		cin >> pre[i];
//	cout << "请输入后序序列：";
//	for(int i=0;i<n;++i)
//		cin >> post[i];
//	cout << "请输入中序序列：";
//	for(int i=0;i<n;++i)
//		cin >> in[i];
//	cout << "所构造的二叉树为：";
////	DispBTree(CreateBT1(pre,in,n));
//	DispBTree(CreateBT2(post,in,n));
	int n;
	cout << "请输入二叉树的高度：";
	cin >> n;
	cout << "顺序存储转化为链式存储：" << endl;
	SqBTree t;
	cout << "请输入二叉树元素：";
	for(int i=1;i<=pow(2,n)-1;++i)           //注意空为'#'
		cin >> t[i];
	cout << "打印二叉树：";
	DispBTree(trans(t,1));
}
