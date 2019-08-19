#include <bits/stdc++.h>
#define maxn 100200
using namespace std;


namespace DT{
	vector<int> G[maxn], H[maxn];
	vector<int> S[maxn], T[maxn]; //S是semi树，T是domain树
	int fa[maxn],min_fa[maxn]; //min_fa是semi最小的祖先
	int dfn[maxn],rd[maxn], pre[maxn]; //DFS序号，DFS序号对应的点号，DFS树前驱
	int semi[maxn], idom[maxn];//半支配节点，最近支配节点
	int ans[maxn]; //ans用来存子树size
	int time_stamp, n;

	void init(){
		time_stamp = 0;
		for (int i=1;i<=n;i++) {
			semi[i]=min_fa[i]=fa[i]=i;
			G[i].clear();
			H[i].clear();
			S[i].clear();
			T[i].clear();
		}
		memset(dfn, 0, sizeof(dfn));
		memset(ans, 0, sizeof(ans));
	}
	void add_edge(int x, int y){
		G[x].push_back(y);
		H[y].push_back(x);
	}
	int upfind(int x){
		if (fa[x]==x) return x;
		int y = fa[x];
		fa[x] = upfind(fa[x]);
		if (dfn[semi[min_fa[y]]] < dfn[semi[min_fa[x]]]) min_fa[x]=min_fa[y];
		return fa[x];
	}
	void dfs(int x){
		dfn[x] = ++time_stamp;
		rd[dfn[x]] = x;
		for (int &y:G[x])
			if (!dfn[y]) {
				pre[y]=x;
				dfs(y);
			}
	}
	void solve(int rt){
		dfs(rt);
		for (int i=time_stamp;i>=2;i--){
			int x=rd[i], tmp = time_stamp+1;
			for (int &y:H[x]){
				if (!dfn[y]) continue;
				upfind(y); 
				tmp = min(tmp, dfn[semi[min_fa[y]]]);
			}
			fa[x]=pre[x];
			semi[x]=rd[tmp];
			S[semi[x]].push_back(x);
			x = pre[x];
			for (int &y:S[x]){
				// x==semi[y]
				upfind(y);
				int t = min_fa[y];
				if (semi[t]==x) idom[y]=x;
				else idom[y] = t;
			}
		}
		for (int i=2;i<=time_stamp;i++){
			int x = rd[i];
			if (idom[x] != semi[x]) idom[x]=idom[idom[x]];
			T[idom[x]].push_back(x);
		}
	}
	void get_ans(int x){
		ans[x]=1;
		for (int &y:T[x]){
			if (dfn[y]>dfn[x]){
				get_ans(y);
				ans[x]+=ans[y];
			}
		}
	}
}

int n, x;
int deg[maxn];

int main()
{
	cin>>n;
	DT::n = n+1;
	DT::init();
	memset(deg, 0, sizeof(deg));
	for (int i=1;i<=n;i++){
		cin>>x;
		while (x){
			DT::add_edge(x, i);
			deg[i]+=1;
			cin>>x;
		}
	}
	for (int i=1;i<=n;i++)
		if (!deg[i])
			DT::add_edge(n+1, i);
	DT::solve(n+1);
	DT::get_ans(n+1);
	for (int i=1;i<=n;i++)
		cout<<DT::ans[i]-1<<endl;
	return 0;
}