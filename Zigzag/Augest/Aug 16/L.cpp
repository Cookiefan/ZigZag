#include <bits/stdc++.h>
#define maxn 820
#define maxm 220020
#define inf 2000000000
using namespace std;

struct edge
{
	int s, t, val, next;
}e[maxm];

int pay[maxn], pro[maxn], t[maxn];
vector<int> w[maxn];
int v[maxn];
int n,m,p,k;
int fir[maxn], last[maxn], dis[maxn], gap[maxn];
int tot, st, ed, num;

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


int judge(int limit)
{
	st=0, ed=n+m+1; num=ed+1; tot=1;
	memset(fir,0,sizeof(fir));
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));

	memset(v,0,sizeof(v));
	for (int i=1;i<=n;i++)
		if (t[i]<=limit)
		{
			v[i]=1;
			add_edge(m+i, ed, pay[i]);
		}

	int sum=0;

	for (int i=1;i<=m;i++)
	{
		bool flag=1;
		int k=w[i].size();
		for (int j=0;j<k;j++)
			if (!v[w[i][j]]) flag=0;
		if (flag)
		{
			add_edge(st, i, pro[i]);
			sum+=pro[i];
			for (int j=0;j<k;j++)
				add_edge(i, m+w[i][j], inf);
		}
	}
	//for (int j=2;j<=tot;j+=2) cout<<e[j].s<<' '<<e[j].t<<' '<<e[j].val<<endl;
	int ans=max_flow();
	return sum-ans;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&p);
		for (int i=1;i<=n;i++) scanf("%d%d",&pay[i],&t[i]);
		int x;
		for (int i=1;i<=m;i++)
		{
			scanf("%d",&pro[i]);
			w[i].clear();
			scanf("%d",&k);
			for (int j=0;j<k;j++)
			{
				scanf("%d",&x);
				w[i].push_back(x);
			}
		}
		int l=0, r=1000000001, ans1=-1, ans2;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			int tmp=judge(mid);
			if (tmp>=p)
			{
				ans1=mid;
				ans2=tmp;
				r=mid-1;
			}
			else
				l=mid+1;
		}
		if (ans1!=-1)
			printf("Case #%d: %d %d\n",o, ans1, ans2);
		else
			printf("Case #%d: impossible\n", o);
	}
	return 0;
}