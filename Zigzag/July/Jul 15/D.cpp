#include <bits/stdc++.h>
#define maxn 220000
using namespace std;
typedef long long llg;
llg sz[maxn];
double f[maxn];
vector<int> ch[maxn];
int n;

void dfs(int x)
{
	sz[x]=1;
	for (int i=0,ss=ch[x].size();i<ss;i++)
	{
		int y=ch[x][i];
		if (!sz[y]) dfs(y);
		sz[x]+=sz[y];
	}
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) ch[i].clear();
	int x;
	for (int i=2;i<=n;i++)
	{
		scanf("%d",&x);
		ch[x].push_back(i);
	}
	memset(sz,0,sizeof(sz));
	dfs(1);
	queue<int> q;
	while (!q.empty()) q.pop();
	q.push(1);
	f[1]=1.0;
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		double sum=0;
		for (int i=0,ss=ch[x].size();i<ss;i++)
		{
			int y=ch[x][i];
			sum+=sz[y];
		}
		for (int i=0,ss=ch[x].size();i<ss;i++)
		{
			int y=ch[x][i];
			f[y]=f[x]+0.5*(sum-sz[y])+1.0;
			q.push(y);
		}
	}
	for (int i=1;i<=n;i++) printf(i==n?"%.6f\n":"%.6f ",f[i]);


	return 0;
}