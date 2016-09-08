#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t,s,x;
	scanf("%d%d%d",&t,&s,&x);
	if (s==1) if (x>=t) printf("YES\n"); else printf("NO\n");
	else if (x-t>=0 && ((x-t)%s==1 || (x-t)%s==0) && x!=t+1) printf("YES\n"); else printf("NO\n");
	return 0;
}