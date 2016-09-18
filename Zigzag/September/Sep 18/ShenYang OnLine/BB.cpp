#include <bits/stdc++.h>
#define maxn 50200
using namespace std;

int c[maxn][2], fa[maxn];
int col[maxn], cov[maxn], lc[maxn], rc[maxn], sum[maxn];
int n,m;

//LCT
void update(int x)
{
	if (!x) return ;
	lc[x]=(c[x][0])?lc[c[x][0]]:col[x]; 
	rc[x]=(c[x][1])?rc[c[x][1]]:col[x];
	sum[x]=sum[c[x][0]]+sum[c[x][1]]+1;
	if (col[x]==rc[c[x][0]]) sum[x]--;
	if (col[x]==lc[c[x][1]]) sum[x]--;
}

void change(int x, int z)
{
	if (!x) return ;
	col[x]=z;
	cov[x]=z;
	lc[x]=z;
	rc[x]=z;
	sum[x]=1;
}

void down(int x)
{
	if (cov[x])
	{
		change(c[x][0], cov[x]);
		change(c[x][1], cov[x]);
		cov[x]=0;
	}
}

bool is_root(int x)
{
	return c[fa[x]][0]!=x && c[fa[x]][1]!=x;
}

void relax(int x)
{
	if (!is_root(x)) relax(fa[x]);
	down(x);
}

void zigzag(int x)
{
	int y=fa[x], z=fa[y];
	int p=(c[y][1]==x), q=p^1;
	if (!is_root(y)) c[z][c[z][0]!=y]=x;
	fa[x]=z; fa[y]=x; fa[c[x][q]]=y;
	c[y][p]=c[x][q]; c[x][q]=y;
	update(y);
}

void splay(int x)
{
	relax(x);
	while (!is_root(x))
	{
		int y=fa[x], z=fa[y];
		if (!is_root(y))
			((c[y][0]==x) ^ (c[z][0]==y))?zigzag(x):zigzag(y);
		zigzag(x);
	}
	update(x);
}

int access(int x)
{
	int y;
	for (y=0; x; y=x, x=fa[x])
	{
		splay(x);
		c[x][1]=y;
		update(x);
	}
	return y;
}

int root(int x)
{
	while (fa[x]) x=fa[x];
	return x;
}

struct edge
{
	int t, z;
};
vector<edge> e[maxn];
int vis[maxn];
void dfs(int x)
{
	vis[x]=1;
	for (edge tmp:e[x])
		if (!vis[tmp.t])
		{
			int y=tmp.t;
			col[y]=tmp.z;
			fa[y]=x;
			dfs(y);
		}
}

void write(int x)
{
	cout<<x<<' '<<fa[x]<<' '<<c[x][0]<<' '<<c[x][1]<<' '<<col[x]<<' '<<sum[x]<<endl;
}

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		int x, y, z;
		for (int i=1;i<=n;i++)
			e[i].clear();
		for (int i=2;i<=n;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			z++;
			e[x].push_back((edge){y,z});
			e[y].push_back((edge){x,z});
		}
		memset(c,0,sizeof(c));
		memset(fa,0,sizeof(fa));
		memset(cov,0,sizeof(cov));
		memset(col,0,sizeof(col));
		memset(lc,0,sizeof(lc));
		memset(rc,0,sizeof(rc));
		memset(sum,0,sizeof(sum));
		memset(vis,0,sizeof(vis));
		fa[1]=0;
		dfs(1);
		char sign[10];
		for (int i=1;i<=m;i++)
		{
			scanf(" %s",sign);
			if (sign[0]=='C')
			{
				scanf("%d%d%d",&x,&y,&z);
				z++;
				if (x==y) continue;
				access(x);
				int lca=access(y);
				splay(x);
				change(c[lca][1], z);
				if (x!=lca) change(x, z);
			}
			else
			{
				scanf("%d%d",&x,&y);
				access(x);
				int lca=access(y);
				splay(x);
				//for (int j=1;j<=n;j++) write(j);
				int ans=sum[c[lca][1]];
				if (x!=lca)
				{
					ans+=sum[x];
					if (lc[x]==lc[c[lca][1]])
						ans--;
				}
				//if (x==y) ans=1;
				printf("%d\n",ans);
			}
		}
	}

	return 0;
}