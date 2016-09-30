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

/*
input:
2
5 7
1 3 3
2 3 4
2 4 3
1 5 6
4 5 3
1 4 4
3 4 2
4 5
6 7
1 2 1
2 3 6
4 5 5
5 6 3
1 4 6
2 5 5
3 6 4
1 6
output:
9
6
*/