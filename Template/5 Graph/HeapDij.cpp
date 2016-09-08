//堆DJ
struct node
{
	int id,dis;
	node(){}
	node(int x,int y)
	{
		id=x; dis=y;
	}
	friend bool operator <(node a,node b)
	{ 
		return a.dis>b.dis;
	}
};

priority_queue<node> q;

void dij(int st)
{
	for (int i=1;i<=n;i++) dis[i]=inf;
	memset(vis,0,sizeof(vis));
	while (!q.empty()) q.pop();
	q.push(node(st,0));
	dis[st]=0;
	while (!q.empty())
	{
		int i=q.top().id;
		q.pop();
		if (vis[i]) continue;
		vis[i]=1;
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (!vis[k]&&dis[i]+e[j].val<dis[k])
			{
				dis[k]=dis[i]+e[j].val;
				q.push(node(k,dis[k]));
			}
		}
	}
}