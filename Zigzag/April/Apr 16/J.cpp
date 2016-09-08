#include <bits/stdc++.h>
#define maxn 2200
using namespace std;

string re;
int tmp[maxn],ans[maxn],v[maxn];
int n, m;

int main()
{
	srand(666);
	scanf("%d",&n);
	for (int i=0;i<n;i++) tmp[i]=rand()%2;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++) printf("%d",tmp[j]);
		printf("\n");
		fflush(stdout);
		scanf("%d",&m);
		if (m==n) return 0;
		else if (m==n/2) break;
		for (int j=i;j<n;j++) tmp[j]=rand()%2;
		//tmp[i]^=1;
	}
	ans[0]=tmp[0];
	tmp[0]^=1;
	for (int i=1;i<n;i++)
	{
		tmp[i]^=1;
		for (int j=0;j<n;j++) printf("%d",tmp[j]);
		printf("\n");
		fflush(stdout);
		scanf("%d",&m);
		tmp[i]^=1;
		if (m==0)
			ans[i]=tmp[i];
		else if (m==n/2)
			ans[i]=tmp[i]^1;
		else if (m==n)
			return 0;
	}
	for (int j=0;j<n;j++) printf("%d",ans[j]);
	printf("\n");
	fflush(stdout);
	scanf("%d",&m);
	if (m==n) return 0;
	for (int j=0;j<n;j++) printf("%d",ans[j]^1);
	printf("\n");
	fflush(stdout);
	scanf("%d",&m);
	return 0;
}