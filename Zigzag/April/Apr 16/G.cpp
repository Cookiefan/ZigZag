#include <bits/stdc++.h>
#define maxn 22000
using namespace std;
struct TRI
{
	int x, y, z;
	TRI(int x, int y, int z):x(x), y(y),z(z){}
	friend bool operator <(TRI a, TRI b)
	{
		return a.x<b.x;
	}
};
int n, k;
int a, x, b, c, sum;
vector<TRI> f[maxn];
vector<TRI> d;
int ans[maxn];
int v[1200];

int main()
{
	freopen("generators.in","r",stdin);
	freopen("generators.out","w",stdout);
	scanf("%d%d",&n,&k);
	d.clear();
	for (int i=1;i<=n;i++)
	{
		f[i].clear();
		scanf("%d%d%d%d",&x,&a,&b,&c);
		memset(v,0,sizeof(v));
		int id=0, mx=-1;
		while (!v[x])
		{
			if (x>mx)
			{
				mx=x;
				ans[i]=id;
			}
			f[i].push_back(TRI(x, i, id++));
			v[x]=1;
			x=(x*a+b)%c;
		}
		sum+=mx;
		for (int j=0;j<id;j++) d.push_back(TRI(mx-f[i][j].x, i, j));	
	}
	sort(d.begin(), d.end());
	if (sum%k==0)
	{
		int num=d.size();
		for (int i=0;i<num;i++)
			if (d[i].x%k!=0)
			{
				sum-=d[i].x;
				ans[d[i].y]=d[i].z;
				break;
			}
		if (sum%k==0)
			sum=-1;
	}
	printf("%d\n",sum);
	if (sum!=-1)
	{
		for (int i=1;i<=n;i++)
			printf(i<n?"%d ":"%d\n",ans[i]);
	}
	return 0;
}
