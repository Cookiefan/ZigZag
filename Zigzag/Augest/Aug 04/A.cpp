#include <bits/stdc++.h>
using namespace std;

int a[20],f[20];

int n,m;
int mul, ans;

int com(int a, int b)
{
	return f[a]/(f[b]*f[a-b]);
}

void dfs(int k)
{
	if (k>m)
	{
		ans+=mul;
		return ;
	}
	for (int i=a[k-1];i<=n;i++)
	{
		a[k]=i;
		mul*=com(a[k], a[k-1]);
		dfs(k+1);
		mul/=com(a[k], a[k-1]);
	}
}

int main()
{
	f[0]=1;
	for (int i=1;i<=10;i++) f[i]=f[i-1]*i;
	for (n=0;n<=6;n++)
	{
		for (m=2;m<=6;m++)
		{
			a[0]=0;
			mul=1;
			ans=0;
			dfs(1);
			cout<<ans<<' ';
		}
		cout<<endl;
	}
	return 0;
}