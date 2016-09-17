#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main()
{
	int n;
	scanf("%d", &n);
	LL ans=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<i;j++)
		{
			if ((i+j)%2==0) ans+=(j-1)/2;
			else ans+=j/2;
		}
	printf("%I64d\n",ans);
	return 0;
}
