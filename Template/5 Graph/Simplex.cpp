//单纯形(复杂度不确定，慎用!!!)
#include <bits/stdc++.h>
using namespace std;
#define maxn 6020
#define inf 999999999

int a[1020][10020];
int nxt[maxn], id[maxn], ans[maxn];
int p, q, n, m, num;

void pivot(int x,int y)//交换非基x与基y
{
    int last=-1;
    swap(id[x+m], id[y]);
    for (int i=0;i<=m;i++)
        if (a[x][i]){
            nxt[i]=last;
            last=i;
        }
    for (int i=0;i<=n;i++){
        if (i==x||a[i][y]==0) continue;
        for (int j=last;j!=-1;j=nxt[j]){
            if (j==y) continue;
            a[i][j]-=a[i][y]*a[x][j];
        }
        a[i][y]=-a[i][y];
    }
}

int simplex()
{
    for (int i=1;i<=m;i++) id[i]=i;
    while (1){
        int y=0;
        for (int i=1;i<=m;i++) 
            if (a[0][i]>0) { y=i; break; }
        if (y==0) return -a[0][0];
        int x,mi=inf;
        for (int i=1;i<=n;i++){
            if (a[i][y]>0&&a[i][0]<mi){
                x=i;
                mi=a[i][0];
            }
        }
        pivot(x,y);
    }
    for (int i=m+1;i<=m+n;i++)
        ans[id[i]]=a[i-m][0];
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