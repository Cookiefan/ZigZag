#include <bits/stdc++.h>
#define maxn 120000
using namespace std;

int main()
{
	int a,b,ans=0;
	scanf("%d%d",&a,&b);
	while (a && b)
	{
		if (a<=b)
		{
			a+=1;
			b-=2;
		}
		else
		{
			a-=2;
			b+=1;
		}
		if (a>=0 && b>=0) ans++;
		else break;
	}
	printf("%d\n",ans);
	return 0;
}