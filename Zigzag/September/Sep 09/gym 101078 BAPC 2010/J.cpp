#include <bits/stdc++.h>
#define inf 999999999
#define maxn 5200
#define maxm 5200000
using namespace std;

//最大流sap
struct edge
{
	int s,t,val,next;
}e[maxm];
int fir[maxn], dis[maxn], gap[maxn], last[maxn];
int num,tot,st,ed;

typedef pair<int,int> pii;
string s[maxn];
pii p[maxn];
int n,m;

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
	st=0, ed=n+m+1, num=ed+1, tot=1;
	memset(fir,0,sizeof(fir));
	memset(last,0,sizeof(last));
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
}

bool judge(int x, int y)
{
	if (p[x].first<=p[y].first && p[y].first<=p[x].first+s[x].length()-1&&
		p[y].second<=p[x].second && p[x].second<=p[y].second+s[y].length()-1)
	{
		//cout<<x<<' '<<y<<' '<<s[x][p[y].first-p[x].first]<<' '<<s[y][p[x].second-p[y].second]<<endl;;
		return s[x][p[y].first-p[x].first]==s[y][p[x].second-p[y].second];
	}
	return 1;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=0;i<n+m;i++)
		{
			scanf("%d%d",&p[i].first,&p[i].second);
			cin>>s[i];
		}
		init();
		for (int i=1;i<=n;i++) add_edge(st, i, 1);
		for (int j=n+1;j<=n+m;j++) add_edge(j, ed, 1);
		for (int i=0;i<n;i++)
			for (int j=n;j<n+m;j++)
				if (!judge(i, j))
					add_edge(i+1, j+1, 1);
		//cout<<max_flow()<<endl;
		printf("%d\n",n+m-max_flow());			
	}
	return 0;
}