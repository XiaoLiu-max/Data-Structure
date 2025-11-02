#include<iostream>
#include<string>
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

//Brute-Force
int BF(SqString s,SqString t)
{
	int i = 0,j = 0;
	while(i<s.length && j<t.length)
	{
		if(s.data[i] == t.data[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if(j >= t.length)
		return i - t.length;
	else
		return -1;
}

//KMP
void GetNext(SqString t,int next[])
{
	int j = 0,k = -1;
	next[0] = -1;
	while(j < t.length-1)
	{
		if(k == -1 || t.data[j] == t.data[k])
		{
			++j;
			++k;
			next[j] = k;
		}
		else
			k = next[k];
	}
}

int KMPIndex(SqString s,SqString t)
{
	int next[Maxsize],i=0,j=0;
	GetNext(t,next);
	while(i<s.length && j<t.length)
	{
		if(j == -1 || s.data[i] == t.data[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if(j >= t.length)
		return i-t.length;
	else 
		return -1;
}

//改进的KMP算法
void GetNextval(SqString t,int nextval[])
{
	int j = 0,k = -1;
	nextval[0] = -1;
	while(j < t.length-1)
	{
		if(k == -1 || t.data[j] == t.data[k])
		{
			j++;
			k++;
			if(t.data[j] != t.data[k])
				nextval[j] = k;
			else
				nextval[j] = nextval[k];
		}
		else
			k = nextval[k];
	}
}

int KMPIndexl(SqString s,SqString t)
{
	int nextval[Maxsize],i=0,j=0;
	GetNext(t,nextval);
	while(i<s.length && j<t.length)
	{
		if(j == -1 || s.data[i]==t.data[j])
		{
			++i;
			++j;
		}
		else
			j = nextval[j];
	}
	if(j >= t.length)
		return i-t.length;
	else
		return -1;
}

int main()
{
	string s1,t1;
	cin >> s1 >> t1;
	SqString s,t;
	StrAssign(s,s1.c_str());
	StrAssign(t,t1.c_str());
	cout << BF(s,t) << " " << KMPIndex(s,t) << " " << KMPIndexl(s,t) << endl;
}
