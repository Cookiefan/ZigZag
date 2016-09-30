	#include <bits/stdc++.h>
	#define maxn 100200
	#define maxm 800200
	#define inf 99999999
	using namespace std;

	struct edge
	{
	    int s,t,val,next,cost;
	}e[maxm];
	int tot;
	int fir[maxn], last[maxn], dis[maxn], vis[maxn], inque[maxn];
	int n,m,num,st,ed,ans;
	typedef pair<int,int> pii;
	pii p[maxn];
	int q[maxm];

	void prepare()
	{
	    for (int i=1;i<=n;i++) dis[i]=inf;//min
	    queue<int> q;
	    q.push(ed); dis[ed]=0; inque[ed]=1;
	    while (!q.empty())
	    {
	        int now=q.front();
	        inque[now]=0;
	        q.pop();
	        for (int j=fir[now];j;j=e[j].next)
	        {
	            int k=e[j].t;
	            if (e[j^1].val&&dis[k]>dis[now]+e[j^1].cost)//min
	            {
	                dis[k]=dis[now]+e[j^1].cost;
	                if (!inque[k]) q.push(k),inque[k]=1;
	            }
	        }
	    }
	}

	int dfs(int now,int flow)
	{
	    if (now==ed)
	    {
	        ans+=flow;
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
	    int tmp=inf;
	    for (int i=1;i<=n;i++) if (vis[i])
	        for (int j=fir[i];j;j=e[j].next)
	        {
	            int k=e[j].t;
	            if (!vis[k]&&e[j].val) tmp=min(tmp,dis[k]+e[j].cost-dis[i]);//min
	        }
	    if (tmp==inf) return 0;
	    for (int i=1;i<=n;i++) if (vis[i])
	        dis[i]+=tmp;
	    return 1;
	}

	void add_edge(int x,int y,int z,int w)
	{
	    e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x]; fir[x]=tot;
	    e[++tot].s=y; e[tot].t=x; e[tot].val=z; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
	}

	int zkw_flow()
	{
	    ans=0;
	    prepare();
	    do{
	        do
	        {
	            memset(vis,0,sizeof(vis));
	        }while (dfs(st,inf));
	    }while (adjust());
	    return ans;
	}

	int init()
	{
	    memset(fir,0,sizeof(fir));
	    tot=1;
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
	            add_edge(x,y,z,1);
	        }
	        // cout<<st<<' '<<ed<<endl;
	        // for (int i=2;i<=tot;i+=2)
	        // {
	        //     cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<endl;
	        // }
	        printf("%d\n",zkw_flow());
	    }
	    return 0;
	}