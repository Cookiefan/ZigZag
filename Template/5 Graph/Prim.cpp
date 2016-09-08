//prim算法
void prim()
{
    int ans=0;
    for (int i=1;i<=n;i++) d[i]=e[0][i],v[i]=0;
    v[0]=1;
    for (int i=1;i<=n;i++)
    {
        int min=inf,k;
        for (int j=1;j<=n;j++)
            if (!v[j]&&d[j]<min)
            {
                min=d[j];
                k=j;
            }
        v[k]=1;
        ans+=min;
        for (int j=1;j<=n;j++)
        if (!v[j]&&e[k][j]<d[j])
			d[j]=e[k][j];
    }
    printf("%d\n",ans);
}

//堆优化prim

priority_queue<node> q;

int prim(int n)
{
    int ans=0;
    memset(vis,0,sizeof(vis));
    for (int i=0;i<=n;i++) dis[i]=inf;
    while (!q.empty())q.pop();
	q.push(node(0,0));
    dis[0]=0;
    while (!q.empty())
    {
    	int i=q.top().id;
    	q.pop();
    	if (vis[i]) continue;
    	vis[i]=1;
    	ans+=dis[i];
        for (int j=fir[i];j;j=e[j].next)
        {
        	int k=e[j].t;
        	if (!vis[k] && e[j].val<dis[k])
        	{
				dis[k]=e[j].val;
				q.push(node(k,dis[k]));
        	}
		}
    }
    return ans;
}