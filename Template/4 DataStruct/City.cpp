// Input
// 文件第一行包含三个整数N,M,Q，
// 分别表示城市的数目，可以修建的道路个数，及收到的消息个数。 
// 接下来M行，第i+1行有三个用空格隔开的整数Xi,Yi,Zi(1≤Xi,Yi≤n, 0≤Zi≤50000000)，
// 表示在城市Xi与城市Yi之间修建道路的代价为Zi。
// 接下来Q行，每行包含两个数k,d，表示输入的第k个道路的修建代价修改为d(即将Zk修改为d)。
// Output
// 输出包含Q行，第i行输出得知前i条消息后使城市连通的最小花费总和。
// Sample Input
// 5 5 3
// 1 2 1
// 2 3 2
// 3 4 3
// 4 5 4
// 5 1 5
// 1 6
// 1 1
// 5 3
// Sample Output
// 14
// 10
// 9
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define maxn 60000
#define maxm 120000
#define inf 2147483647
using namespace std;
struct et
{
    int s,t,pos,val;
}e[22][maxm],d[maxm],t[maxm];
struct adj
{
    int x,z;
}q[maxn];
int a[maxm],c[maxm];
int f[maxn],sum[maxn],size[maxn];
long long ans[maxm];
int n,m,p;

inline void fill(int tot)
{
    for (int i=1;i<=tot;i++) 
        f[d[i].s]=f[d[i].t]=0,size[d[i].s]=size[d[i].t]=1;
}
inline int find(int i)
{
    return (!f[i])?i:f[i]=find(f[i]);
}
inline void merge(int x,int y)
{
    int fx=find(x),fy=find(y);
    if (size[fx]<=size[fy]) f[fx]=fy,size[fy]+=size[fx];
    else f[fy]=fx,size[fx]+=size[fy];
}

inline bool cmp(et a,et b)
{
    return a.val<b.val;
}

inline void reduce(int &tot)
{
    int tmp=0;
    fill(tot);
    sort(d+1,d+tot+1,cmp);
    for (int i=1;i<=tot;i++)
    {
        if (find(d[i].s)!=find(d[i].t))
        {
            merge(d[i].s,d[i].t);
            t[++tmp]=d[i];
            c[d[i].pos]=tmp;
        }
        else 
        if (d[i].val==inf)
        {
            t[++tmp]=d[i];
            c[d[i].pos]=tmp;
        }
    }
    for (int i=1;i<=tmp;i++) d[i]=t[i];
    tot=tmp;
}

inline void connect(int &tot,long long &cnt)
{
    int tmp=0;
    fill(tot);
    sort(d+1,d+tot+1,cmp);
    for (int i=1;i<=tot;i++)
    {
        if (find(d[i].s)!=find(d[i].t)) 
        {
            merge(d[i].s,d[i].t);
            t[++tmp]=d[i];
        }
    }
    for (int i=1;i<=tmp;i++) f[t[i].s]=f[t[i].t]=0,size[t[i].s]=size[t[i].t]=1;
    for (int i=1;i<=tmp;i++)
        if (t[i].val!=-inf&&find(t[i].s)!=find(t[i].t))
            merge(t[i].s,t[i].t),cnt+=t[i].val;
    tmp=0;
    for (int i=1;i<=tot;i++)
        if (find(d[i].s)!=find(d[i].t)) 
        {
            t[++tmp]=d[i];
            c[d[i].pos]=tmp;
            t[tmp].s=find(d[i].s);
            t[tmp].t=find(d[i].t);
        }
    for (int i=1;i<=tmp;i++) d[i]=t[i];
    tot=tmp;
}

inline void solve(int l,int r,int now,long long cnt)
{
    int tot=sum[now];
    if (l==r) a[q[l].x]=q[l].z;//修改生效
    for (int i=1;i<=tot;i++) e[now][i].val=a[e[now][i].pos];
    for (int i=1;i<=tot;i++) d[i]=e[now][i],c[d[i].pos]=i;  
    if (l==r)
    {
        ans[l]=cnt;
        fill(tot);
        sort(d+1,d+tot+1,cmp);
        for (int i=1;i<=tot;i++)
            if (find(d[i].s)!=find(d[i].t))
                merge(d[i].s,d[i].t),ans[l]+=d[i].val;
        return ;
    }
    for (int i=l;i<=r;i++) d[c[q[i].x]].val=-inf;
    connect(tot,cnt);
    for (int i=l;i<=r;i++) d[c[q[i].x]].val=inf;
    reduce(tot);
    for (int i=1;i<=tot;i++) e[now+1][i]=d[i];
    sum[now+1]=tot;
    int mid=(l+r)>>1;
    solve(l,mid,now+1,cnt);
    solve(mid+1,r,now+1,cnt);
}    

int main()
{
    //freopen("city.in","r",stdin);
    //freopen("city.out","w",stdout);
    scanf("%d%d%d",&n,&m,&p);
    int x,y;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&a[i]);
        e[0][i].s=x; e[0][i].t=y; e[0][i].val=a[i];
        e[0][i].pos=i;
    }
    for (int i=1;i<=p;i++)
        scanf("%d%d",&q[i].x,&q[i].z);
    sum[0]=m;
    solve(1,p,0,0);
    for (int i=1;i<=p;i++)
        printf("%lld\n",ans[i]);
    return 0;
}