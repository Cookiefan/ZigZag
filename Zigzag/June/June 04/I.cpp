#include <bits/stdc++.h>
#define maxn 12000
using namespace std;

struct peo
{
	int s, num, id;
	peo(){s=num=id=0;}
	peo(int x, int n, int i):s(x), num(n), id(i){}
	friend bool operator < (peo a, peo b)
	{
		if (a.s!=b.s) return a.s>b.s;
		if (a.num!=b.num) return a.num>b.num;
		return a.id<b.id;
	};
}p[maxn];
int n,k;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) p[i]=peo(0,0,i);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		int x, y;
		for (int j=1;j<=k;j++)
		{
			scanf("%d%d",&x,&y);
			p[x].num++;
			p[x].s+=y;
			p[i].s-=y;
		}
	}
	sort(p+1, p+n+1);
	for (int i=1;i<=n;i++)
		printf("%d %.2f\n",p[i].id,(double)p[i].s/100);

	return 0;
}