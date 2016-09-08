#include <bits/stdc++.h>
#define maxn 200020
using namespace std;
int mi[maxn*8], ma[maxn*8], tag[maxn*8];
int f[maxn], lt[maxn], rt[maxn];
int cost[maxn];
int n,m;

void cover(int x, int a, int b)
{
	mi[x]=min(mi[x], a);
	ma[x]=max(ma[x], b);
	tag[x]=1;
}

void down(int x)
{
	if (tag[x])
	{
		cover(x<<1, mi[x], ma[x]);
		cover(x<<1|1, mi[x], ma[x]);
		tag[x]=0;
	}
}

void change(int x, int l, int r, int ll, int rr, int z)
{
	if (ll<=l && r<=rr)
	{
		cover(x, z, z);
		return ;
	}
	down(x);
	int mid=(l+r)>>1;
	if (ll<=mid) change(x<<1, l, mid, ll, rr, z);
	if (rr>mid) change(x<<1|1, mid+1, r, ll, rr, z);
}

void release(int x, int l, int r)
{
	if (l==r)
	{
		lt[l]=mi[x];
		rt[l]=ma[x];
		return ; 
	}
	down(x);
	int mid=(l+r)>>1;
	release(x<<1, l, mid);
	release(x<<1|1, mid+1, r);
}

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		int x, y;
		for (int i=1;i<=n-1;i++) scanf("%d",&f[i]);
		for (int i=1;i<=6*n;i++)
		{
			mi[i]=m+1;
			ma[i]=0;
		}
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			if (x>y) swap(x,y);
			change(1,1,n-1,x,y-1,i);
		}
		release(1,1,n-1);
		memset(cost,0,sizeof(cost));
		for (int i=1;i<=n-1;i++)
		{
			x=lt[i]; y=rt[i];
			if (x>y) continue;
			cost[x]+=f[i];
			cost[y+1]-=f[i];
		}
		for (int i=1;i<=m;i++)
			cost[i]=cost[i-1]+cost[i];
		for (int i=1;i<=m;i++)
			printf("%d\n",cost[i]);
	}

	return 0;
}