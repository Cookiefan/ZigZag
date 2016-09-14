#include <bits/stdc++.h>
#define maxn 2000200
#define sz 18
using namespace std;

int ch[maxn][20];
int v[maxn];
int n, num;
typedef long long LL;

void trie_add(string s, int z)
{
	int now=0;
	for (int i=0;i<sz;i++)
	{
		int w=(s[i]-'0')%2;
		if (ch[now][w]==-1)
			ch[now][w]=++num;
		now=ch[now][w];
	}
	v[now]+=z;
}

int trie_ask(string s)
{
	int now=0;
	for (int i=0;i<sz;i++)
	{
		int w=(s[i]-'0')%2;
		if (ch[now][w]==-1) return 0;
		now=ch[now][w];
	}
	return v[now];
}

string s;

int main()
{
	scanf("%d",&n);
	char sign;
	LL x;
	num=0;
	memset(ch,-1,sizeof(ch));
	memset(v,0,sizeof(v));
	for (int o=1;o<=n;o++)
	{
		scanf(" %c",&sign);
		cin>>s;
		reverse(s.begin(), s.end());
		int len=s.length();
		for (int i=len;i<sz;i++) s.push_back('0');
		if (sign=='+')
		{
			trie_add(s, 1);
		}
		else if (sign=='-')
		{
			trie_add(s, -1);
		}
		else
			printf("%d\n",trie_ask(s));
	}
	return 0;
}