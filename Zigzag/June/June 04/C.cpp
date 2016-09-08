#include <bits/stdc++.h>
using namespace std;

int main()
{
	int x,y,n,xx=0,yy=0;
	scanf("%d%d",&x,&y);
	scanf("%d",&n);
	int q,p,a,b;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&a,&p,&b,&q);
		if (p==a+b && q!=a+b)
		{
			xx++;
		}
		else
		if (q==a+b && p!=a+b)
		{
			yy++;
		}
		if (xx==x+1 || yy==y+1) break;
	}
	if (xx==x+1) printf("A\n%d\n",yy);
	else printf("B\n%d\n",xx);
	return 0;
}