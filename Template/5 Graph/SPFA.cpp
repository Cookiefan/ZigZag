//负环spfa
queue<int> q;

bool neg_loop(int st)
{
	while (!q.empty()) q.pop();
	for (int i=0;i<=n;i++) dis[i]=inf;
	memset(times,0,sizeof(times));
	memset(vis,0,sizeof(vis));
	q.push(st);
	vis[st]=1;
	times[st]=1;
	dis[st]=0;
	while (!q.empty())
	{
		int i=q.front();
		q.pop();
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (dis[k]>dis[i]+e[j].val)
			{
				dis[k]=dis[i]+e[j].val;
				if (!vis[k])
				{
					q.push(k);
					vis[k]=1;
					times[k]++;
					if (times[k]>=n) return 1;
				}
			}
		}
		vis[i]=0;
	}
	return 0;
}