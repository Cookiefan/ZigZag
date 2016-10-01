#include <bits/stdc++.h>
#define maxn 100200
#define low 20
using namespace std;

vector<int> t[maxn];
int fa[maxn][22], dep[maxn],id[maxn];
int n,m,num;
char s[10];
map<string, int> mp;

int get_father(int x,int y)
{
	if (dep[x]>dep[y]) swap(x,y);
	for (int i=low;i>=0;i--)
		if (dep[fa[y][i]]>=dep[x]) y=fa[y][i];
	if (x==y) return x;
	for (int i=low;i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

int dis(int x, int y)
{
	int lca=get_father(x, y);
	return (dep[x]+dep[y]-2*dep[lca]+1);
}

struct pii
{
	int x, y, d;
	pii(){}
	pii(int x, int y):x(x),y(y),d(dis(x, y)){}
}mdp[maxn];

bool operator <(pii a, pii b)
{
	return a.d<b.d;
}

void dfs(int x)
{
	for (int k=1;k<=low;k++)
		fa[x][k]=fa[fa[x][k-1]][k-1];
	for (int y:t[x])
	{
		if (y==fa[x][0]) continue;
		fa[y][0]=x;
		dep[y]=dep[x]+1;
		dfs(y);
	}
}

int main()
{
	//freopen("E.in","r",stdin);
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		mp.clear();
		num=0;
		for (int i=1;i<=n;i++)
		{
			scanf(" %s", s);
			if (mp.count(s)==0) mp[s]=++num;
			id[i]=mp[s];
		}
		for (int i=1;i<=num;i++) mdp[i]=pii(0, 0);
		int x, y, u, v;
		for (int i=1;i<=n;i++) t[i].clear();
		for (int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			t[x].push_back(y);
			t[y].push_back(x);
		}
		dep[1]=1;
		dfs(1);
		for (int x=1;x<=n;x++)
		{
			if (mdp[id[x]].x==0)
				mdp[id[x]]=pii(x,x);
			else
			{
				int u=mdp[id[x]].x, v=mdp[id[x]].y;
				mdp[id[x]]=max(pii(u,v), max(pii(u, x), pii(v, x)));
			}
		}

		for (int i=1;i<=m;i++)
		{
			scanf(" %s", s);
			int a=mp.count(s)?mp[s]:-1;
			scanf(" %s", s);
			int b=mp.count(s)?mp[s]:-1;
			if (a==-1 || b==-1) printf("-1\n");
			else
			{
				pii ans;
				if (a==b) ans=mdp[a];
				else
				{
					x=mdp[a].x; y=mdp[a].y;
					u=mdp[b].x; v=mdp[b].y;
					ans=max(max(pii(x, u), pii(x, v)), max(pii(y, u), pii(y, v)));
				}
				printf("%d\n",ans.d);
			}
		}
	}

	return 0;
}