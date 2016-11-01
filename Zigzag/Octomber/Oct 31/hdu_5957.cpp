#include <bits/stdc++.h>
using namespace std;
#define maxn 100200
typedef long long LL;
vector<int> t[maxn];
vector<int> lop,que;
int fa[maxn], vis[maxn], id[maxn], col[maxn];
int bfn[maxn], lc[maxn], rc[maxn];
int n,m,flag,qid,num;

void dfs(int x, int f){
	vis[x]=1;
	lop.push_back(x);
	for (int y:t[x]){
		if (vis[y] && y!=f){
			flag=1;
			return ;
		}
		else if (!vis[y]) dfs(y,x);
		if (flag) return ;
	}
	lop.erase(lop.end()-1);
}

void flood_fill(){
	int now=0;
	que.clear();
	memset(vis,0,sizeof(vis));
	memset(lc, 0, sizeof(lc));
	memset(rc, 0, sizeof(rc));
	memset(id, 0, sizeof(id));
	num=0;
	for (int x:lop){
		id[x]=num++;
		fa[x]=0;
		vis[x]=1;
		que.push_back(x);
		bfn[x]=que.size();
	}
	while (now<que.size()){
		int x=que[now++];
		for (int y:t[x])
			if (!vis[y]){
				fa[y]=x;
				vis[y]=1;
				que.push_back(y);
				bfn[y]=que.size();
				if (!lc[x]) lc[x]=y;
				rc[x]=y;
			}
	}
}

struct bit{
	LL b[maxn];
	int num;
	void add(int x,int z){
		for (int i=x;i<=num;i+=(i&-i)) b[i]+=z;
	}
	LL ask(int x){
		LL tmp=0;
		for (int i=x;i;i-=(i&-i)) tmp+=b[i];
		return tmp;
	}
	void init(int n){
		num=n;
		memset(b,0,sizeof(b));
	}
}S,T;

void add(int x,int y,int z){
	//cout<<x<<' '<<y<<endl;
	S.add(x,z); S.add(y+1,-z);
	T.add(x,z*x); T.add(y+1,-z*(y+1));
}

LL ask(int x,int y){
	LL tmp=S.ask(y)*(y+1)-S.ask(x-1)*x
		   -(T.ask(y)-T.ask(x-1));
	return tmp;
}

void modify(int x, int k, int z){
	if (col[x]==qid && z>0) return ;
	col[x]=qid;
	if (k>=0)
		add(bfn[x], bfn[x], z);
	if (k>=1 && lc[x] && rc[x])
		add(bfn[lc[x]], bfn[rc[x]], z);
	if (k>=2 && lc[x] && rc[x] && lc[lc[x]] && rc[rc[x]])
		add(bfn[lc[lc[x]]], bfn[rc[rc[x]]], z);
}

LL query(int x, int k, int z){
	if (col[x]==qid && z>0) return 0;
	col[x]=qid;
	LL tmp=0;
	if (k>=0)
		tmp+=ask(bfn[x], bfn[x]);
	if (k>=1 && lc[x] && rc[x])
		tmp+=ask(bfn[lc[x]], bfn[rc[x]]);
	if (k>=2 && lc[x] && rc[x] && lc[lc[x]] && rc[rc[x]])
		tmp+=ask(bfn[lc[lc[x]]], bfn[rc[rc[x]]]);
	return tmp*z;
}

int pre(int x){
	return lop[(id[x]-1+num)%num];
}
int nxt(int x){
	return lop[(id[x]+1+num)%num];
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++){
		scanf("%d",&n);
		for (int i=1;i<=n;i++) t[i].clear();
		int x,y,z;
		for (int i=1;i<=n;i++){
			scanf("%d%d",&x,&y);
			t[x].push_back(y);
			t[y].push_back(x);
		}
		memset(vis,0,sizeof(vis));
		flag=0;
		lop.clear();
		dfs(1,0);
		flood_fill();
		//for (int i=1;i<=n;i++) cout<<bfn[i]<<' '; cout<<endl;
		memset(col, 0, sizeof(col));
		scanf("%d",&m);
		char sign[20];
		S.init(n+1);
		T.init(n+1);
		for (qid=1;qid<=m;qid++){
			scanf(" %s",sign);
			if (sign[0]=='M'){
				scanf("%d%d%d",&x,&y,&z);
				if (!fa[x]){
					modify(x, y, z);
					if (y>=1){
						modify(pre(x), y-1, z);
						modify(nxt(x), y-1, z);
					}
					if (y>=2){
						modify(pre(pre(x)), y-2, z);
						modify(nxt(nxt(x)), y-2, z);
					}
				}
				else if (!fa[fa[x]]){
					modify(x, y, z);
					if (y>=1){
						modify(fa[x], y-1, z);
					}
					if (y>=2){
						modify(x, 0, -z);
						modify(pre(fa[x]), y-2, z);
						modify(nxt(fa[x]), y-2, z);
					}
				}
				else{
					modify(x, y, z);
					if (y>=1){
						modify(fa[x], y-1, z);
					}
					if (y>=2){
						modify(x, 0, -z);
						modify(fa[fa[x]], y-2, z);
					}
				}
			}
			else{
				LL ans=0;
				scanf("%d%d",&x,&y);
				if (!fa[x]){
					ans+=query(x, y, 1);
					if (y>=1){
						ans+=query(pre(x), y-1, 1);
						ans+=query(nxt(x), y-1, 1);
					}
					if (y>=2){
						ans+=query(pre(pre(x)), y-2, 1);
						ans+=query(nxt(nxt(x)), y-2, 1);
					}
				}
				else if (!fa[fa[x]]){
					ans+=query(x, y, 1);
					if (y>=1){
						ans+=query(fa[x], y-1, 1);
					}
					if (y>=2){
						ans+=query(x, 0, -1);
						ans+=query(pre(fa[x]), y-2, 1);
						ans+=query(nxt(fa[x]), y-2, 1);
					}
				}
				else{
					ans+=query(x, y, 1);
					if (y>=1){
						ans+=query(fa[x], y-1, 1);
					}
					if (y>=2){
						ans+=query(x, 0, -1);
						ans+=query(fa[fa[x]], y-2, 1);
					}
				}
				printf("%I64d\n",ans);
			}
		}
	}
	return 0;
}