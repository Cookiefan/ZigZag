#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL a, b, g, x, y;
bool flag;

LL gcd(LL a,LL b)
{
    return (b==0?a:gcd(b, a%b));
}

LL solve(LL g){
	LL u=a*a-4*b*g;
	if (u<0) return -1;
	return sqrt(u);
}

int main()
{
	while (scanf("%I64d%I64d",&a,&b)!=EOF){
		x=0; y=0; flag=0;
		for (LL g=1;g*g<=a;g++)
			if (a%g==0)
			{
				LL tmp=solve(g);
				if (tmp!=-1){
					x=(a+tmp)/2;
					y=(a-tmp)/2;
				 	if (x>0 && y>0 && x+y==a && x*y==b*gcd(x,y)){
						flag=1;
						break;
					}
				}
				tmp=solve(a/g);
				if (tmp!=-1){
					x=(a+tmp)/2;
					y=(a-tmp)/2;
					if (x>0 && y>0 && x+y==a && x*y==b*gcd(x,y)){
						flag=1;
						break;
					}
				}
			}
		if (x>y) swap(x, y);
		if (flag) printf("%I64d %I64d\n", x, y);
		else printf("No Solution\n");
	}
	return 0;
}