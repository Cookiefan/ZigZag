#include <bits/stdc++.h>
using namespace std;

int f[200010];
int find(int x)
{
	return f[x]==-1?x:f[x]=find(f[x]);
}

bool merge(int x, int y)
{
	int fx=find(x), fy=find(y);
	if (fx!=fy)
	{
		f[fx]=fy;
		return 1;
	}
	return 0;
}

int main()
{
	freopen("A.in","w",stdout);
	int n;
	cout<<(n=10000)<<endl;
	memset(f,-1,sizeof(f));
	srand(time(0));
	for (int i=2;i<=n;i++)
	{
		int x, y;
		x=rand()%n+1, y=rand()%n+1;
		//cout<<x<<' '<<y<<endl;
		while (!merge(x, y))
		{
			x=rand()%n+1, y=rand()%n+1;
		}
		cout<<x<<' '<<y<<endl;
		
	}
	return 0;
}