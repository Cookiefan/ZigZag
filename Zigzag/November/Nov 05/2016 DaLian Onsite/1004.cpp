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
	LL t=sqrt(u);
	if (t*t==u) return t;
	else return -1;
}

int main()
{
	while (scanf("%I64d%I64d",&a,&b)!=EOF){
		x=0; y=0; flag=0;
		for (int g=1;g*g<=a;g++){
			LL tmp=solve(g);
			if (tmp!=-1){
				x=(a+tmp)/2;
				y=(a-tmp)/2;
				if (x>0 && y>0 && x+y==a && (LL)x*y/gcd(x,y)==b){
					flag=1;
					break;
				}
			}
			tmp=solve(a/g);
			if (tmp!=-1){
				x=(a+tmp)/2;
				y=(a-tmp)/2;
				if (x>0 && y>0 && x+y==a && (LL)x*y/gcd(x,y)==b){
					flag=1;
					break;
				}
			}
		}
		if (flag) printf("%I64d %I64d\n", x, y);
		else printf("No Solution\n");
	}
	return 0;
}