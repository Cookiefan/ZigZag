//zkw最大费用流
struct et
{
    int s,t,val,cost,next;
}e[maxm];
int fir[maxn],dis[maxn],vis[maxn],q[maxm],pre[maxn];
bool inque[maxn];
int n,m,st,ed,tot,ans;

void prepare()
{
    for (int i=st;i<=ed;i++) dis[i]=-inf;//min
    int head=0,tail=1;
    q[1]=ed; dis[ed]=0; inque[ed]=1;
    while (head<tail)
    {
        int now=q[++head];
        for (int j=fir[now];j;j=e[j].next)
        {
            int k=e[j].t;
            if (e[j^1].val&&dis[k]<dis[now]+e[j^1].cost)//min
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
    int sap=0;    vis[now]=1;
    for (int j=fir[now];j;j=e[j].next)
    {
        int k=e[j].t;
        if (!vis[k]&&e[j].val&&dis[now]==dis[k]+e[j].cost)
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
    for (int i=st;i<=ed;i++) if (vis[i])
        for (int j=fir[i];j;j=e[j].next)
        {
            int k=e[j].t;
            if (!vis[k]&&e[j].val) tmp=max(tmp,dis[k]+e[j].cost-dis[i]);//min
        }
    if (tmp==-inf) return 0;
    for (int i=st;i<=ed;i++) if (vis[i])
        dis[i]+=tmp;
    return 1;
}

void add_edge(int x,int y,int z,int w)
{
    e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x]; fir[x]=tot;
    e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
}

int zkw_flow()
{
	ans=0;
	prepare();
	do{
		do memset(v,0,sizeof(v));
		while (dfs(st,inf));
	}while (adjust());
}

int init()
{
	memset(fir,0,sizeof(fir));
	tot=1; st=0; ed=n+2;
}