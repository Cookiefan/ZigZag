#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
struct point
{
	int x[4];
	int flag;
	int sum;
	point(){}
	point(int a, int b, int c, int d, int f)
	{
		x[0]=a; x[1]=b; x[2]=c; x[3]=d; flag=f;
		sum=0;
		int now=flag;
		for (int i=0;i<4;i++)
		{
			if ((now&1)==0)
				sum+=x[i];
			else
				sum-=x[i];
			now=now>>1;
		}
	}
	friend bool operator ==(point a, point b)
	{
		for (int i=0;i<4;i++)
			if (a.x[i]!=b.x[i]) return 0;
		return 1;
	}
	friend bool operator <(point a, point b)
	{
		return a.sum<b.sum;
	}
};
set<point>s[16];
int n;

int main()
{
	scanf("%d",&n);
	int x[4],sign;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d%d",&sign,&x[0],&x[1],&x[2],&x[3]);
		if (sign==1)
			for (int i=0;i<16;i++)
				s[i].insert(point(x[0], x[1], x[2], x[3], i));
		else if (sign==2)
			for (int i=0;i<16;i++)
				s[i].erase(point(x[0], x[1], x[2], x[3], i));
		else
		{
			int ans=0;
			for (int i=0;i<16;i++)
			{
				point* now=new point(x[0], x[1], x[2], x[3], i);
				ans=max(ans, now->sum-s[i].begin()->sum);
			}
			printf("%d\n",ans);
		}
	}

	return 0;
}