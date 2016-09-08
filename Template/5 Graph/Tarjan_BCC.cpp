//tarjan割点
void tarjan(int now)
{
    dfn[now]=low[now]=++tim;
    v[now]=1;
    for (int j=fir[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!v[k])
		{
			tarjan(k);
			low[now]=min(low[now],low[k]);
			if (dfn[now]<=low[k]) v[now]++;
		}
		else
			low[now]=min(low[now],dfn[k]);
	}
	if ((dfn[now]==1&&v[now]>2)||(dfn[now]>1&&v[now]>1))
		cut[now]=1;
}
//tarjan割边
void tarjan(int i)
{
	vis[i]=1;
	dfn[i]=low[i]=++cnt;
	for (int j=fir[i];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!vis[k])
		{
			pre[k]=j^1;
			tarjan(k);
			low[i]=min(low[i],low[k]);
		}
		else if (j!=pre[i])
			low[i]=min(low[i],dfn[k]);
	}
	if (pre[i] && dfn[i]==low[i]) bridge[pre[i]]=bridge[pre[i]^1]=1;
}
