#include <bits/stdc++.h>
#define maxn 120
using namespace std;
typedef long long LL;

LL gcd(LL a, LL b)
{
    if (!b)
        return a;
    else
        return gcd(b, a % b);
}
LL lcm(LL a, LL b)
{
	return a/gcd(a,b)*b;
}

struct fff
{
	LL up, dw;
	fff(){}
	fff(int x, int y):up(x),dw(y){}
	void update()
	{
		LL g=gcd(up, dw);
		up/=g;
		dw/=g;
	}
}f[maxn], g[maxn];


fff operator +(fff a, fff b)
{
	fff c;
	LL l=lcm(a.dw, b.dw);
	c.up=a.up*l/a.dw+b.up*l/b.dw;
	c.dw=l;
	c.update();
	return c;
}

fff operator *(fff a, fff b)
{
	fff c;
	c.up=a.up*b.up;
	c.dw=a.dw*b.dw;
	c.update();
	return c;
}
int  v[maxn], d[maxn];
LL frac[maxn];
int n,m,p;
LL hit;

void dfs(int k)
{
	if (k>m) return ;
	if (k>0)
	{
		g[k].dw++;
		if (hit>=p) g[k].up++;
	}
	for (int i=1;i<=m;i++)
		if (!v[i])
		{
			hit+=d[i];
			v[i]=1;
			dfs(k+1);
			v[i]=0;
			hit-=d[i];
		}
}

int main()
{
	fff a=fff(7, 2), b=fff(3, 7);
	//cout<<(a+b).up<<'/'<<(a+b).dw<<endl;
	//cout<<(a*b).up<<'/'<<(a*b).dw<<endl;
	frac[0]=1;
	for (int i=1;i<=21;i++) frac[i]=frac[i-1]*i;
	while (scanf("%d%d%d",&p,&n,&m)!=EOF)
	{
		for (int i=1;i<=m;i++) scanf("%d",&d[i]);
		for (int i=1;i<=m;i++)
		{
			g[i].up=g[i].dw=0;
		}
		hit=0;
		dfs(0);

		fff sum=fff(0,1);
		for (int i=1;i<=m;i++) f[i]=fff(0,1);
		for (int i=1;i<=min(m,n+1);i++)
		{
			f[i].up=frac[n]/frac[n-i+1]*frac[m]/frac[m-i];
			//cout<<frac[n+1]<<' '<<frac[n+m-2*i+1]<<endl;
			f[i].dw=frac[n+m]/frac[n+m-2*i+1];
			f[i].update();
			printf("%I64d/%I64d\n",f[i].up, f[i].dw);
			sum=sum+f[i];
		}
		sum.up=sum.dw-sum.up;
		f[min(n,n+1)]=sum;
		//printf("%I64d/%I64d\n",sum.up, sum.dw);
		fff ans=fff(0,1);
		for (int i=1;i<=m;i++) ans=ans+(f[i]*g[i]);
		printf("%I64d/%I64d\n",ans.up, ans.dw);

	}
	return 0;
}