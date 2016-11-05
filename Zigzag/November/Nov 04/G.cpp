#include <bits/stdc++.h>
using namespace std;
#define maxn 1020
#define inf 99999999
typedef pair<int,int> pii;
int a[maxn][maxn];
int vis[maxn], dg[maxn];
int n, tot;
vector<int> ans;

int chose(){
	int mx=0, x=0;
	for (int i=1;i<=tot;i++){
		if (vis[i]) continue;
		int tm=0;
		for (int j=1;j<=tot;j++){
			if (vis[j] || j==i)continue;
			tm=max(tm, a[i][j]);
		}
		if (tm>mx){
			mx=tm;
			x=i;
		}
	}
	return x;
}

void modify(int x){
	int mi=inf;
	vis[x]=1;
	for (int i=1;i<=tot;i++){
		if (vis[i]) continue;
		mi=min(mi, a[x][i]);
	}
	if (mi==inf) return ;
	dg[x]++;
	dg[++tot]=1;
	vis[tot]=1;
	for (int i=1;i<=tot;i++){
		if (vis[i]) continue;
		a[tot][i]=a[x][i]-1;
		a[i][tot]=a[i][x]-1;
		if (a[tot][i]==1){
			vis[i]=1;
			dg[tot]++;
			dg[i]++;
		}
	}
	vis[tot]=0;
}

void show(){
	for (int i=1;i<=tot;i++){
		for (int j=1;j<=tot;j++)
			cout<<a[i][j]<<' ';
		cout<<endl;
	}
}

int main()
{
	// freopen("G.in","r",stdin);
	while (scanf("%d",&n)!=EOF){
		memset(a,0,sizeof(a));
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				scanf("%d",&a[i][j]);
		memset(vis,0,sizeof(vis));
		memset(dg,0,sizeof(dg));
		tot=n;
		ans.clear();
		while(1){
			int now=chose();
			if (!now) break;
			modify(now);
		}
		for (int i=n+1;i<=tot;i++){
			ans.push_back(dg[i]);
		}
		sort(ans.begin(), ans.end());
		for (int i=0;i<ans.size();i++)
			printf(i==ans.size()-1?"%d\n":"%d ",ans[i]);
		//cout<<endl;
	}
	return 0;
}