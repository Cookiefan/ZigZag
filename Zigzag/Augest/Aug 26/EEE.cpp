#include <bits/stdc++.h>
#define maxn 62
#define maxm 250000
#define inf 99999999
using namespace std;
struct point
{
    int x, y;
    point(){}
    point(int x, int y):x(x),y(y){}
}p[maxn];
typedef long long LL;
LL d[maxn][maxn];
struct et
{
    int s,t,val,cost,next;
}e[maxm];
int fir[maxn],dis[maxn],v[maxn],q[maxm],pre[maxn];
bool inque[maxn];
int n,m,st,ed,tot,ans;

void prepare()
{
    for (int i=st;i<=ed;i++) dis[i]=-inf;
    int head=0,tail=1;
    q[1]=ed; dis[ed]=0; inque[ed]=1;
    while (head<tail)
    {
        int now=q[++head];
        for (int j=fir[now];j;j=e[j].next)
        {
            int k=e[j].t;
            if (e[j^1].val&&dis[k]<dis[now]+e[j^1].cost)
            {
                dis[k]=dis[now]+e[j^1].cost;
                if (!inque[k]) q[++tail]=k,inque[k]=1;
            }
        }
        inque[now]=0;
    }
}

int dfs(int now,int flow)
{
    if (now==ed)
    {
        ans+=dis[st]*flow;
        return flow;
    }
    int sap=0;    v[now]=1;
    for (int j=fir[now];j;j=e[j].next)
    {
        int k=e[j].t;
        if (!v[k]&&e[j].val&&dis[now]==dis[k]+e[j].cost)
        {
            int tmp=dfs(k,min(e[j].val,flow-sap));
            e[j].val-=tmp;
            e[j^1].val+=tmp;
            sap+=tmp;
            if (sap==flow) return sap;
        }
    }
    return sap;
}

bool adjust()
{
    int tmp=-inf;
    for (int i=st;i<=ed;i++) if (v[i])
        for (int j=fir[i];j;j=e[j].next)
        {
            int k=e[j].t;
            if (!v[k]&&e[j].val) tmp=max(tmp,dis[k]+e[j].cost-dis[i]);
        }
    if (tmp==-inf) return 0;
    for (int i=st;i<=ed;i++) if (v[i])
        dis[i]+=tmp;
    return 1;
}

void add_edge(int x,int y,int z,int w)
{
    e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x]; fir[x]=tot;
    e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
}


LL count(int i, int j)
{
    return ((LL)abs(p[i].x-p[j].x)+(LL)abs(p[i].y-p[j].y));
}

bool judge(LL limit)
{
    st=0; ed=n+2; tot=1;
    add_edge(st, 1, 1, 0);
    add_edge(n, ed, 1, 0);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (d[i][j]<=limit)
                add_edge(i, j+1, inf, 1);
    for (int i=1;i<=n;i++)
        add_edge(i, i+1, inf, 0);
    prepare();
    do 
        do memset(v,0,sizeof(v));
        while (dfs(st,inf));
    while (adjust());
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
                d[i][j]=count(i,j);
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
