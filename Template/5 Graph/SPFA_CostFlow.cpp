//spfa费用流(max)
struct edge
{
	int s, t, val, cost, next;
}e[maxm];

void add_edge(int x, int y, int z, int w)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x], fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
}

void init()
{
	st=0, ed=n*m+1; tot=1;
	memset(fir,0,sizeof(fir));
	memset(dis,0,sizeof(dis));
}

bool find_path()
{
	for (int i=st;i<=ed;i++) dis[i]=inf;
	queue<int> q;
	q.push(st);
	dis[st]=0;
	inque[st]=1;
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		inque[x]=0;
		for (int j=fir[x];j;j=e[j].next)
		{
			int y=e[j].t;
			if (e[j].val && dis[y]>dis[x]+e[j].cost)
			{
				dis[y]=dis[x]+e[j].cost;
				pre[y]=j;
				if (!inque[y]) q.push(y), inque[y]=1;
			}
		}
	}
	return dis[ed]<inf;
}

int fare_flow()
{
	int fare=0, flow=0;
	while (find_path())
	{
		int tmp=inf;
		for (int j=pre[ed];j;j=pre[e[j].s]) tmp=min(tmp, e[j].val);
		for (int j=pre[ed];j;j=pre[e[j].s]) e[j].val-=tmp, e[j^1].val+=tmp;
		flow+=tmp;
		fare+=tmp*dis[ed];
	}
	return fare;
}