#include<iostream>
#include<cstring>
using namespace std;
#define Maxsize 100

typedef struct
{
	char data[Maxsize];
	int length;
}SqString;

void StrAssign(SqString& s,const char* str)
{
	int i=0;
	while(str[i] != '\0' && i<Maxsize)
	{
		s.data[i] = str[i];
		++i;
	}
	s.length = i;
}

void Destroy(SqString& s)
{
	s.length = 0;
}

void StrCopy(SqString& s,SqString str)
{
	for(int i=0;i<str.length;++i)
	{
		s.data[i] = str.data[i];
	}
	s.length = str.length;
}

bool StrEqual(SqString s,SqString t)
{
	if(s.length != t.length)
		return false;
	for(int i=0;i<s.length;++i)
	{
		if(s.data[i] != t.data[i])
			return false;
	}
	return true;
}

int StrLength(SqString s)
{
	return s.length;
}

SqString Concat(SqString s,SqString t)
{
	SqString str;
	int i;
	for(i=0;i<s.length;++i)
		str.data[i] = s.data[i];
	for(int j=0;j<t.length;++j)
	{
		str.data[i+j] = t.data[j];
	}
	str.length = s.length + t.length;
	return str;
}

SqString SubStr(SqString s,int i,int j)
{
	SqString str;
	str.length = 0;
	if(i<1 || i>s.length || i+j-1>s.length || j<0)
		return str;
	for(int k=0;k<j;++k)
		str.data[k] = s.data[i+k-1];
	str.length = j;
	return str;
}

SqString Insert(SqString s1,int i,SqString s2)
{
	int j;
	SqString str;
	str.length = 0;
	if(i<1 || i>s1.length+1)
		return str;
	for(j=0;j<i-1;++j)
		str.data[j] = s1.data[j];
	for(j=0;j<s2.length;++j)
		str.data[i-1+j] = s2.data[j];
	for(j=i-1;j<s1.length;++j)
		str.data[j+s2.length] = s1.data[j];
	str.length = s1.length + s2.length;
	return str;
}

SqString DelStr(SqString s,int i,int j)
{
	SqString str;
	str.length = 0;
	if(i<1 || i>s.length || i+j-1>s.length || j<0)
		return str;
	for(int k=0;k<i-1;++k)
		str.data[k] = s.data[k];
	for(int k=i-1+j;k<s.length;++k)
		str.data[k-j] = s.data[k];
	str.length = s.length - j;
	return str;
}

SqString RepStr(SqString s,int i,int j,SqString t)
{
	SqString str;
	str.length = 0;
	if(i<1 || i>s.length || i+j-1>s.length || j<0)
		return str;
	for(int k=0;k<i-1;++k)
		str.data[k] = s.data[k];
	for(int k=0;k<t.length;++k)
		str.data[i-1+k] = t.data[k];
	for(int k=i-1+j;k<s.length;++k)
		str.data[t.length + k - j] = s.data[k];
	str.length = s.length + t.length - j;
	return str;
}

void DispStr(SqString s)
{
	for(int i=0;i<s.length;++i)
		cout << s.data[i];
	cout << endl;
}

int Strcmp(SqString s,SqString t)
{
	int same;
	same = s.length > t.length ? t.length : s.length;
	for(int i=0;i<same;++i)
	{
		if(s.data[i] > t.data[i])
			return 1;
		else
		{
			if(s.length < t.length)
				return -1;
		}
	}
	if(s.length == t.length)
		return 0;
	else
		return s.length > t.length ? 1 : -1;
}

int main()
{
	int choice;
	SqString s,t;
	do
	{
		cout << "\n菜单\n";
		cout << "1.初始化赋值" << endl;
		cout << "2.串复制" << endl;
		cout << "3.判断两个串是否相等" << endl;
		cout << "4.求串长" << endl;
		cout << "5.串连接" << endl;
		cout << "6.求子串" << endl;
		cout << "7.子串的插入" << endl;
		cout << "8.子串的删除" << endl;
		cout << "9.子串的替换" << endl;
		cout << "10.打印串" << endl;
		cout << "11.串的比较" << endl;
		cout << "0.退出" << endl;
		cout << "请选择对应功能：" ;
		cin >> choice;
		switch(choice)
		{
		case 1:
			{
				int n;
				cout << "请输入字符串长度：" ;
				cin >> n;
				char arr[n+1];
				cout << "请输入字符串：";
				for(int i=0;i<n;++i)
					cin >> arr[i];
				StrAssign(s,arr);
				cout << "赋值成功！" << endl;
				break;
			}
		case 2:
			{
				int n;
				cout << "请输入字符串长度：" ;
				cin >> n;
				char arr[n+1];
				cout << "请输入字符串：";
				for(int i=0;i<n;++i)
					cin >> arr[i];
				StrAssign(t,arr);
				StrCopy(s,t);
				cout << "复制成功！" << endl;
				DispStr(s);
				break;
			}
		case 3:
			{
				int n;
				cout << "请输入字符串长度：" ;
				cin >> n;
				char arr[n+1];
				cout << "请输入字符串：";
				for(int i=0;i<n;++i)
					cin >> arr[i];
				StrAssign(t,arr);
				cout << boolalpha << StrEqual(s,t) << endl;
				break;
			}
		case 4:
			cout << "串的长度为：" << StrLength(s) << endl;
		case 5:
			{
				int n;
				cout << "请输入字符串长度：" ;
				cin >> n;
				char arr[n+1];
				cout << "请输入字符串：";
				for(int i=0;i<n;++i)
					cin >> arr[i];
				StrAssign(t,arr);
				cout << "连接后的串：";
				DispStr(Concat(s,t));
				break;
			}
		case 6:
			{
				int i,j;
				cout << "请输入子串位置i和子串长度j：";
				cin >> i >> j;
				cout << "取出的子串为：";
				DispStr(SubStr(s,i,j));
				break;
			}
		case 7:
			{
				int n,i;
				cout << "请输入插入子串的位置：";
				cin >> i;
				cout << "请输入插入子串的长度：" ;
				cin >> n;
				char arr[n+1];
				cout << "请输入子串：";
				for(int i=0;i<n;++i)
					cin >> arr[i];
				StrAssign(t,arr);
				cout << "新子串：";
				DispStr(Insert(s,i,t));
				break;
			}
		case 8:
			{
				int i,j;
				cout << "请输入删除子串的初始位置和长度：";
				cin >> i >> j;
				cout << "删除后的新串：";
				DispStr(DelStr(s,i,j));
				break;
			}
		case 9:
			{
				int n,i,j;
				cout << "请输入替换的子串长度：" ;
				cin >> n;
				char arr[n+1];
				cout << "请输入子串：";
				for(int i=0;i<n;++i)
					cin >> arr[i];
				StrAssign(t,arr);
				cout << "请输入替换的位置和长度：";
				cin >> i >> j;
				cout << "替换后的新串：";
				DispStr(RepStr(s,i,j,t));
				break;
			}
		case 10:
			DispStr(s);
			break;
		case 11:
			{
				int n;
				cout << "请输入要比较串的长度：" ;
				cin >> n;
				char arr[n+1];
				cout << "请输入要比较的串t：";
				for(int i=0;i<n;++i)
					cin >> arr[i];
				StrAssign(t,arr);
				if(Strcmp(s,t) == 0) cout << "两串相等" << endl;
				else
				{
					if(Strcmp(s,t) == -1) cout << "串t较大" << endl;
					else cout << "串t较小" << endl;
				}
				break;
			}
		case 0:
			Destroy(s);Destroy(t);
			cout << "已退出" << endl;
			break;
		default:
			cout << "输入无效，请重新输入！" << endl;
			break;
		}
	}while(choice!=0);
}
