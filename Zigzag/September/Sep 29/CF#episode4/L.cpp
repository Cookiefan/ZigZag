#include <bits/stdc++.h>
#define maxn 2200
using namespace std;

struct edge
{
	int s, t, val, flag, next;
};
vector<edge> e;
int fir[maxn];
void add_edge(int x, int y, int z, int w)
{
	e.push_back((edge){x, y, z, w, fir[x]});
	fir[x]=e.size()-1;
}
int dis[2][maxn], inque[maxn], idg[maxn], f[2][maxn];
int n,m,st,ed;

void spfa(int st, int flag)
{
	memset(dis[flag],0x3f,sizeof(dis[flag]));
	memset(inque,0,sizeof(inque));
	dis[flag][st]=0;
	queue<int> q;
	q.push(st);
	inque[st]=1;
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		inque[x]=0;
		for (int j=fir[x];j!=-1;j=e[j].next)
		{
			if (e[j].flag!=flag) continue;
			int y=e[j].t;
			if (dis[flag][y]>dis[flag][x]+e[j].val)
			{
				dis[flag][y]=dis[flag][x]+e[j].val;
				if (!inque[y])
				{
					q.push(y);
					inque[y]=1;
				}
			}
		}
	}
}

void topo(int st, int flag)
{
	queue<int> q;
	q.push(st);
	memset(f[flag],0,sizeof(f[flag]));
	f[flag][st]=1;
	while (!q.empty())
	{
		int x=q.front(); q.pop();
		for (int j=fir[x];j!=-1;j=e[j].next)
		{
			int y=e[j].t;
			if (e[j].flag==-1) continue;
			if (e[j].flag==flag) f[flag][y]+=f[flag][x];
			if (!(--idg[y])) q.push(y);
		}
	}	
}

int main()
{
	//freopen("L.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		e.clear();
		memset(fir,-1,sizeof(fir));
		int x, y, z;
		for (int i=0;i<m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			add_edge(x, y, z, 0);
			add_edge(y, x, z, 1);
		}
		scanf("%d%d",&st,&ed);
		spfa(st, 0);
		//for (int i=1;i<=n;i++) cout<<dis[0][i]<<' '; cout<<endl;
			// if (dis[0][ed]==0x3f3f3f3f)
			// {
			// 	printf("0\n");
			// 	continue;
			// }
		spfa(ed, 1);
		memset(idg,0,sizeof(idg));
		for (int i=0;i<e.size();i++) e[i].flag=-1;
		for (int i=0;i<e.size();i+=2)
			if (dis[0][e[i].s]+e[i].val==dis[0][e[i].t])
			{
				e[i].flag=0;
				idg[e[i].t]++;
			}
		topo(st, 0);

		memset(idg,0,sizeof(idg));
		for (int i=0;i<e.size();i++) e[i].flag=-1;
		for (int i=1;i<e.size();i+=2)
			if (dis[1][e[i].s]+e[i].val==dis[1][e[i].t])
			{
				e[i].flag=1;
				idg[e[i].t]++;
			}
		topo(ed, 1);
		int ans=f[0][ed];
		//cout<<"0: "<<ans<<endl;
		for (int i=0;i<e.size();i+=2)
			if (dis[0][e[i].s]+e[i].val==dis[0][e[i].t]+1 && dis[0][e[i].s]+e[i].val+dis[1][e[i].t]==dis[0][ed]+1)
			{
				//cout<<e[i].s<<' '<<e[i].t<<' '<<f[0][e[i].s]<<' '<<f[1][e[i].t]<<endl;
				ans+=f[0][e[i].s]*f[1][e[i].t];
			}

		// for (int i=0;i<e.size();i+=2)
		// 	cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<' '<<e[i].flag<<endl;
		// for (int i=1;i<=n;i++)
		// 	cout<<f[1][i]<<' '; cout<<endl;
		printf("%d\n",ans);
	}
	return 0;
}
