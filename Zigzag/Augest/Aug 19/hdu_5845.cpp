#include <bits/stdc++.h>
#define maxn 220000
#define lowbit 31
using namespace std;
int a[maxn], s[maxn];
int f[maxn];
int n,m,l,p,q;

int c[maxn][2], v[maxn], mx[maxn], fa[maxn];
int num;

void trie_init()
{
	num=0;
	memset(c,-1,sizeof(c));
	memset(v,0,sizeof(v));
	memset(mx,-1,sizeof(mx));
	memset(f,-1,sizeof(f));
}

void trie_cov(int x, int z, int f)
{
	int now=0;
	for (int i=lowbit-1;i>=0;i--)
	{
		int w=(x>>i)&1;
		if (c[now][w]==-1) c[now][w]=++num;
		fa[c[now][w]]=now;
		now=c[now][w];
		mx[now]=max(mx[now], f);
		v[now]+=z;
	}
	if (v[now]==0)
	{
		mx[now]=-1;
		while (now)
		{
			now=fa[now];
			mx[now]=-1;
			if (c[now][0] && v[c[now][0]]) mx[now]=max(mx[now],mx[c[now][0]]);
			if (c[now][1] && v[c[now][1]]) mx[now]=max(mx[now],mx[c[now][1]]);
		}
	}
}

int trie_ask(int x)
{
	int now=0, tmp=0, ans=-1;
	for (int i=lowbit-1;i>=0;i--)
	{
		int w=(x>>i)&1;
		int x=c[now][w^1], y=c[now][w];
		if ((tmp^(1<<i))<=m)
		{
			if (y!=-1 && v[y]) ans=max(ans, mx[y]);
			now=x, tmp^=(1<<i);
		}
		else
			now=y;
		if (now==-1 || v[now]==0) return ans;
	}
	ans=max(ans, mx[now]);
	return ans;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&l);
		scanf("%d%d%d",&a[1],&p,&q);
		s[1]=a[1];
		for (int i=2;i<=n;i++)
		{
			a[i]=((long long)a[i-1]*p+q)%268435456;
			s[i]=s[i-1]^a[i];
		}
		trie_init();
		trie_cov(0, 1, 0);
		for (int i=1;i<=n;i++)
		{
			if (i-l-1>=0 && f[i-l-1]>0) trie_cov(s[i-l-1], -1, -1);
			int tmp=trie_ask(s[i])+1;
			if (tmp>0)
			{
				f[i]=tmp;
				trie_cov(s[i], 1, f[i]);
			}
			else
				f[i]=0;
		}
		printf("%d\n",f[n]);
	}

	return 0;
}