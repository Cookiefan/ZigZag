#include <bits/stdc++.h>
#define maxn 120000
using namespace std;

int a[maxn];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1, a+n+1);
	int tmp=a[n]+1;
	for (int i=1;i<n;i++) tmp-=a[i];
	printf("%d\n", tmp);
	return 0;
}