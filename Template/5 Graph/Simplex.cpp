#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define maxn 1010
#define maxm 10010
#define inf 2147483647
using namespace std;
int a[maxn][maxm],next[maxm];
int n,m;

void pivot(int l,int e)
{
    int last=-1;
    for (int i=0;i<=m;i++)
        if (a[l][i])
        {
            next[i]=last;
            last=i;
        }
    for (int i=0;i<=n;i++)
    {
        if (a[i][e]==0||i==l) continue;
        for (int j=last;j!=-1;j=next[j])
        {
            //cout<<j<<' ';
            if (j==e) continue;
            a[i][j]-=a[i][e]*a[l][j];
        }
        //cout<<endl;
        a[i][e]=-a[i][e];
    }
}

int simplex()
{
    while (1)
    {
        int now=0;
        for (int i=1;i<=m;i++) 
            if (a[0][i]>0) { now=i; break; }
        if (now==0) return -a[0][0];
        int tmp,mi=inf;
        for (int i=1;i<=n;i++)
        {
            if (a[i][now]>0&&a[i][0]<mi)
            {
                tmp=i;
                mi=a[i][0];
            }
        }
        pivot(tmp,now);
    }
}

int main()
{
    //freopen("defend.in","r",stdin);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&a[i][0]);
    int x,y;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&a[0][i]);
        for (int j=x;j<=y;j++)
            a[j][i]=1;
    }
    int ans=simplex();
    printf("%d\n",ans);
    return 0;
}