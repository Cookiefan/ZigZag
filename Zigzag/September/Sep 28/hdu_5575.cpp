#include <bits/stdc++.h>
#define maxn 200200
#define inf 999999999
using namespace std;

int v[maxn], dis[maxn], l[maxn], r[maxn], rot[maxn];
int num;

int build(int z)
{
	v[++num]=z;
	l[num]=r[num]=dis[num]=0;
	return num;
}
int merge(int x, int y)
{
	if (!x || !y) return x+y;
	if (v[x]>v[y]) swap(x, y);
	r[x]=merge(r[x], y);
	if (dis[r[x]]>dis[l[x]]) swap(l[x], r[x]);
	dis[x]=dis[r[x]]+1;
	return x;
}
int top(int x)
{
	return v[x];
}
void pop(int &x)
{
	x=merge(l[x], r[x]);
}

int f[maxn];
int find(int x)
{
	return (f[x]==-1)?x:f[x]=find(f[x]);
}
typedef pair<int, int> pii;
vector<pii> q;
int lh[maxn], rh[maxn], L[maxn], R[maxn];
int up[maxn], dw[maxn];
int n, m;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x, y, z;
		lh[1]=rh[n]=inf;
		for (int i=1;i<n;i++)
		{
			scanf("%d",&x);
			rh[i]=lh[i+1]=x;
			L[i]=i-1; R[i]=i+1;
		}
		L[n]=n-1; R[n]=0;
		num=0;
		memset(f,-1,sizeof(f));
		memset(rot, 0,sizeof(rot));
		q.clear();
		int ans=0;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			if (z==0)
			{
				if (!rot[x])
					rot[x]=build(y);
				else
					rot[x]=merge(rot[x], build(y));
				ans++;
			}
			else
				q.push_back(pii(y, x));
		}
		sort(q.begin(), q.end());
		memset(up,0,sizeof(up));
		memset(dw,0,sizeof(dw));
		for (int i=0;i<q.size();i++)
		{
			int now=find(q[i].second), high=q[i].first;
			up[now]++;
			//<<flow
			while (high>=lh[now] && L[now])
			{
				int tmp=find(L[now]);
				if (tmp!=now) f[tmp]=now;
				rot[now]=merge(rot[now], rot[tmp]);
				L[now]=L[tmp];
				lh[now]=lh[tmp];
				dw[now]+=dw[tmp];
				up[now]+=up[tmp];
			}
			//>>flow
			while (high>=rh[now] && R[now])
			{
				int tmp=find(R[now]);
				if (tmp!=now) f[tmp]=now;
				rot[now]=merge(rot[now], rot[tmp]);
				R[now]=R[tmp];
				rh[now]=rh[tmp];
				dw[now]+=dw[tmp];
				up[now]+=up[tmp];
			}
			while (rot[now] && high>=top(rot[now]))
			{
				dw[now]++;
				pop(rot[now]);
			}
			if (up[now]>dw[now])
			{
				ans+=(up[now]-dw[now]);
				up[now]=dw[now]=0;
			}
		}
		printf("Case #%d: %d\n", o, ans);
	}
	return 0;
}