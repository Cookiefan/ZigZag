#include <bits/stdc++.h>
#define maxn 200200
#define maxm 20000020
using namespace std;

int lc[maxm], rc[maxm], s[maxm], rot[maxm];
int pre[maxn];
int num, n, m;

inline int build(int l, int r)
{
	int now=++num;
	lc[now]=rc[now]=s[now]=0;
	if (l==r) return now;
	int mid=(l+r)>>1;
	lc[now]=build(l, mid);
	rc[now]=build(mid+1, r);
	return now;
}

inline int change(int x, int l, int r, int p, int z)
{
	int now=++num;
	lc[now]=lc[x];
	rc[now]=rc[x];
	s[now]=s[x];
	if (l==r)
	{
		s[now]+=z;
		return now;
	}
	int mid=(l+r)>>1;
	if (p<=mid) lc[now]=change(lc[x], l, mid, p, z);
	else rc[now]=change(rc[x], mid+1, r, p, z);
	s[now]=s[lc[now]]+s[rc[now]];
	return now;
}

inline int ask(int x, int y, int l, int r, int ll, int rr)
{
	if (ll<=l && r<=rr)
		return s[y]-s[x];
	int mid=(l+r)>>1, tmp=0;
	if (ll<=mid) tmp+=ask(lc[x], lc[y], l, mid, ll, rr);
	if (rr>mid) tmp+=ask(rc[x], rc[y], mid+1, r, ll, rr);
	return tmp;
}

inline int query(int l, int r)
{
	return ask(rot[l-1], rot[r], 1, n, l, n);
}

int main()
{
	freopen("I.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x, y, ans=0;
		memset(pre,0,sizeof(pre));
		num=0;
		rot[0]=build(1, n);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			if (pre[x])
				rot[i]=change(rot[i-1], 1, n, pre[x], -1);
			pre[x]=i;
			rot[i]=change(rot[i], 1, n, pre[x], 1);
		}
		printf("Case #%d: ",o);
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			int lf=(x+ans)%n+1;
			int rt=(y+ans)%n+1;
			if (lf>rt) swap(lf, rt);
			cout<<lf<<' '<<rt<<endl;
			int l=lf, r=rt, cnt=(query(lf, rt)+1)>>1;
			while (l<=r)
			{
				int mid=(l+r)>>1;
				if (query(lf, mid)>=cnt)
				{
					ans=mid;
					r=mid-1;
				}
				else
					l=mid+1;
			}
			printf(i==m?"%d\n":"%d ",ans);
		}
	}
	return 0;
}