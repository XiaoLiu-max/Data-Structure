#include<iostream>
using namespace std;
typedef int KeyType;
typedef int InfoType;

typedef struct node
{
	KeyType key;
	InfoType data;
	node *lchild,*rchild;
}BSTNode;

BSTNode* InsertBST(BSTNode *bt,KeyType k)    //二叉排序树的插入
{
	if(bt == NULL)
	{
		bt = new BSTNode;
		bt->key = k;
		bt->lchild = bt->rchild = NULL;
	}
	else
	{
		if(k < bt->key)
			bt->lchild = InsertBST(bt->lchild,k);
		else
		{
			if(k > bt->key)
				bt->rchild = InsertBST(bt->rchild,k);
		}
	}
	return bt;
}

BSTNode* CreateBST(KeyType a[],int n)         //二叉排序树的创建
{
	BSTNode *bt = NULL;
	for(int i=0;i<n;++i)
		bt = InsertBST(bt,a[i]);
	return bt;
}

void InOrder(BSTNode *b)
{
	if(b != NULL)
	{
		InOrder(b->lchild);
		cout << b->key << " ";
		InOrder(b->rchild);
	}
}

BSTNode* SearchBST(BSTNode *bt,KeyType k)     //二叉排序树的查找（递归）
{
	if(bt == NULL || bt->key == k)
		return bt;
	if(k < bt->key)
		return SearchBST(bt->lchild,k);
	else
	{
		if(k > bt->key)
			return SearchBST(bt->rchild,k);
	}
}

BSTNode* SearchBST1(BSTNode *bt,KeyType k)     //二叉排序树的查找（非递归）
{
	BSTNode *p = bt;
	while(p != NULL)
	{
		if(k == p->key) break;
		if(k < p->key)
			p = p->lchild;
		else
			p = p->rchild;
	}
	return bt;
}

BSTNode* DeleteBST(BSTNode *bt,KeyType k)     //二叉排序树的删除
{
	if(bt == NULL) return NULL;
	BSTNode *p = bt,*f = NULL;
	while(p != NULL)            //查找k结点
	{
		if(p->key == k) break;
		f = p;
		if(k < p->key)
			p = p->lchild;
		else
			p = p->rchild;
	}
	if(p == NULL) return bt;
	if(p->lchild == NULL && p->rchild == NULL)    //结点p是叶子结点
	{
		if(f == NULL)
			bt = NULL;
		else
		{
			if(p == f->lchild)
				f->lchild = NULL;
			else
				f->rchild = NULL;
		}
		delete p;
	}
	else
	{
		if(p->rchild == NULL)   //结点p只有左子树
		{
			if(f == NULL)
				bt = bt->lchild;
			else
			{
				if(f->lchild == p)
					f->lchild = p->lchild;
				else
					f->rchild = p->lchild;
			}
			delete p;
		}
		else
		{
			if(p->lchild == NULL)         //结点p只有右子树
			{
				if(f == NULL)
					bt = bt->rchild;
				else
				{
					if(f->lchild == p)
						f->lchild = p->rchild;
					else
						f->rchild = p->rchild;
				}
				delete p;
			}
			else     //结点p有左、右孩子
			{
				BSTNode *q = p->rchild;
				f = p;
				while(q->lchild != NULL)
				{
					f = q;
					q = q->lchild;
				}
				p->key = q->key;
				if(f->lchild == q)
					f->lchild = q->rchild;
				else
					f->rchild = q->rchild;
				delete q;
			}
		}
	}
	return bt;
}

int main()
{
	int n;
	cout << "请输入二叉排序树的元素个数：";
	cin >> n;
	int Key[n];
	cout << "请输入二叉排序树的元素：" << endl;
	for(int i=0;i<n;++i)
		cin >> Key[i];
	BSTNode* bt = CreateBST(Key,n);
	int k;
	cout << "请输入要查找的元素值：" ;
	cin >> k;
	BSTNode *bt1 = SearchBST(bt,k);
	cout << (bt1 == NULL ? "未找到该元素" : "查找成功") << endl;
	cout << "请输入要删除的元素值：";
	cin >> k;
	cout << "删除之前的二叉排序树：（中序输出）" << endl;
	InOrder(bt);
	cout << endl;
	BSTNode *bt2 = DeleteBST(bt,k);
	cout << "删除之后的二叉排序树：（中序输出）" << endl;
	InOrder(bt2);
}
