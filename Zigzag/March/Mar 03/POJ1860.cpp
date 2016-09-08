#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define maxn 300
#define maxm 1200
using namespace std;
deque<double>que;
double dis[maxn];
bool inque[maxn];
int fir[maxn],freq[maxn];
int n,m,bg,tot;
double s;

struct edge
{
	int s,t,next;
	double r,c;
}e[maxm];

bool spfa(int st, double cur)
{
	for (int i=1;i<=n;i++) dis[i]=0;
	memset(inque,0,sizeof(inque));
	memset(freq,0,sizeof(freq));
	dis[st]=cur;
	que.push_back(st);
	inque[st]=1;
	while (!que.empty())
	{
		int now=que.front();
		que.pop_front();
		inque[now]=0;
		for (int j=fir[now];j;j=e[j].next)
		{
			int k=e[j].t;
			if (dis[k]<(dis[now]-e[j].c)*e[j].r)
			{
				dis[k]=(dis[now]-e[j].c)*e[j].r;
				if (!inque[k])
				{
					que.push_back(k);
					inque[k]=1;
					if (++freq[k]>n) return 1;
				}
			}
		}
	}
	return 0;
}

void add_edge(int x,int y,double r,double c)
{
	e[++tot].s=x; e[tot].t=y; e[tot].r=r; e[tot].c=c;
	e[tot].next=fir[x]; fir[x]=tot;
}

int main()
{

	scanf("%d%d%d%lf",&n,&m,&bg,&s);
	int a,b;
	double ra,rb,ca,cb;
	tot=0;
	memset(fir,0,sizeof(fir));
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%lf%lf%lf%lf",&a,&b,&ra,&ca,&rb,&cb);
		add_edge(a,b,ra,ca);
		add_edge(b,a,rb,cb);
	}
	//for (int i=1;i<=tot;i++) printf("%d %d %lf %lf\n",e[i].s,e[i].t,e[i].r,e[i].c);
	printf(spfa(bg,s)?"YES\n":"NO\n");
	return 0;
}