#include <bits/stdc++.h>
#define maxn 105
#define oo 1000000007
using namespace std;
typedef long long LL;
struct edge
{
	int x, y, z;
	edge(){}
	edge(int x, int y, int z):
	x(x),y(y),z(z){}
}e[maxn];
LL f[maxn][maxn][maxn];
int mu[maxn], np[maxn], prime[maxn];
int n, m, tot, t;
LL ans;

void get_prime(int n)
{
    memset(np,0,sizeof(np));
    tot=0;
    mu[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!np[i])
        {
            prime[++tot]=i;
            mu[i]=-1;
        }
        for (int j=1;j<=tot && i*prime[j]<=n;j++)
        {
            np[i*prime[j]]=1;
            if (i%prime[j]) mu[i*prime[j]]=-mu[i];
            else
            {
                mu[i*prime[j]]=0;
                break;
            }
        }
    }
}

int main()
{
	get_prime(100);
	scanf("%d%d",&n,&m);
	int x,y,z;
	memset(f,0,sizeof(f));
	memset(e,0,sizeof(e));
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		e[i]=edge(x, y, z);
		for (int p=1;p<=z;p++)
			if (z%p==0)
				f[x][y][p]=(f[x][y][p]+1)%oo;
	}
	for (int p=1;p<=100;p++)
		for (int k=1;k<=n;k++)
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
					f[i][j][p]=(f[i][j][p]+f[i][k][p]*f[k][j][p]%oo)%oo;
	ans=0;
	for (int p=1;p<=100;p++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				ans=(ans+f[i][j][p]*mu[p]%oo)%oo;
	printf("%d\n",ans);
	scanf("%d",&t);
	int id;
	while (t--)
	{
		scanf("%d%d",&id,&z);
		int x=e[id].x, y=e[id].y;
		int last=e[id].z;
		for (int p=1;p<=last;p++) if (last%p==0)
		{
			f[x][y][p]=(f[x][y][p]-1+oo)%oo;
			for (int i=1;i<=n;i++)
				f[i][y][p]=(f[i][y][p]-f[i][x][p]+oo)%oo;
			for (int i=1;i<=n;i++)
				f[x][i][p]=(f[x][i][p]-f[y][i][p]+oo)%oo;
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
					f[i][j][p]=(f[i][j][p]-f[i][x][p]*f[y][j][p]%oo+oo)%oo;
		}
		
		for (int p=1;p<=z;p++) if (z%p==0)
		{
			f[x][y][p]=(f[x][y][p]+1)%oo;
			for (int i=1;i<=n;i++)
				f[i][y][p]=(f[i][y][p]+f[i][x][p]%oo)%oo;
			for (int i=1;i<=n;i++)
				f[x][i][p]=(f[x][i][p]+f[y][i][p]%oo)%oo;
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
					f[i][j][p]=(f[i][j][p]+f[i][x][p]*f[y][j][p]%oo)%oo;
		}
		ans=0;
		for (int p=1;p<=100;p++)
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)		
					ans=(ans+f[i][j][p]*mu[p]%oo)%oo;
		e[id].z=z;
		printf("%d\n",ans);
	}
	return 0;
}