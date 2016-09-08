#include <bits/stdc++.h>
#define maxn 20000020
using namespace std;

int c[maxn][2], v[maxn];
int a[1020];
int n, num;

void trie_ins(int x, int z)
{
	int now=0;
	for (int i=30;i>=0;i--)
	{
		int w=(x>>i)&1;
		//cout<<w<<' ';
		if (c[now][w]==-1)
		{
			c[now][w]=++num;
			c[num][0]=c[num][1]=-1;
			v[num]=0;
		}
		now=c[now][w];
		v[now]+=z;
	}
	//cout<<endl;
}

int trie_ask(int x)
{
	int now=0, tmp=0;
	for (int i=30;i>=0;i--)
	{
		int w=(x>>i)&1;
		if (c[now][w^1]!=-1 && v[c[now][w^1]]>0)
		{
			now=c[now][w^1];
			tmp=tmp|(1<<i);
		}
		else 
			now=c[now][w];
	}
	return tmp;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		num=0;
		c[0][0]=c[0][1]=-1;
		v[0]=0;
		for (int i=1;i<=n;i++)
			for (int j=1;j<i;j++)
				trie_ins(a[i]+a[j], 1);

		int ans=0;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
				if (j!=i)
					trie_ins(a[i]+a[j], -1);
			ans=max(ans, trie_ask(a[i]));
			for (int j=1;j<=n;j++)
				if (j!=i)
					trie_ins(a[i]+a[j], 1);
		}
		printf("%d\n",ans);
	}
	return 0;
}