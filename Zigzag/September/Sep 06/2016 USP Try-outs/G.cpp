#include <bits/stdc++.h>
#define maxn 200020
using namespace std;

int fa[maxn][50], dep[maxn];
int head[maxn], tail[maxn];
int v[maxn];
int n, num;

void set_father(int x)
{
	for (int i=1;i<=22;i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
}

int get_father(int x, int y)
{
	for (int i=22;i>=0;i--)
		if (dep[fa[y][i]]>dep[x]) y=fa[y][i];
	return y;
}

int main()
{
	scanf("%d",&n);
	int x, y;
	char sign;
	head[0]=tail[0]=num=0;
	fa[0][0]=dep[0]=0;
	for (int i=1;i<=n;i++)
	{
		scanf(" %c",&sign);
		if (sign=='E')
		{
			scanf("%d%d",&x,&y);
			head[i]=head[x];
			tail[i]=++num;
			v[tail[i]]=y;
			fa[tail[i]][0]=tail[x];
			dep[tail[i]]=dep[tail[x]]+1;
			set_father(tail[i]);
			//cout<<head[i]<<' '<<tail[i]<<endl;
		}
		else
		{
			scanf("%d",&x);
			head[i]=head[x];
			tail[i]=tail[x];
			head[i]=get_father(head[i], tail[i]);
			//cout<<head[i]<<' '<<tail[i]<<endl;
			printf("%d\n",v[head[i]]);
		}
	}
	return 0;
}