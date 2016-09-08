//zkw最小费用流
int dfs(int now,int flow)
{
	if (now==ed)
	{
		fare+=dis[st]*flow;
		return flow;
	}
	v[now]=1;
	int sap=0;
	for (int j=fir[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!v[k]&&e[j].val&&dis[now]==dis[k]+e[j].cost)
		{
			int tmp=dfs(k,min(e[j].val,flow-sap));
			e[j].val-=tmp;
			e[j^1].val+=tmp;
			sap+=tmp;
			if (sap==flow)return sap;
		}
	}
	return sap;
}

bool adjust()
{
	int tmp=inf;
	for (int i=st;i<=ed;i++) if (v[i])
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (!v[k]&&e[j].val) tmp=min(tmp,dis[k]+e[j].cost-dis[i]);
		}
	if (tmp==inf) return 0;
	for (int i=st;i<=ed;i++) if (v[i])
		dis[i]+=tmp;
	return 1;
}

int main()
{
		do{
			do memset(v,0,sizeof(v));
			while (dfs(st,inf));
		}while (adjust());
}