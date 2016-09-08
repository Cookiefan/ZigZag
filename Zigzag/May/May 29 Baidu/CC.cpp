#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#define inf 999999999
#define mo 1000000007
#define LL long long 
using namespace std;
const int mz=20000;
const int jia=2000000;
const int maxn=4000000;
const int mn=15000;
struct Node
{
	int x,y,v;
	Node(){}
	Node(int _x,int _y,int _v):x(_x),y(_y),v(_v){}
};
Node a[mn],b[mn];
int c[maxn],na,nb,ans;
int n;
bool cmp(Node x,Node y)
{
	if (x.x==y.x) return x.y>y.y;
	else return x.x<y.x;
}

int lowbit(int i) {return (i&(-i));}

int H(int en)
{
    int sum = 0;
    while (en > 0)
    {
        sum +=c[en];
        en -=lowbit(en);
    }
    return sum;
}

int Query(int x,int y)
{
    int sum1=H(x);
    int sum2=H(y);
    return (sum2-sum1);
}

void Add(int x,int y)
{
    while (x <= maxn)
    {
        c[x]+=y;
        x+=lowbit(x);
    }
}

void Clear()
{
	memset(c,0,sizeof(c));
}

void Run()
{
	Clear();
	for (int i=1;i<=na;i++)
		Add(a[i].y,1);
	for (int i=1;i<=na;i++)
	{
		a[i].v=Query(a[i].x,a[i].x+2*mz);
		ans=max(ans,a[i].v);
		Add(a[i].y,-1);
	}

	Clear();
	for (int i=1;i<=nb;i++)
		Add(b[i].y,1);
	for (int i=1;i<=nb;i++)
	{
		ans=max(ans,b[i].v);
		b[i].v=Query(b[i].x,b[i].x+2*mz);
		Add(b[i].y,-1);
	}
	return ;
}
int main()
{
	int x,y,z,d,now,mb,t;
	scanf("%d",&t);
	for (int o=1;o<=t;o++)
	{

		scanf("%d",&n);
		na=0;nb=0;
		ans=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d",&x,&y,&z,&d);
			if (d==1)
			{
				na++;
				a[na]=Node(x-(mz-z)+jia,y+(mz-z)+jia,0);
			}
			else
			{
				nb++;
				b[nb]=Node(x-(mz-z)+jia,y+(mz-z)+jia,0);
			}
		}
		sort(a+1,a+1+na,cmp);
		sort(b+1,b+1+nb,cmp);
		Run();
		now=nb;mb=0;
		for (int i=na;i>=1;i--)
		{
			if (a[i].x<=b[now].x)
			{
				while (now>0 && a[i].x<=b[now].x)
				{
					mb=max(b[now].v,mb);
					now--;
				}
				// cout<<a[i].x<<' '<<b[now].x<<' '<<mb<<endl;
			}
			ans=max(ans,a[i].v+mb);
		}
		printf("Case #%d:\n",o);
		printf("%d\n",ans);	
	}
}
/*
5
1 2 5 1
1 3 5 1
20 21 5 1
1 2 5 -1
1 3 5 -1
*/
