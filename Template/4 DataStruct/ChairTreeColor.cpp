//从后往前插入线段树
//在第i颗线段树中维护i..n区间内第一次出现的数的位置
//(为1则为第一次出现，为0则未出现或前面出现过)
//这样查询一个区间时，只需在l树中查找1..r里面1的个数
//查询第k大的数时，也可以直接在l树中二分

#include <bits/stdc++.h>
#define maxn 200200
#define maxm 10000020
using namespace std;

int lc[maxm], rc[maxm], s[maxm];
int pre[maxn], a[maxn], rot[maxn];
int num, n, m, ans;

inline int build(int l, int r)
{
	int now=++num;
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
	s[now]=s[x]+z;
	if (l==r) return now;
	int mid=(l+r)>>1;
	if (p<=mid) lc[now]=change(lc[x], l, mid, p, z);
	else rc[now]=change(rc[x], mid+1, r, p, z);
	//s[now]=s[lc[now]]+s[rc[now]];
	return now;
}

inline int query(int x, int l, int r, int p)
{
	if (l==r) return s[x];
	int mid=(l+r)>>1;
	if (p<=mid) return query(lc[x], l, mid, p);
	else return s[lc[x]]+query(rc[x], mid+1, r, p);
}

inline void search(int x, int l, int r, int z)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	if (z<=s[lc[x]])
	{
		if (z==s[lc[x]]) ans=mid;
		search(lc[x], l, mid, z);
	}
	else 
		search(rc[x], mid+1, r, z-s[lc[x]]);
}

void write(int x, int l, int r)
{
	if (l==r)
	{
		cout<<s[x]<<' ';
		return;
	}
	int mid=(l+r)>>1;
	write(lc[x], l, mid);
	write(rc[x], mid+1, r);
}

int main()
{
	//freopen("I.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x, y;
		memset(pre,0,sizeof(pre));
		memset(s,0,sizeof(s));
		memset(lc,0,sizeof(lc));
		memset(rc,0,sizeof(rc));
		num=0;
		rot[n+1]=build(1, n);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for (int i=n;i>=1;i--)
		{
			x=a[i];
			if (pre[x])
			{
				rot[i]=change(rot[i+1], 1, n, pre[x], -1);
				rot[i]=change(rot[i], 1, n, i, 1);
			}
			else
				rot[i]=change(rot[i+1], 1, n, i, 1);
			pre[x]=i;
		}
		ans=0;
		printf("Case #%d: ",o);
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			int lf=(x+ans)%n+1;
			int rt=(y+ans)%n+1;
			if (lf>rt) swap(lf, rt);
			int cnt=(query(rot[lf], 1, n, rt)+1)>>1;
			search(rot[lf], 1, n, cnt);
			printf(i==m?"%d\n":"%d ",ans);
		}
	}
	return 0;
}