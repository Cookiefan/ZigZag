#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define maxn 10020
#define inf 999999999
using namespace std;

int a[maxn],s[maxn], p[50];
int f[maxn][20];

int n,m,l,mxbit;

struct trie
{
	int c[5000000][2], v[5000000];
	int tot;
	void clear()
	{
		tot=0;
		c[0][0]=c[0][1]=0;
		v[0]=0;
	}
	void add(int x, int z)
	{
		for (int i=0;i<mxbit;i++) p[i]=x&1, x>>=1;
		int now=0;
		for (int i=mxbit-1;i>=0;i--)
		{
			if (!c[now][p[i]])
			{
				c[now][p[i]]=++tot;
				c[tot][0]=c[tot][1]=0;
				v[tot]=0;
			}
			now=c[now][p[i]];
			v[now]+=z;
		}
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=0;i<mxbit;i++) p[i]=x&1, x>>=1;
		int now=0;
		for (int i=mxbit-1;i>=0;i--)
		{
			if (c[now][p[i]^1] && v[c[now][p[i]^1]]>0)
				now=c[now][p[i]^1], tmp=(tmp<<1)+1;
			else
				now=c[now][p[i]], tmp=tmp<<1;
		}
		return tmp;
	}
}tree;

bool judge(int limit)
{
	for (int i=0;i<=n+1;i++)
		for (int j=0;j<=12;j++)
			f[i][j]=0;

	for (int i=1;i<=l;i++)
		if (s[i]>=limit)
			f[i][1]=1;
	
	for (int k=2;k<=m;k++)
	{
		tree.clear();
		for (int i=1;i<=n;i++)
		{
			if (i>=k && tree.ask(s[i])>=limit) f[i][k]=1;
			if (f[i][k-1])
				tree.add(s[i], 1);
			if (i-l>0 && f[i-l][k-1])
				tree.add(s[i-l], -1);
		}
	}
	return f[n][m];
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&l);
		int l=0, r=0, ans;
		for (int i=1;i<=n;i++) scanf("%d",&a[i]), r=max(r, a[i]);
		s[0]=0;
		for (int i=1;i<=n;i++) s[i]=s[i-1]^a[i];
		mxbit=(int)log2(r)+1;
		r=1<<((int)log2(r)+1);
		while (l<=r)
		{
			int mid=(l+r)>>1;
			//cout<<mid<<endl;
			if (judge(mid))
			{
				l=mid+1;
				ans=mid;
			}
			else
				r=mid-1;
		}
		printf("Case #%d:\n%d\n",o,ans);
	}
	return 0;
}