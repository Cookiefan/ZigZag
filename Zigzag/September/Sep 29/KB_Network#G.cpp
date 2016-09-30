#include <bits/stdc++.h>
#define maxn 100200
#define maxm 400200
#define inf 99999999
using namespace std;

struct edge
{
	int s,t,val,next;
}e[maxm];
int tot;
int fir[maxn], last[maxn], gap[maxn], dis[maxn], vis[maxn];
int n,m,num,st,ed,ans;
typedef pair<int,int> pii;
pii p[maxn];
int q[maxm];

void add_edge(int x,int y,int z)
{
    e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].next=fir[x]; fir[x]=tot;
    e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].next=fir[y]; fir[y]=tot;
}

void prepare()
{
	memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(ed);
    vis[ed]=1;
    while (!q.empty())
    {
        int x=q.front(); q.pop();
        for (int j=fir[x];j;j=e[j].next)
        {
            int y=e[j].t;
            if (!vis[y])//min
            {
                dis[y]=dis[x]+1;
                gap[dis[y]]++;
                q.push(y);
                vis[y]=1;
            }
        }
    }
}

int dfs(int x,int flow)
{
    if (x==ed) return flow;
    int sap=0;
    for (int j=last[x];j;j=e[j].next)
    {
        int y=e[j].t;
        if (e[j].val&&dis[x]==dis[y]+1)
        {
        	last[x]=j;
            int tmp=dfs(y,min(e[j].val,flow-sap));
            e[j].val-=tmp;
            e[j^1].val+=tmp;
            sap+=tmp;
            if (sap==flow) return sap;
        }
    }
    if (dis[st]>=num) return sap;
	if (!(--gap[dis[x]])) dis[st]=num;
	++gap[++dis[x]];
	last[x]=fir[x];
    return sap;
}

int max_flow()
{
	int tmp=0;
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
	prepare();
	memcpy(last,fir,sizeof(fir));
	while(dis[st]<num) tmp+=dfs(st, inf);
	return tmp;
}

int init()
{
	memset(fir,0,sizeof(fir));
	tot=1; num=n;
	//st=; ed=;
}
int main()
{
	//freopen("G.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		init();
		st=ed=1;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&p[i].first,&p[i].second);
			if (p[i].first<p[st].first) st=i;
			if (p[i].first>p[ed].first) ed=i;
		}
		int x, y, z;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x, &y,&z);
			add_edge(x,y,z);
			add_edge(y,x,z);
		}
		cout<<st<<' '<<ed<<endl;

		printf("%d\n",max_flow());
	}
	return 0;
}

