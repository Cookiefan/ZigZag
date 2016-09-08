#include <bits/stdc++.h>
#define maxn 220000
using namespace std;
int a[maxn],b[maxn];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	int i=n, j=n, wa=0, wb=0;
	while (i>0)
	{
		while (a[i]<b[j] && j>0) j--;
		if (j==0) break;
		if (a[i]>b[j]) wa++, j--;
		i--;
	}
	i=n, j=n;
	while (i>0)
	{
		while (b[i]<a[j] && j>0) j--;
		if (j==0) break;
		if (b[i]>a[j]) wb++, j--;
		i--;
	}
	//cout<<wa<<' '<<wb<<endl;
	if (wa>n-wa && wb>n-wb) printf("Both\n");
	else if (wa<=n-wa && wb<=n-wb) printf("None\n");
	else if (wa>n-wa) printf("First\n");
	else printf("Second\n");
	return 0;
}