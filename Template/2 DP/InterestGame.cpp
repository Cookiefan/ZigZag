//n个人每个人有一个l长的字母序列字母表为m
//每个字母出现的概率为x/y
//出现一个人的字母序列那么这个人赢
//问每个人赢的概率
#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int ch[maxn][12],tran[maxn][12],pre[maxn],q[maxn],v[maxn],d[maxn];
char s[maxn];
double rate[maxn],a[maxn][maxn],ans[maxn];
int n,m,len,num,now,rot;

void insert(int w)
{
    if (ch[now][w]==0) ch[now][w]=++num;
    now=ch[now][w];
}

void build()
{
    int head=0,tail=1;
    q[1]=rot;
    while (head<tail)
    {
        int now=q[++head];
        for (int w=1;w<=m;w++)
            if (ch[now][w])
            {
                int k=ch[now][w];
                if (now==rot) pre[k]=rot;
                else 
                {
                    int p=pre[now];
                    while (p&&ch[p][w]==0) p=pre[p];
                    if (p) pre[k]=ch[p][w];
                    else pre[k]=rot;
                }
                q[++tail]=k;
            }
    }
}

void gauss(int n)
{
    int k=1;
    for (int i=1;i<=n;i++)
    {
        int p=0;
        for (int j=k;j<=n;j++)
            if (a[j][i]) {    p=j; break;    }
        if (!p) continue;
        for (int l=1;l<=n+1;l++) swap(a[p][l],a[k][l]);
        for (int j=k+1;j<=n;j++)
            if (a[j][i])
            {
                double tmp=a[j][i]/a[k][i];
                for (int l=1;l<=n+1;l++) a[j][l]-=tmp*a[k][l];
            }
        k++;
    }
    for (int i=n;i;i--)
    {
        ans[i]=a[i][n+1];
        for (int j=i+1;j<=n;j++)
            ans[i]-=a[i][j]*ans[j];
        ans[i]/=a[i][i];
    }
}    

int main()
{
    //freopen("game.in","r",stdin);
    //freopen("game.out","w",stdout);
    scanf("%d%d%d",&n,&len,&m);
    int x,y;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        rate[i]=(y)?(1.0*x/y):0;
    }
    now=rot=num=1;
    for (int i=1;i<=n;i++)
    {
        now=rot;
        scanf("%s",s);
        for (int j=0;j<len;j++) insert(s[j]-'A'+1);
        v[now]=i;
        d[i]=now;
    }
    build();
    for (int i=1;i<=num;i++) 
        for (int w=1;w<=m;w++)
        {
            int p=i;
            while (p&&ch[p][w]==0) p=pre[p];
            if (p) tran[i][w]=ch[p][w];
            else tran[i][w]=rot;
        }
    //求转移函数
    for (int i=1;i<=num;i++)
    {
        a[i][i]=-1;
        for (int w=1;w<=m;w++)
            if (!v[i]) a[tran[i][w]][i]+=rate[w];
    }
    for (int i=1;i<=num;i++) if (v[i]) a[1][i]=1;else a[1][i]=0;
    a[1][num+1]=1;
    gauss(num);
    for (int i=1;i<=n;i++)
        if (ans[d[i]]>0&&ans[d[i]]<=1)
            printf("%.2lf\n",ans[d[i]]);
        else printf("0.00\n");
    return 0;
}