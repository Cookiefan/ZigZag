#include <bits/stdc++.h>
#define maxn 120
#define maxm 2200
#define inf 99999999
using namespace std;

struct point
{
	int x, y;
	point(){}
	point(int x, int y):
	x(x),y(y){}
	friend point operator +(point a, point b)
	{
		return point(a.x+b.x, a.y+b.y);
	};
};
const point dir[4]={point(1,0),point(0,1),point(-1,0),point(0,-1)};
int a[12][12], id[12][12];
struct edge
{
	int s, t, val, next;
}e[maxm];
queue<point> que;
int vis[12][12];
int fir[maxn],last[maxn];
int dis[maxn],gap[maxn];
int n,m,num,tot,st,ed,cnt,ans,tmp;

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
	st=0; ed=cnt+1; num=ed+1; tot=1;
	memset(fir,0,sizeof(fir));
	memset(last,0,sizeof(last));
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
}

void bfs(point st, int msk)
{
	que.push(st);
	vis[st.x][st.y]=1;
	while (!que.empty())
	{
		point now=que.front();
		
		que.pop();
		for (int i=0;i<4;i++)
		{
			point tmp=now+dir[i];
			if (!vis[tmp.x][tmp.y] && a[tmp.x][tmp.y]>0 && (msk>>(a[tmp.x][tmp.y]-1))&1)
				que.push(tmp);
			vis[tmp.x][tmp.y]=1;
		}
	}
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		memset(a,-1,sizeof(a));
		char c;
		int mx=0;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				scanf(" %c",&c);
				if (c=='.') a[i][j]=0;
				else a[i][j]=c-'0'+1;
				mx=max(mx, a[i][j]);
			}
		ans=0;
		for (int msk=0;msk<1<<mx;msk++)
		{
			memset(vis,0,sizeof(vis));
			memset(id,0,sizeof(id));
			tmp=0;
			for (int i=1;i<=n;i++)
				for (int j=1;j<=m;j++)
					if (!vis[i][j] && a[i][j]>0 &&( msk>>(a[i][j]-1))&1)
					{
						bfs(point(i,j), msk);
						tmp++;
					}
			cnt=0;
			for (int i=1;i<=n;i++)
				for (int j=1;j<=m;j++)
					if (!vis[i][j] && a[i][j]==0)
						id[i][j]=++cnt;
			init();
			for (int i=1;i<=n;i++)
				for (int j=1;j<=m;j++)
					if (id[i][j])
					{
						if ((i+j)&1)
						{
							add_edge(st, id[i][j], 1);
							for (int k=0;k<4;k++)
								if (id[i+dir[k].x][j+dir[k].y])
									add_edge(id[i][j], id[i+dir[k].x][j+dir[k].y], 1);
						}
						else
							add_edge(id[i][j], ed, 1);
					}
			ans=max(ans, tmp+cnt-max_flow());
		}
		printf("Case #%d: %d\n",o, ans);
	}
	return 0;
}