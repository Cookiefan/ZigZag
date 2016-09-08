#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
typedef long long LL;
LL gcd(LL a, LL b)
{
    if (!b)
        return a;
    else
        return gcd(b, a % b);
}

LL n,m;

int main()
{
	while (scanf("%I64d %I64d",&n,&m)&& (n+m))
	{
		//cout<<n<<' '<<m<<endl;
		LL up=(m-1)*n;
		LL dw=m*m;
		//cout<<up<<' '<<dw<<endl;
		LL g=gcd(up, dw);
		printf("%I64d/%I64d\n",up/g, dw/g);
	}
	return 0;
}