#include <bits/stdc++.h>
using namespace std;
#define maxn 100200
typedef long long LL;
LL f[maxn], s[maxn], ans;
int vis[maxn];
int n,p;
struct edge{
	int s,t,val;
};
vector<int> q;
vector<edge> e[maxn];

void solve(int y){
	f[y]=s[y]*s[y];
	int mi=0;
	for (int i=0;i<q.size();i++){
		int x=q[i];
		if (f[x]+(s[y]-s[x])*(s[y]-s[x])+p<f[y]){
			f[y]=f[x]+(s[y]-s[x])*(s[y]-s[x])+p;
			mi=x;
		}
	}
	//cout<<mi<<endl;
	cout<<f[y]<<endl;
	ans=max(ans, f[y]);
}

void dfs(int x){
	vis[x]=1;
	for (int j=0;j<e[x].size();j++){
		int y=e[x][j].t;
		if (vis[y]) continue;
		q.push_back(y);
		s[y]=s[x]+e[x][j].val;
		solve(y);
		dfs(y);
		q.erase(q.end()-1);
	}
}

int main()
{
	freopen("II.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++){
		scanf("%d%d",&n,&p);
		int x, y, z;
		for (int i=1;i<=n;i++) e[i].clear();
		for (int i=1;i<n;i++){
			scanf("%d%d%d",&x, &y, &z);
			e[x].push_back((edge){x,y,z});
			e[y].push_back((edge){y,x,z});
		}
		ans=0;
		memset(vis,0,sizeof(vis));
		dfs(1);
		printf("%I64d\n",ans);
	}
	return 0;
}
