#include <bits/stdc++.h>
#define maxn 220000
using namespace std;

int n,m;
vector<int> t[maxn];
queue<int> que;
long long a[maxn], b[maxn];
int idg[maxn];
long long f[maxn];
long long ans;
const int oo=1e9+7;

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		for (int i=1;i<=n;i++)
		{
			t[i].clear();
			idg[i]=0;
			f[i]=0;
		}
		for (int i=1;i<=n;i++)
			scanf("%d%d",&a[i],&b[i]);
		int x,y;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			t[x].push_back(y);
			idg[y]++;
		}
		while (!que.empty()) que.pop();
		for (int i=1;i<=n;i++)
			if (idg[i]==0)
				que.push(i);
		ans=0;
		while (!que.empty())
		{
			int x=que.front(); que.pop();
			ans=(ans+(f[x]*b[x])%oo)%oo;
			f[x]=(f[x]+a[x])%oo;
			for (int y:t[x])
			{
				f[y]=(f[y]+f[x])%oo;
				if ((--idg[y])==0)
					que.push(y);
			}				
		}
		printf("%lld\n",ans);
	}

	return 0;
}