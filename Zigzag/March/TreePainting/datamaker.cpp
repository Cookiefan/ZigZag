#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
int v[maxn];
int f[maxn];

int find(int x)
{
	return (!f[x])?x:f[x]=find(f[x]);
}

int main()
{
	const int s[20]={5,10,50,100,500,1000,5000,10000,50000,100000,10,100,1000,1000,10000,10,101,1002,1003,10004};
	freopen("data.in","w",stdout);
	cout<<20<<endl;
	for (int i=0;i<10;i++)
	{
		int n=s[i];
		printf("%d\n",n);
		srand(time(0));
		memset(f,0,sizeof(f));
		for (int i=2;i<=n;i++)
		{
			int a=rand()%n+1;
			while (find(a)==find(i)) a=rand()%n+1;
			f[find(a)]=i;
			printf("%d %d\n",i,a);
		}
	}
	for (int i=10;i<15;i++)
	{
		int n=s[i];
		cout<<n<<endl;
		for (int i=2;i<=n;i++)
			cout<<i<<' '<<i-1<<endl;
	}
	for (int i=15;i<20;i++)
	{
		int n=s[i];
		cout<<n<<endl;
		for (int i=2;i<=n;i++)
			cout<<i<<' '<<1<<endl;
	}
	return 0;
}