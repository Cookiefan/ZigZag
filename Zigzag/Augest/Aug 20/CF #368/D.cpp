#include <bits/stdc++.h>
#define maxn 100020
using namespace std;

vector< bitset<1005> >b;
typedef bitset<1005> bs;
int t[maxn][1005];
int ans[maxn];
int n,m,q;

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	int sign, x, y, z;
	b.clear();
	for (int i=1;i<=n;i++)
	{
		b.push_back(bs(0));
		t[0][i]=i-1;
	}
	ans[0]=0;
	for (int i=1;i<=q;i++)
	{
		bs now;
		int tmp=ans[i-1];
		scanf("%d",&sign);
		if (sign==1)
		{
			scanf("%d%d",&x,&y);
			for (int j=1;j<=n;j++) t[i][j]=t[i-1][j];
			now=b[t[i][x]];
			if (now[y]==0) tmp++;
			now[y]=1;
			b.push_back(now);
			t[i][x]=b.size()-1;
			printf("%d\n",ans[i]=tmp);
		}
		else if (sign==2)
		{
			scanf("%d%d",&x,&y);
			for (int j=1;j<=n;j++) t[i][j]=t[i-1][j];
			now=b[t[i][x]];
			if (now[y]==1) tmp--;
			now[y]=0;
			b.push_back(now);
			t[i][x]=b.size()-1;
			printf("%d\n",ans[i]=tmp);

		}
		else if (sign==3)
		{
			scanf("%d",&x);
			for (int j=1;j<=n;j++) t[i][j]=t[i-1][j];
			now=b[t[i][x]];
			for (int i=1;i<=m;i++)
			{
				if (now[i]==1) tmp--; else tmp++;
				now[i]=now[i]^1;
			}
			b.push_back(now);
			t[i][x]=b.size()-1;
			printf("%d\n",ans[i]=tmp);
		}
		else
		{
			scanf("%d",&x);
			for (int j=1;j<=n;j++) t[i][j]=t[x][j];
			printf("%d\n",ans[i]=ans[x]);
		}
	}
	return 0;
}