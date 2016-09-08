#include <bits/stdc++.h>
#define maxn 100
using namespace std;

long long a[maxn];

int main()
{
	int n;
	scanf("%d",&n);
	a[0]=1;
	for (int i=1;i<=n;i++) a[i]=a[i-1]*2;
	cout<<a[n]<<endl;


	
	
	return 0;
}