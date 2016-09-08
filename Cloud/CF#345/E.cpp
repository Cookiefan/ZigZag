#include <bits/stdc++.h>
#define maxn 1200000
using namespace std;

struct node
{
	int num,pos;
	node(){}
	node(int num, int pos):num(num),pos(pos){}
	friend bool operator <(node a, node b)
	{
		return a.num<b.num;
	}
};
vector<node>a[maxn],b[maxn];
vector<int>t[maxn],tt[maxn];
int idg[maxn],vis[maxn],dfn[maxn],low[maxn],col[maxn];
int number[maxn];
stack<int> stk;
deque<int> que;
int ts,num,cnt;
int n,m;

void tarjan(int x)
{
	dfn[x]=low[x]=ts++;
	stk.push(x);
	vis[x]=1;
	for (int i=0, len=t[x].size();i<len;i++)
	{
		int y=t[x][i];
		if (!vis[y]) tarjan(y);
		if (vis[y]<2) low[x]=min(low[x],low[y]);
	}
	if (dfn[x]==low[x])
	{
		num++;
		int now;
		do
		{
			now=stk.top(); stk.pop();
			col[now]=num;
			vis[now]=2;
		}while (now!=x);
	}
}

void solve()
{
	que.clear();
	for (int i=1;i<=num;i++)
		if (idg[i]==0)
		{
			que.push_back(i);
			number[i]=1;
		}
	cnt=1;
	while (!que.empty())
	{
		int x=que.front();
		que.pop_front();
		for (int j=0, len=tt[x].size();j<len;j++)
		{
			int y=tt[x][j];
			if (--idg[y]==0)
			{
				que.push_back(y);
				number[y]=number[x]+1;
			}
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	int x;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			scanf("%d",&x);
			a[i].push_back(node(x,i*m+j));
			b[j].push_back(node(x,i*m+j));
		}
	for (int i=0;i<n;i++)
	{
		sort(a[i].begin(),a[i].end());
		for (int j=0;j<m-1;j++)
		{
			t[a[i][j].pos].push_back(a[i][j+1].pos);
			if (a[i][j].num==a[i][j+1].num)
				t[a[i][j+1].pos].push_back(a[i][j].pos);
		}
	}
	for (int j=0;j<m;j++)
	{
		sort(b[j].begin(),b[j].end());
		for (int i=0;i<n-1;i++)
		{
			t[b[j][i].pos].push_back(b[j][i+1].pos);
			if (b[j][i].num==b[j][i+1].num)
				t[b[j][i+1].pos].push_back(b[j][i].pos);
		}
	}
	memset(vis,0,sizeof(vis));
	for (int i=0;i<n*m;i++)
		if (!vis[i])
		{
			while (!stk.empty()) stk.pop();
			ts=0;
			tarjan(i);
		}

	memset(idg,0,sizeof(idg));
	for (int i=0;i<n*m;i++)
	{
		for (int j=0, len=t[i].size();j<len;j++)
		{
			int k=t[i][j];
			if (col[k]!=col[i])
			{
				tt[col[i]].push_back(col[k]);
				idg[col[k]]++;
			}
		}
	}
	
	solve();
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m-1;j++)
			printf("%d ",number[col[i*m+j]]);
		printf("%d\n",number[col[i*m+m-1]]);
	}
	return 0;
}