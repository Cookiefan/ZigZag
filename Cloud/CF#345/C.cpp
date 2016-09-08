#include <bits/stdc++.h>
#define maxn 220000
using namespace std;

struct point
{
	int x,y;
}p[maxn];
int n;

bool cmp1(point a, point b)
{
	return a.x<b.x;
}
bool cmp2(point a, point b)
{
	return a.y==b.y?a.x<b.x:a.y<b.y;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y);
	long long ans=0;

	long long now=1;
	sort(p+1,p+n+1,cmp1);

	for (int i=2;i<=n;i++)
		if (p[i].x==p[i-1].x)
			now++;
		else
		{
			ans+=now*(now-1)/2;
			now=1;
		}
	ans+=now*(now-1)/2;

	now=1;
	sort(p+1,p+n+1,cmp2);
	for (int i=2;i<=n;i++)
		if (p[i].y==p[i-1].y)
			now++;
		else
		{
			ans+=now*(now-1)/2;
			now=1;
		}	
	ans+=now*(now-1)/2;


	now=1;
	for (int i=2;i<=n;i++)
		if (p[i].x==p[i-1].x && p[i].y==p[i-1].y)
			now++;
		else
		{
			ans-=now*(now-1)/2;
			now=1;
		}
	ans-=now*(now-1)/2;

	printf("%I64d\n",ans);
	
	return 0;
}