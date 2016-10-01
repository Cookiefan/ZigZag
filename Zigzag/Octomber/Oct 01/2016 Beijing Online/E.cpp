#include <bits/stdc++.h>
#define maxn 100200
#define low 18
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

typedef pair<int, int> pii;
pii mdp[maxn];

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
		for (int i=1;i<=num;i++) mdp[i]=pii(0,0);
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
		for (int i=1;i<=n;i++)
		{
			int x=i;
			if (!mdp[id[x]].first)
				mdp[id[x]]=pii(x,x);
			else
			{
				tie(u,v)=mdp[id[x]];
				int dis_1=dis(u, v);
				int dis_2=dis(u, x);
				int dis_3=dis(x, v);
				if (dis_2>=dis_3 && dis_2>=dis_1)
					mdp[id[x]].second=x;
				else if (dis_3>=dis_2 && dis_3>=dis_1)
					mdp[id[x]].first=x;
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
				int ans;
				if (a==b) ans=dis(mdp[a].first, mdp[a].second);
				else
				{
					tie(x, y)=mdp[a];
					tie(u, v)=mdp[b];
					ans=max(max(dis(x, u), dis(x, v)), max(dis(y, u), dis(y, v)));
				}
				printf("%d\n",ans);
			}
		}
	}

	return 0;
}