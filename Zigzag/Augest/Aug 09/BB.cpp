#include <bits/stdc++.h>
#define maxn 1200
using namespace std;

int n,m;
int a[maxn];
int sum, ans;

void dfs(int k)
{
	if (k>n)
	{
		int tmp=0;
		for (int i=1;i<=m;i++)
			tmp+=a[i]*a[i];
		ans+=tmp;
		sum++;
		return ;
	}
	for (int i=1;i<=m;i++)
	{
		a[i]++;
		dfs(k+1);
		a[i]--;
	}
}

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		sum=ans=0;
		dfs(0);
		sum/=m;
		cout<<ans*1.0/sum<<endl;
	}
	return 0;
}