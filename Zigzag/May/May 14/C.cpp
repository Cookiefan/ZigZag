#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
#define maxn 220000
using namespace std;

struct node
{
	node* c[30], *fa;
	int sum;
	node(int s, node* fa):sum(s), fa(fa)
	{
		for (int i=0;i<26;i++)
			c[i]=NULL;
	}
}*rot;
int n;
string sign, s;

void add_str(string s)
{
	node *now=rot;
	int len=s.length();
	for (int i=0;i<len;i++)
	{
		int w=s[i]-'a';
		if (now->c[w]==NULL)
		{
			//cout<<w<<endl;
			now->c[w]=new node(0, now);
			//cout<<(now->c[w]->fa==rot)<<endl;
		}
		now=now->c[w];
		now->sum++;
	}
}

void del_str(string s)
{
	node *now=rot;
	int len=s.length();
	for (int i=0;i<len;i++)
	{
		int w=s[i]-'a';
		if (now->c[w]==NULL) return;
		else now=now->c[w];
	}
	for (int i=0;i<26;i++)
		if (now->c[i]!=NULL)
			now->c[i]=NULL;
	int tmp=now->sum;
	while (now!=rot)
	{
		now->sum-=tmp;
		now=now->fa;
	}
}

bool find_str(string s)
{
	node *now=rot;
	int len=s.length();
	for (int i=0;i<len;i++)
	{
		int w=s[i]-'a';
		if (now->c[w]==NULL) return 0;
		else now=now->c[w];
	}
	if (now->sum>0) return 1;
	else return 0;
}

int main()
{
	scanf("%d",&n);
	rot=new node(0, NULL);
	for (int i=1;i<=n;i++)
	{
		cin>>sign;
		cin>>s;
		if (sign=="insert") add_str(s);
		else if (sign=="delete") del_str(s);
		else printf(find_str(s)?"Yes\n":"No\n");
	}
	return 0;
}