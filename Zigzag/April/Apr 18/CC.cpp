#include <bits/stdc++.h>
#define maxn 220000
#define inf 999999999
using namespace std;
int n,m;
typedef vector<int> vit;
vit a[maxn],b[maxn], p[2], ans[2];
int v[maxn];
bool flag[2];

int dfs(int x, int pick)
{
	int flag=1;
	v[x]=pick;
	p[pick].push_back(x);
	int num=a[x].size();
	for (int j=0;j<num;j++)
	{
		int y=a[x][j];
		if (v[y]==-1)
			flag&=dfs(y, pick);
		else
			flag&=(pick==v[y]);
	}
	num=b[x].size();
	for (int j=0;j<num;j++)
	{
		int y=b[x][j];
		if (v[y]==-1)
			flag&=dfs(y, pick^1);
		else
			flag&=(pick!=v[y]);
	}
	return flag;
}

bool get_ans(int o)
{
	
	bool flag;
	ans[o].clear();
	memset(v,-1,sizeof(v));
	for (int i=1;i<=n;i++)
		if (v[i]==-1)
		{
			p[0].clear(); p[1].clear();
			flag=dfs(i,0);
			//cout<<p[0].size()<<' '<<p[1].size()<<endl;
			if (!flag) return 0;
			else
			{
				int op=p[0].size()>p[1].size();
				ans[o].insert(ans[o].end(), p[op].begin(), p[op].end());
			}
		}
	return 1;
}


int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) a[i].clear(), b[i].clear();
	int x,y;
	char c;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d %c",&x,&y,&c);
		if (c=='B')
		{
			a[x].push_back(y);
			a[y].push_back(x);
		}
		else
		{
			b[x].push_back(y);
			b[y].push_back(x);
		}
	}
	flag[0]=get_ans(0);
	for (int i=1;i<=n;i++) swap(a[i],b[i]);
	flag[1]=get_ans(1);
	if (!flag[0] && !flag[1])
		printf("-1\n");
	else if (!flag[1] || (flag[0] && ans[0].size()<=ans[1].size()))
	{
		int num=ans[0].size();
		printf("%d\n",num);
		for (int i=0;i<=num-1;i++) printf(i==num-1?"%d\n":"%d ",ans[0][i]);
	}
	else
	{
		int num=ans[1].size();
		printf("%d\n",num);
		for (int i=0;i<=num-1;i++) printf(i==num-1?"%d\n":"%d ",ans[1][i]);
	}
	return 0;
}