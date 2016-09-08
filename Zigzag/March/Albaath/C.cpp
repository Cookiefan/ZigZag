#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
int a[maxn];
int n;
long long sum[2],ans;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		sum[0]=sum[1]=ans=0;
		for (int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			sum[i%2]+=a[i];
		}
		ans=sum[0];
		for (int i=0;i<n;i++)
		{
			sum[0]-=a[i];
			sum[1]+=a[i];
			swap(sum[0],sum[1]);
			ans=max(ans,sum[0]);	
		}
		printf("%I64d\n",ans);
	}
	return 0;
}