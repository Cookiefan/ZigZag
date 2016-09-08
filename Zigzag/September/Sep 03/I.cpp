#include <bits/stdc++.h>
#define maxn 120000
using namespace std;

int col[maxn], sum[maxn], f[maxn];
struct edge
{
	int t, id;
	edge(){}
	edge(int t, int id):t(t),id(id){}
};
vector<edge> t[maxn];
queue<int> que;
map<int,int> col_map[maxn];
typedef map<int,int>::iterator mit;
typedef vector<edge>::iterator vit;

int n;

void change(int x, int y)
{
	for (auto t:col_map[y])
	{
		if (col_map[x].find(t.first)==col_map[x].end())
			col_map[x][t.first]=0;
		col_map[x][t.first]+=t.second;
		if (col_map[x][t.first]==sum[t.first])
			col_map[x].erase(t.first);
	}
	col_map[y].clear();
}

void dfs(int x, int fa, int id)
{
	for (auto j:t[x]) if (j.t!=fa)
	{
		dfs(j.t, x, j.id);
		change(x, j.t);
	}
	if (col_map[x].find(col[x])==col_map[x].end())
		col_map[x][col[x]]=0;
	col_map[x][col[x]]++;
	f[id]=0;
	
	if (col_map[x][col[x]]==sum[col[x]])
		col_map[x].erase(col[x]);
	f[id]=col_map[x].size();
}

int main()
{
	freopen("HH.in","r",stdin);
	freopen("H.out","w",stdout);
	while (scanf("%d",&n)!=EOF)
	{
		memset(sum,0,sizeof(sum));
		for (int i=1;i<=n;i++)
		{
			t[i].clear();
			col_map[i].clear();
			scanf("%d",&col[i]);
			sum[col[i]]++;
		}
		int x,y;
		for (int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			t[x].push_back(edge(y, i));
			t[y].push_back(edge(x, i));
		}
		int rot=rand()%n+1;
		dfs(rot, 0, 0);
		for (int i=1;i<n;i++)
			printf("%d\n",f[i]);
	}

	return 0;
}