#include <bits/stdc++.h>
#define maxn 62
#define inf 99999999
using namespace std;
struct point
{
    int x, y;
    point(){}
    point(int x, int y):x(x),y(y){}
}p[maxn];
typedef long long LL;
int n,m;
int a[maxn][maxn],nxt[maxn];
LL dis[maxn][maxn];

void change(int x,int e)
{
    int last=-1;
    for (int i=0;i<=n;i++)
        if (a[x][i])
        {
            nxt[i]=last;
            last=i;
        }
    for (int i=0;i<=n;i++)
    {
        if (i==x || a[i][e]==0) continue;
        for (int j=last;j!=-1;j=nxt[j])
        {
            if (j==e) continue;
            a[i][j]-=a[i][e]*a[x][j];
        }
        a[i][e]=-a[i][e];
    }
}

int simplex()
{
    while (1)
    {
        int now=0;
        for (int i=1;i<=n;i++)     
            if (a[0][i]>0) { 
                now=i;
                break;
            }
        if (now==0) return -a[0][0];
        int tmp,mi=inf;
        for (int i=1;i<=n;i++)
            if (a[i][now]>0 && a[i][0]<mi)
                mi=a[i][0],tmp=i;
        change(tmp,now);
    }
}

LL count(int i, int j)
{
    return ((LL)abs(p[i].x-p[j].x)+(LL)abs(p[i].y-p[j].y));
}

bool judge(LL limit)
{
    a[0][0]=0;
    for (int i=1;i<=n;i++)
    {
        a[i][0]=1;
        a[0][i]=1;
        for (int j=1;j<=n;j++)
            if (j==i || dis[i][j]<=limit)
                a[j][i]=1;
            else
                a[j][i]=0;
    }
    int ans=simplex();
    return ans<=m;
}

int main()
{
    //freopen("defend.in","r",stdin);
    int Case;
    scanf("%d",&Case);
    for (int o=1;o<=Case;o++)
    {
        scanf("%d%d",&n,&m);
        int x,y;
        for (int i=1;i<=n;i++)
        {
            scanf("%d%d",&x,&y);
            p[i]=point(x,y);
        }
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                dis[i][j]=count(i,j);
        LL l=0, r=4000000000LL, ans=0;
        while (l<=r)
        {
            LL mid=(l+r)>>1;
            if (judge(mid))
            {
                r=mid-1;
                ans=mid;
            }
            else
                l=mid+1;
        }
        printf("Case #%d: %I64d\n",o,ans);
    }
    return 0;
}