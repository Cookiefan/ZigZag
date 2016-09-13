#include <bits/stdc++.h>
#define maxn 202000
using namespace std;
typedef long long LL;
const LL w=5;
const LL oo=1e9+7;
struct PP
{
	LL x, y;
	PP(){}
	PP(LL x, LL y):x(x%oo), y(y%oo){}
};
PP operator +(PP a, PP b){
	return PP((a.x+b.x)%oo, (a.y+b.y)%oo);
}
PP operator -(PP a, PP b){
	return PP((a.x-b.x+oo)%oo, (a.y-b.y+oo)%oo);
}
PP operator *(PP a, PP b){
	return PP((a.x*b.x%oo+a.y*b.y%oo*w%oo)%oo, (a.x*b.y%oo+a.y*b.x%oo)%oo);
}
void write(PP a){
	cout<<a.x<<' '<<a.y<<endl;
}

//快速幂
PP exp(PP a, LL b, LL p){
	PP tmp=PP(1, 0);
	while (b){
		if (b&1) tmp=tmp*a;
		a=a*a;
		b=b>>1;
	}
	return tmp;
}

PP inv(PP a)
{
	PP r=exp(PP((a.x*a.x%oo-a.y*a.y%oo*w%oo+oo)%oo, 0), oo-2, oo);
	return r*PP(a.x, oo-a.y);
}

LL n, k;
PP frac[maxn], invf[maxn];

int main()
{
	frac[0]=PP(1,0);
	invf[0]=PP(1,0);
	for (int i=1;i<=100005;i++)
	{
		frac[i]=frac[i-1]*PP(i,0);
		invf[i]=inv(frac[i]);
	}

	PP inv_2=exp(PP(2, 0), oo-2, oo);
	PP a=PP(1,1)*inv_2;
	PP b=PP(1, oo-1)*inv_2;
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%I64d%I64d",&n,&k);
		PP ans=PP(0, 0);
		for (int j=0;j<=k;j++)
		{
			PP t=exp(a, j, oo)*exp(b, k-j, oo);
			if (t.x==1 && t.y==0)
				ans=ans+(PP(n+1, 0)*frac[k]*invf[j]*invf[k-j]);
			else
			{
				PP a1=exp(t, n+1, oo)-PP(1,0);
				PP a2=inv(t-PP(1,0));
				ans=ans+(a1*a2*frac[k]*invf[j]*invf[k-j]);
			}
		}
		printf("%d\n",ans.x);
	}
	return 0;
}