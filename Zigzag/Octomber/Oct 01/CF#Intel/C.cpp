#include <bits/stdc++.h>
#define maxn 100200
using namespace std;

typedef long long LL;

int a[maxn], b[maxn], v[maxn], t[maxn], f[maxn];
LL s[maxn], sum[maxn];
int n;
int find(int x)
{
	return (f[x]==-1)?x:f[x]=find(f[x]);
}
void merge(int x, int y)
{
	int fx=find(x), fy=find(y);
	if (fx!=fy)
	{
		f[fx]=fy;
		sum[fy]+=sum[fx];
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		v[b[i]]=i;
	}
	memset(f,-1,sizeof(f));
	memset(t,0,sizeof(t));
	for (int i=1;i<=n;i++) sum[i]=a[i];
	LL ans=0;
	for (int i=n;i>=1;i--)
	{
		s[i]=ans;
		t[v[i]]=1;
		if (v[i]!=1 && t[v[i]-1]) merge(v[i], v[i]-1);
		if (v[i]!=n && t[v[i]+1]) merge(v[i], v[i]+1);
		int now=find(v[i]);
		for (int j=1;j<=n;j++) cout<<find(j)<<' '; cout<<endl;
		for (int j=1;j<=n;j++) cout<<sum[find(j)]<<' '; cout<<endl;
		cout<<endl;
		ans=max(ans, sum[now]);
	}
	for (int i=1;i<=n;i++)
		printf("%I64d\n",s[i]);
	return 0;
}