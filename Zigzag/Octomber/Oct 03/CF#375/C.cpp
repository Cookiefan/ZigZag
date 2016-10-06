#include <bits/stdc++.h>
#define maxn 2200
using namespace std;

int a[maxn], v[maxn];
vector<int> pos;
int n, m, cnt, ans;

int main()
{
	scanf("%d%d",&n,&m);
	cnt=n/m;
	int x;
	memset(v,0,sizeof(v));
	pos.clear();
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		a[i]=x;
		if (x<=m)
		{
			if (++v[x]>cnt)
			pos.push_back(i);
		}
		else
			pos.push_back(i);
	}
	ans=0;
	int now=0;
	for (int i=1;i<=m;i++)
		while (v[i]<cnt)
		{
			a[pos[now++]]=i;
			v[i]++;
			ans++;
		}
	printf("%d %d\n",cnt, ans);
	for (int i=1;i<=n;i++)
		printf(i==n?"%d\n":"%d ",a[i]);
	return 0;
}