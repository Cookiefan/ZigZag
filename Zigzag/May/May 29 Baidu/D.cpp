#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
#define pii pair<int, int>
#define maxn 12000
#define inf 999999999
using namespace std;

int a[maxn],s[maxn];
int f[maxn][20];

set<pii> q[20];

int n,m,l;

int sum(int l, int r)
{
	return s[r]^s[l-1];
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&l);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		s[0]=0;
		for (int i=1;i<=n;i++) s[i]=s[i-1]^a[i];
		memset(f,0,sizeof(f));
		f[0][0]=inf;
		for (int k=1;k<=m;k++)
			for (int i=1;i<=n;i++)
			{
				int now=(set.end()-1)->first;
				for (int j=max(0,i-l);j<i;j++)
					f[i][k]=max(f[i][k], min(f[j][k-1],sum(j+1, i)));
				q[k].insert(pii(f[i][k], i));
			}
		printf("%d\n",f[n][m]);
	}
	return 0;
}