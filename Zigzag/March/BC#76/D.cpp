#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define maxn 1020000
#define oo 1000000007
using namespace std;
int a[maxn], now[maxn];
int n,m,p;
struct sum_bit
{
	int sum[maxn], cov[maxn], size[maxn];
	void update(int x)
	{
		sum[x]=sum[x<<1]+sum[x<<1|1];
	}
	void cover(int x, int z)
	{
		cov[x]=z;
		sum[x]=size[x]*z;
	}
	void down(int x)
	{
		if (cov[x]==-1) return ;
		cover(x<<1, cov[x]);
		cover(x<<1|1, cov[x]);
		cov[x]=-1;
	}
	void change(int x, int l, int r, int ll, int rr, int z)
	{
		if (ll<=l && r<=rr)
		{
			cover(x, z);
			return ;
		}
		down(x);
		int mid=(l+r)>>1;
		if (ll<=mid) change(x<<1, l, mid, ll, rr, z);
		if (rr>mid) change(x<<1|1, mid+1, r, ll, rr, z);
		update(x);
	}
	int get_sum(int x, int l, int r, int ll, int rr)
	{
		if (ll<=l && r<=rr) return sum[x];
		down(x);
		int mid=(l+r)>>1, tmp=0;
		if (ll<=mid) tmp+=get_sum(x<<1, l, mid, ll, rr);
		if (rr>mid) tmp+=get_sum(x<<1|1, mid+1, r, ll, rr);
		update(x);
		return tmp;
	}
	void init(int x, int l, int r)
	{
		if (l==r)
		{
			sum[x]=now[l];
			cov[x]=-1;
			size[x]=1;
			return ;
		}
		int mid=(l+r)>>1;
		init(x<<1, l, mid);
		init(x<<1|1, mid+1, r);
		size[x]=size[x<<1]+size[x<<1|1];
		update(x);
		cov[x]=-1;
	}
}tree;

struct query
{
	int l,r,o;
}q[maxn];


bool pass(int mid)
{
	memset(sum,0,sizeof(sum));
	memset(size,0,sizeof(size));
	for (int i=1;i<=n;i++)
		now[i]=(a[i]>mid);
	tree.init(1,1,n);
	// for (int i=1;i<=n;i++) cout<<tree.get_sum(1,1,n,i,i)<<' ';cout<<endl;
	// cout<<endl;
	for (int i=1;i<=m;i++)
	{
		int tmp=tree.get_sum(1,1,n,q[i].l, q[i].r);
		if (!tmp) continue;
		tree.change(1,1,n,q[i].l,q[i].r,0);
		if (q[i].o==0)			
			tree.change(1,1,n,q[i].r-tmp+1,q[i].r,1);
		else
			tree.change(1,1,n,q[i].l,q[i].l+tmp-1,1);
		//for (int i=1;i<=n;i++) cout<<tree.get_sum(1,1,n,i,i)<<' ';cout<<endl;
	}
	//cout<<endl;
	return tree.get_sum(1,1,n,p,p)==0;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for (int i=1;i<=m;i++)
			scanf("%d%d%d",&q[i].o,&q[i].l,&q[i].r);
		scanf("%d",&p);
		int l=1,r=n, ans=0;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (pass(mid))
			{
				ans=mid;
				r=mid-1;
			}
			else
				l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}