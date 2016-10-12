#include <bits/stdc++.h>
#define maxn 100200
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
using namespace std;
typedef unsigned long long LL;
const LL oo=9223372034707292160LL;
LL sum[maxn<<3], flag[maxn<<3];
int n,m;
LL ans,tmp;

// LL mul(LL a,LL b,LL p)
// {
// 	a%=p,b%=p;
// 	LL tmp=0;
// 	while (b)
// 	{
// 		if (b&1) tmp=(tmp+a)%p;
// 		a=(a+a)%p;
// 		b/=2;
// 	}
// 	return tmp;
// }

inline LL mul(LL x, LL y, LL mod)
{
    LL ret = 0;
    __asm__("movq %1,%%rax\n imulq %2\n idivq %3\n":"=d"(ret):"m"(x),"m"(y),"m"(mod):"%rax");
    return ret;
}

void update(int x)
{
	sum[x]=sum[x<<1]+sum[x<<1|1];
	if (sum[x]>=oo) sum[x]-=oo;
	flag[x]=flag[x<<1]&flag[x<<1|1];
}

void build(int x, int l, int r)
{
	flag[x]=0;
	if (l==r)
	{
		scanf("%I64u",&sum[x]);
		return ;
	}
	int mid=(l+r)>>1;
	build(lson);
	build(rson);
	update(x);
}

void modify(int x, int l, int r, int ll, int rr)
{
	if (ll<=l && r<=rr)
		if (flag[x])
		{
			tmp+=sum[x];
			if (tmp>=oo) tmp-=oo;
			return ;
		}
	if (l==r)
	{
		tmp+=sum[x];
		if (tmp>=oo) tmp-=oo;
		LL cnt=sum[x];
		sum[x]=mul(cnt,cnt,oo);
		if (sum[x]==cnt) flag[x]=1;
		return ;
	}
	int mid=(l+r)>>1;
	if (ll<=mid) modify(lson, ll, rr);
	if (rr>mid) modify(rson, ll, rr);
	update(x);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		build(1, 1, n);
		int x, y;
		ans=0;
		printf("Case #%d:\n",o);
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			tmp=0;
			modify(1,1,n,x,y);
			ans+=tmp;
			if (ans>=oo) ans-=oo;
			printf("%I64u\n",ans);
		}
	}
	return 0;
}