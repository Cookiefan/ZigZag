#include <bits/stdc++.h>
#define maxn 3200
using namespace std;

typedef long long LL;
int n;
int a[maxn];

int v[maxn], dis[maxn], sz[maxn];
int l[maxn], r[maxn];
int rot[maxn], st[maxn], ed[maxn];
int num;
int build(int z){
	v[++num]=z;
	sz[num]=1;
	l[num]=r[num]=dis[num]=0;
	return num;
}
int merge(int x, int y){
	if (!x || !y) return x+y;
	if (v[x]<v[y]) swap(x, y);//bit rot
	r[x]=merge(r[x], y);
	if (dis[r[x]]>dis[l[x]]) swap(l[x], r[x]);
	sz[x]=sz[l[x]]+sz[r[x]]+1;
	dis[x]=dis[r[x]]+1;
	return x;
}
int top(int x){
	return v[x];
}
int size(int x){
	return sz[x];
}
void pop(int &x){
	x=merge(l[x], r[x]);
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]=a[i]-i;
	}
	int now=0;
	for (int i=1;i<=n;i++)
	{
		rot[++now]=build(a[i]);
		st[now]=ed[now]=i;
		while (now>1 && top(rot[now-1])>top(rot[now]))
		{
			rot[--now]=merge(rot[now], rot[now+1]);
			ed[now]=ed[now+1];
			while (size(rot[now])>(ed[now]-st[now]+2)/2) pop(rot[now]);
		}
	}
	LL ans=0;
	for (int i=1;i<=now;i++)
		for (int j=st[i];j<=ed[i];j++)
			ans+=(LL)abs(top(rot[i])-a[j]);
	printf("%I64d\n",ans);
	return 0;
}