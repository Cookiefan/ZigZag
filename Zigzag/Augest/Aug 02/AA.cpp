#include <bits/stdc++.h>
#define maxn 2200
#define inf 99999999
using namespace std;

double f[maxn][maxn];
int vis[maxn][maxn];
int n,m;
double dp(int k, int w)
{   
    if (vis[k][w]!=-1) return f[k][w];
    if (k<=0) return 0;
    vis[k][w]=1;
    if (k==1) return f[k][w]=1.0;
    if (w==1)
        f[k][w]=1.0+((double)k/(k+1))*dp(k-1, w)+((double)1/(k+1))*dp(0, w-1);
	if ((1<<w)>k)
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
		for (int x=1;x<=k;x++)
		{
	    	tmp=1.0+((double)(k-x+1)/(k+1))*dp(k-x, w)+((double)x/(k+1))*dp(x-1, w-1);
	    	f[k][w]=min(f[k][w],tmp);
		}    	
	}
 
    return f[k][w];
}

int main()
{
    //freopen("data.in","r",stdin);
    //freopen("A.out","w",stdout);

    memset(vis,-1,sizeof(vis));
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        printf("%.6f\n",dp(n,m));
    }
    return 0;
}