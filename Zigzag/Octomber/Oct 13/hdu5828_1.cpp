#include <bits/stdc++.h>
using namespace std;
#define maxn 100200
#define xx first
#define yy second
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
typedef long long LL;
typedef pair<LL, LL> pll;

pll mv[maxn<<2];
LL add[maxn<<2], sum[maxn<<2], cov[maxn<<2];
int n,m;

inline LL read() {
    LL x=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    return x*f;
}

inline void update(int x)
{
	sum[x]=sum[x<<1]+sum[x<<1|1];
	mv[x].xx=max(mv[x<<1].xx,mv[x<<1|1].xx);
	mv[x].yy=min(mv[x<<1].yy,mv[x<<1|1].yy);
}

inline void build(int x, int l, int r)
{
	add[x]=cov[x]=0;
	if (l==r)
	{
		sum[x]=read();
		mv[x]=pll(sum[x], sum[x]);
		return ;
	}
	int mid=(l+r)>>1;
	build(lson);
	build(rson);
	update(x);
}

inline void cover(int x, int l, int r, LL z)
{
	cov[x]=z;
	add[x]=0;
	sum[x]=(LL)(r-l+1)*z;
	mv[x]=pll(z,z);
}

inline void addit(int x, int l, int r, LL z)
{
	sum[x]+=(LL)(r-l+1)*z;
	add[x]+=z;
	mv[x].xx+=z;
	mv[x].yy+=z;
}

inline void down(int x, int l, int r)
{
	int mid=(l+r)>>1;
	if (cov[x])
	{
		cover(lson, cov[x]);
		cover(rson, cov[x]);
		cov[x]=0;
	}
	if (add[x])
	{
		addit(lson, add[x]);
		addit(rson, add[x]);
		add[x]=0;
	}
}

inline void increase(int x, int l, int r, int ll, int rr, int z)
{
	if (ll<=l && r<=rr)
	{
		addit(x,l,r,z);
		return ;
	}
	down(x,l,r);
	int mid=(l+r)>>1;
	if (ll<=mid) increase(lson, ll, rr, z);
	if (rr>mid) increase(rson, ll, rr, z);
	update(x);
}

inline void getroot(int x, int l, int r, int ll, int rr)
{
	if (ll<=l && r<=rr && mv[x].xx-mv[x].yy<=1)
	{
		LL a=sqrt(mv[x].xx), b=sqrt(mv[x].yy);
		if (a-b==1)
		{
			LL tmp=a-mv[x].xx;
			addit(x,l,r,tmp);
			return ;
		}
		else
		{
			cover(x,l,r,a);
			return ;
		}
	}
	if (l==r)
	{
		LL now=sqrt(sum[x]);
		sum[x]=now;
		mv[x]=pll(now,now);
		return ;
	}
	down(x,l,r);
	int mid=(l+r)>>1;
	if (ll<=mid) getroot(lson, ll, rr);
	if (rr>mid) getroot(rson, ll, rr);
	update(x);
}

inline LL query(int x, int l, int r, int ll, int rr)
{
	if (ll<=l && r<=rr)
		return sum[x];
	down(x,l,r);
	LL tmp=0;
	int mid=(l+r)>>1;
	if (ll<=mid) tmp+=query(lson, ll, rr);
	if (rr>mid) tmp+=query(rson, ll, rr);
	update(x);
	return tmp;
}

int main()
{
	//freopen("R.in","r",stdin);
	int Case=read();
	for (int o=1;o<=Case;o++)
	{
		n=read(); m=read();
		build(1,1,n);
		int sign, x, y, z;
		for (int i=1;i<=m;i++)
		{
			sign=read();
			if (sign==1)
			{
				x=read(); y=read(); z=read();
				increase(1,1,n,x,y,z);
			}
			else if (sign==2)
			{
				x=read(); y=read();
				getroot(1,1,n,x,y);
			}
			else
			{
				x=read(); y=read();
				printf("%I64d\n",query(1,1,n,x,y));
			}
		}
	}
	return 0;
}