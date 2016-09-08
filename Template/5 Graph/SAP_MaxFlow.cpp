//最大流sap
struct edge
{
	int s,t,val,next;
}e[maxm];

void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].next=fir[x]; fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].next=fir[y]; fir[y]=tot;
}

int dfs(int x, int flow)
{
	if (x==ed) return flow;
	int sap=0;
	for (int j=last[x];j;j=e[j].next)
	{
		int y=e[j].t;
		if (e[j].val&&dis[x]==dis[y]+1)
		{
			last[x]=j;
			int tmp=dfs(y, min(e[j].val, flow-sap));
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
	gap[0]=num;
	memcpy(last,fir,sizeof(fir));
	int tmp=0;
	while (dis[st]<num) tmp+=dfs(st, inf);
	return tmp;
}

void init()
{
	st=0; ed=2*n+m+p+1; num=ed+1; tot=1;
	memset(fir,0,sizeof(fir));
	memset(last,0,sizeof(last));
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
}