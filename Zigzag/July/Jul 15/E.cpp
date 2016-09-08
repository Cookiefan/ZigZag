#include <bits/stdc++.h>
#define maxn 220000
using namespace std;
typedef long long LL;
const LL oo=1000000007;
LL a[maxn];
int n;
LL p, q, r;

LL exp(LL a, LL b, LL p)
{
	a%=p;
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp=(tmp*a)%p;
		a=a*a%p;
		b=b/2;
	}
	return tmp;
}

LL rev(LL x)
{
	if (x==1) return 1;
	else return (oo-oo/x)*rev(oo%x)%oo;
}

int main()
{
	scanf("%d",&n);
	p=2;
	r=-1;
	for (int i=1;i<=n;i++)
	{
		scanf("%I64d",&a[i]);
		if (a[i]%2==0) r=1;
		p=exp(p, a[i], oo);
	}
	p=p*rev(2)%oo;
	q=(p+r+oo)%oo*rev(3)%oo;
	printf("%I64d/%I64d\n",q,p);	
	return 0;

}