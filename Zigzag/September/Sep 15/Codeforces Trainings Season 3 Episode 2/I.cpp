#include <bits/stdc++.h>
#define maxn 50000
using namespace std;
typedef long long LL;
int n,m;
int a[maxn], f[12];
bool flag;
int main()
{
	scanf("%d",&n);
	int k;
	a[k=1]=0;
	f[0]=1;
	for (int i=1;i<=9;i++)
	{
		f[i]=3*f[i-1]+1;
		for (int j=k+1;j<=k*2;j++)
			a[j]=i;
		for (int j=k*2+1;j<=f[i];j++)
			a[j]=a[f[i]-j+1];
		k=f[i];
	}
	for (int i=1;i<=n;i++) cout<<a[i];
	cout<<endl;
	return 0;
}
