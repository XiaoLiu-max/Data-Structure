#include<iostream>
using namespace std;

typedef int ElemType;

typedef struct LinkNode
{
	ElemType data;
	LinkNode *next;
}LinkNode;

void CreateList1(LinkNode *&L,ElemType a[],int n)          //头插法
{
	LinkNode *s;
	L = new LinkNode;
	L->next = NULL;
	for(int i=0;i<n;++i)
	{
		s = new LinkNode;
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

void CreateList2(LinkNode *&L,ElemType a[],int n)          //尾插法
{
	LinkNode *s,*r;
	L = new LinkNode;
	L->next = NULL;
	r = L;
	for(int i=0;i<n;++i)
	{
		s = new LinkNode;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = NULL;
}

void InitList(LinkNode *&L)
{
	L = new LinkNode;
	L->next = NULL;
}

void PrintList(LinkNode *L)
{
	LinkNode *p = L->next;
	while(p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

void Reverse(LinkNode *&L)
{
	LinkNode *p = L->next,*q;
	L->next = NULL;
	while(p != NULL)
	{
		q = p->next;
		p->next = L->next;
		L->next = p;
		p = q;
	}
}

void split(LinkNode *&L,LinkNode *&L1,LinkNode *&L2)
{
//	L1 = new LinkNode; L1->next = nullptr;
//	L2 = new LinkNode; L2->next = nullptr;
//	LinkNode *p = L->next, *r1 = L1, *r2 = L2;
//	int idx = 1;
//	while (p != nullptr) {
//		LinkNode *s = new LinkNode;
//		s->data = p->data;
//		s->next = nullptr;
//		if (idx % 2 == 1) {
//			r1->next = s;
//			r1 = s;
//		} else {
//			r2->next = s;
//			r2 = s;
//		}
//		p = p->next;
//		idx++;
//	}
	
	L1 = L;
	LinkNode *p = L1->next,*q,*r1;
	r1 = L1;
	L2 = new LinkNode;
	L2->next = NULL;
	while(p != NULL && p->next)
	{
		r1->next = p;
		r1 = p;
		p = p->next;
		q = p->next;
		p->next = L2->next;
		L2->next = p;
		p = q;
	}
	r1->next = NULL;
	
//	L1 = L; // 公用头结点
//	L2 = new LinkNode;
//	L2->next = nullptr;
//	LinkNode *p = L1->next, *r2 = L2, *q;
//	while (p && p->next) {
//		q = p->next;
//		p->next = q->next; // 奇数节点跳过偶数节点
//		r2->next = q;      // 偶数节点挂到L2
//		r2 = q;
//		r2->next = nullptr;
//		p = p->next;
//	}
}

void delmaxnode(LinkNode *&L)
{
	LinkNode *p = L->next,*pre = L,*maxp = p,*maxpre = pre;
	while(p != NULL)
	{
		if(maxp->data < p->data)
		{
			maxp = p;
			maxpre = pre;
		}
		pre = p;
		p = p->next;
	}
	maxpre->next = maxp->next;
	delete maxp;
}

void Sort(LinkNode *&L)
{
	LinkNode *p = L->next->next,*q,*pre;
	L->next->next = NULL;
	while(p != NULL)
	{
		q = p->next;
		pre = L;
		while(pre->next != NULL && pre->next->data < p->data)
			pre = pre->next;
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
}

int main()
{
	LinkNode *M,*L1,*L2;
	InitList(M);
	int length,choice;
	cout << "请输入单链表初始长度：" ;
	cin >> length;
	ElemType arr[length];
	cout << "请输入链表元素：";
	for(int i=0;i<length;++i)
		cin >> arr[i];
	CreateList2(M,arr,length);
	do
	{
		cout << "\n菜单"<< endl;
		cout << "1.打印链表" << endl;
		cout << "2.实现链表逆序" << endl;
		cout << "3.将链表分装为两个子链表" << endl;
		cout << "4.删除元素值最大的节点" << endl;
		cout << "5.递增排序" << endl;
		cout << "6.退出" << endl;
		cin >> choice;
		switch(choice)
		{
		case 1:
			PrintList(M);
			break;
		case 2:
			Reverse(M);
			PrintList(M);
			break;
		case 3:
			split(M,L1,L2);
			PrintList(L1);PrintList(L2);
			break;
		case 4:
			delmaxnode(M);
			PrintList(M);
			break;
		case 5:
			Sort(M);
			PrintList(M);
			break;
		default:
			cout << "输入无效,请重新输入！" << endl;
		}
	}while(choice != 6);
}
