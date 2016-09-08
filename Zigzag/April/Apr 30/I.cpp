#include <bits/stdc++.h>
#define maxn 520
using namespace std;
int a[maxn];
vector<int> b[maxn];
int n;
const int num=20;

int dis(int x, int y)
{
	int tmp=0;
	for (int i=0;i<num;i++)
		tmp+=(b[x][i]^b[y][i]);
	return tmp;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		for (int i=1;i<=n;i++)
		{
			int x=a[i];
			b[i].clear();
			for (int j=0;j<num;j++)
			{
				b[i].push_back(x%2);
				x=x/2;
			}
		}
		int mx=0;
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				mx=max(mx, dis(i,j));
		printf("%d\n",mx);
	}
	
	return 0;
}