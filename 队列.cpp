#include<iostream>
using namespace std;
#define Maxsize 50

typedef int ElemType;

//顺序队
typedef struct{
	ElemType data[Maxsize];
	int front,rear;
}SqQueue;

void InitQueue(SqQueue *&q)
{
	q = new SqQueue;
	q->front = q->rear = -1;
}

void DestroyQueue(SqQueue *&q)
{
	delete q;
}

bool QueueEmpty(SqQueue *q)
{
	return q->front == q->rear;
}

bool enQueue(SqQueue *&q,ElemType e)
{
	if(q->rear == Maxsize - 1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(SqQueue *&q,ElemType &e)
{
	if(QueueEmpty(q))
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}



////环形队列1,已知front和rear
//typedef struct{
//	ElemType data[Maxsize];
//	int front,rear;
//}SqQueue;
//
//void InitQueue(SqQueue *&q)
//{
//	q = new SqQueue;
//	q->front = q->rear = 0;
//}
//
//void DestroyQueue(SqQueue *&q)
//{
//	delete q;
//}
//
//bool QueueEmpty(SqQueue *q)
//{
//	return q->front == q->rear;
//}
//
//bool enQueue(SqQueue *&q,ElemType e)
//{
//	if((q->rear+1) % Maxsize == q->front)
//		return false;
//	q->rear = (q->rear + 1) % Maxsize;
//	q->data[q->rear] = e;
//	return true;
//}
//
//bool deQueue(SqQueue *&q,ElemType &e)
//{
//	if(QueueEmpty(q))
//		return false;
//	q->front = (q->front + 1) % Maxsize;
//	e = q->data[q->front];
//	return true;
//}
//
//int Count(SqQueue *q)
//{
//	return (q->rear - q->front + Maxsize) % Maxsize;
//}



////环形队列2，已知front和count
//typedef struct
//{
//	ElemType data[Maxsize];
//	int front,count;
//}QuType;
//
//void InitQueue(QuType *&q)
//{
//	q = new QuType;
//	q->front = q->count = 0;
//}
//
//void DestroyQueue(QuType *&q)
//{
//	delete q;
//}
//
//bool QueueEmpty(QuType *q)
//{
//	return q->count == 0;
//}
//
//bool enQueue(QuType *&q,ElemType e)
//{
//	int rear;
//	if(q->count == Maxsize)
//		return false;
//	rear = (q->front + q->count) % Maxsize;
//	rear = (rear + 1) % Maxsize;
//	q->data[rear] = e;
//	q->count++;
//	return true;
//}
//
//bool deQueue(QuType *&q,ElemType &e)
//{
//	if(q->count == 0)
//		return false;
//	q->front = (q->front + 1) % Maxsize;
//	e = q->data[q->front];
//	q->count--;
//	return true;
//}



////链队
//typedef struct qnode{
//	ElemType data;
//	struct qnode* next;
//}DataNode;
//typedef struct{
//	DataNode* front;
//	DataNode* rear;
//}LinkQuNode;
//
//void InitQueue(LinkQuNode *&q)
//{
//	q = new LinkQuNode;
//	q->front = q->rear = NULL;
//}
//
//void DestroyQueue(LinkQuNode *&q)
//{
//	DataNode *pre = q->front,*p;
//	if(pre != NULL)
//	{
//		p = pre->next;
//		while(p != NULL)
//		{
//			delete pre;
//			pre = p;
//			p = p->next;
//		}
//		delete pre;
//	}
//	delete q;
//}
//
//bool QueueEmpty(LinkQuNode *q)
//{
//	return  q->rear == NULL;
//}
//
//bool enQueue(LinkQuNode *&q,ElemType e)
//{
//	DataNode *p;
//	p->data = e;
//	p->next = NULL;
//	if(q->rear == NULL)
//		q->front = q->rear = p;
//	else
//	{
//		q->rear->next = p;
//		q->rear = p;
//	}
//	return true;
//}
//
//bool deQueue(LinkQuNode *&q,ElemType &e)
//{
//	DataNode *t;
//	if(q->rear == NULL)
//		return false;
//	t = q->front;
//	if(q->front == q->rear)
//		q->front = q->rear = NULL;
//	else
//		q->front = q->front->next;
//	e = t->data;
//	delete t;
//	return true;
//}



////链队（只有一个尾指针rear）
//typedef struct Linknode{
//	ElemType data;
//	Linknode *next;
//}LinkNode;
//
//void InitQueue(LinkNode *&rear)
//{
//	rear = NULL;
//}
//
//bool enQueue(LinkNode *&rear,ElemType e)
//{
//	LinkNode *p;
//	p = new LinkNode;
//	p->data = e;
//	if(rear == NULL)
//	{
//		p->next = p;
//		rear = p;
//	}
//	else
//	{
//		p->next = rear->next;
//		rear->next = p;
//		rear = p;
//	}
//	return true;
//}
//
//bool deQueue(LinkNode *&rear,ElemType &e)
//{
//	LinkNode *t;
//	if(rear == NULL)
//		return false;
//	if(rear->next == rear)
//	{
//		e = rear->data;
//		delete rear;
//		rear = NULL;
//	}
//	else
//	{
//		t = rear->next;
//		e = t->data;
//		rear->next = t->next;
//		delete t;
//	}
//	return true;
//}
//
//bool QueueEmpty(LinkNode *rear)
//{
//	return rear == NULL;
//}

void number(int n)
{
	ElemType e;
	SqQueue *q;
	InitQueue(q);
	for(int i=1;i<=n;++i)
		enQueue(q,i);
	cout << "出列顺序：" ;
	while(!QueueEmpty(q))
	{
		deQueue(q,e);
		cout << e << " " ;
		if(!QueueEmpty(q))
		{
			deQueue(q,e);
			enQueue(q,e);
		}
	}
	cout << endl;
	DestroyQueue(q);
}


int main()
{
	int n;
	cout << "请输入队列的长度：" ;
	cin >> n;
	cout << "初始序列：" ;
	for(int i=1;i<=n;++i)
		cout << i << " ";
	cout << endl;
	number(n);
}
