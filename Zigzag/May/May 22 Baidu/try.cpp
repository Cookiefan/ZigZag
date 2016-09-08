#include <bits/stdc++.h>
using namespace std;
int a[1200000];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) a[i]=n-i+1;
	for (int i=1;i<=n;i++) nth_element(a+1, a+i, a+n+1);
	// for (int i=1;i<=n;i++) cout<<a[i]<<' '; cout<<endl;
	return 0;
}