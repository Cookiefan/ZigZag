#include <bits/stdc++.h>
#define maxn 20
#define oo 1000000007
using namespace std;
int v[maxn][maxn],q[maxn];
int a[5]={0,1,2,2,3};
int n=4;

void perm(int k)
{
	if (k>n)
	{
		for (int i=1;i<=n;i++) cout<<a[i]<<' ';
		cout<<endl;
		return ;
	}
	for (int i=k;i<=n;i++)
	{
		if (!v[k][a[i]])
		{
			v[k][a[i]]=1;
			swap(a[k],a[i]);
			perm(k+1);
			swap(a[k],a[i]);
		}
	}
	memset(v[k],0,sizeof(v[k]));
}


int main()
{
	for (int i=0;i<=15;i++)
		memset(v[i],0,sizeof(v[i]));
	perm(1);
	return 0;
}