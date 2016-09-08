#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define inf 1000000007
#define oo 100000000
#define maxn 11
#define maxm 1050

using namespace std;

int n,m,mb;
long long f[maxn][maxn][88][maxm];
int bit[maxm][maxn];

bool legal(int x, int y,int mask)
{
    if (y==1)
    {
        if (bit[mask][n]&bit[mask][n+1]) return 0;
        if (bit[mask][n-1]&bit[mask][n+1]) return 0;
    }
    else
    {
        if (bit[mask][y-1]&bit[mask][n+1]) return 0;
        if (bit[mask][y-2]&bit[mask][n+1]) return 0;
    }
    for (int i=1;i<n;i++) if (bit[mask][i]&bit[mask][i+1]) return 0;
    return 1;
}

int main()
{
    scanf("%d%d",&n,&m);
    mb=(1<<(n+1))-1;
    memset(bit,0,sizeof(bit));
    for (int mask=0;mask<=mb;mask++)
    {
        int tmp=mask;
        for (int i=1;i<=n+1;i++)
        {
            bit[mask][i]=tmp%2;
            tmp/=2;
        }
    }
    memset(f,0,sizeof(f));
    f[0][n][0][0]=1;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            for (int k=0;k<=m;k++)
                for (int mask=0;mask<=mb;mask++)
                    if (legal(i,j,mask))
                    {
                        int tmp=1<<(j-1);
                        int ost=mask&(~tmp),nst=mask|tmp;
                        if (((mask>>(j-1))&1)!=((mask>>n)&1)) ost^=(1<<n),nst^=(1<<n);
                        if (j==1)
                        {
                            f[i][j][k][ost]+=f[i-1][n][k][mask];
                            if (k && !bit[mask][j] && !bit[mask][j+1] && !bit[mask][j-1])
                                f[i][j][k][nst]+=f[i-1][n][k-1][mask];
                        }
                        else
                        {
                            f[i][j][k][ost]+=f[i][j-1][k][mask];
                            if (k && !bit[mask][j] && !bit[mask][j+1] && !bit[mask][j-1] && !bit[mask][n+1])
                                f[i][j][k][nst]+=f[i][j-1][k-1][mask];
                        }
                    }
    long long ans=0;
    for (int mask=0;mask<=mb;mask++)
        if (legal(n+1,1,mask))
        {
            ans+=f[n][n][m][mask];
        }
    printf("%lld\n",ans);
    return 0; 
}

Kings