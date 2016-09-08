#include <bits/stdc++.h>
#define maxn 2200
#define inf 99999999
using namespace std;

double f[maxn][maxn];
int vis[maxn][maxn],g[maxn][maxn];
int n,m;

double dp(int k, int w)
{   
    if (vis[k][w]!=-1) return f[k][w];
    if (k<=0) return 0;
    vis[k][w]=1;
    if (k==1) return f[k][w]=1.0;
    if (w==1)
        f[k][w]=1.0+((double)k/(k+1))*dp(k-1, w)+((double)1/(k+1))*dp(0, w-1);
    else if ((1<<w)>=k)
    {
        int x=k/2;
        double f1=1.0+((double)(k-x+1)/(k+1))*dp(k-x, w)+((double)x/(k+1))*dp(x-1, w-1);
        x=k/2+1;
        double f2=1.0+((double)(k-x+1)/(k+1))*dp(k-x, w)+((double)x/(k+1))*dp(x-1, w-1);
        f[k][w]=min(f1,f2);
    }
    else
    {
        double tmp;
        f[k][w]=inf;
        int z=0;
        for (int x=1;x<=k;x++)
        {
            tmp=1.0+((double)(k-x+1)/(k+1))*dp(k-x, w)+((double)x/(k+1))*dp(x-1, w-1);
            if (tmp<f[k][w]) z=x;
            f[k][w]=min(f[k][w],tmp);
        }
        g[k][w]=z;
    }
    return f[k][w];
}

int main()
{
    //freopen("A.dat","w",stdout);
	memset(vis,-1,sizeof(vis));
	// while (scanf("%d%d",&n,&m)!=EOF)
 //    {
 //        printf("%.6f\n",dp(n,m));
 //    }
	for (int n=0;n<=2000;n++)
		for (int m=0;m<=10;m++)
			dp(n, m);
	for (int n=0;n<=2000;n++)
	{
		printf("{");
		for (int m=2;m<=9;m++)
		{
			printf("%d,",g[n][m]);
		}
		printf("%d}",g[n][10]);
		if (n!=2000) printf(",\n");
	}
	return 0;
}