#include <bits/stdc++.h>
using namespace std;
#define maxn 10200
#define maxm 100020
#define inf 999999999
struct edge{
	int s, t, val, next;
}e[maxm];
int fir[maxn],last[maxn];
int dis[maxn],gap[maxn];
int st,ed,num,tot;

void add_edge(int x,int y,int z){
	e[++tot].s=x; e[tot].t=y; e[tot].val=z;
	e[tot].next=fir[x]; fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].val=0;
	e[tot].next=fir[y]; fir[y]=tot;
}
int dfs(int x, int flow){
	if (x==ed) return flow;
	int sap=0;
	for (int j=last[x];j;j=e[j].next){
		int y=e[j].t;
		if (e[j].val&&dis[x]==dis[y]+1){
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
int maxflow(){
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
	gap[0]=num;
	memcpy(last,fir,sizeof(fir));
	int tmp=0;
	while (dis[st]<num) tmp+=dfs(st,inf);
	return tmp;
}
void init(int s, int t){
	st=s; ed=t; num=ed+1; tot=1;
	memset(fir,0,sizeof(fir));
}
int f[maxn];
int n,m;

int main()
{
	//freopen("DTS.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++){
		scanf("%d%d",&n,&m);
		init(0,n+1);
		int x, y, d, b;
		memset(f,0,sizeof(f));
		for (int i=1;i<=m;i++){
			scanf("%d%d%d%d",&x,&y,&d,&b);
			add_edge(x,y,b);
			f[y]+=d;
			f[x]-=d;
		}
		int sum=0;
		for (int i=1;i<=n;i++){
			if (f[i]>0) add_edge(st, i, f[i]),sum+=f[i];
			else add_edge(i, ed, -f[i]);
		}
		// for (int i=2;i<=tot;i+=2)
		// 	cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<endl;
		int ans=maxflow();
		//cout<<ans<<endl;
		if (ans==sum)
			printf("Case #%d: happy\n",o);
		else
			printf("Case #%d: unhappy\n",o);
	}

	return 0;
}