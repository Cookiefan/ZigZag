#include <bits/stdc++.h>
#define maxn 100020
using namespace std;

struct bit
{
	int b[4*maxn];
	int num;
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) b[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i;i-=(i&-i)) tmp+=b[i];
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(b,0,sizeof(b));
	}
}s;

struct query
{
	int tp, x, l, r;
	query(){}
	query(int tp, int x, int l, int r):tp(tp),x(x),l(l),r(r){}
}q[maxn*2];

bool operator <(query a, query b)
{
	return a.x==b.x?a.tp<b.tp:a.x<b.x;
}

int a[4*maxn];
int n, tot, num;
long long ans;


int get_num(int x)
{
	return (lower_bound(a, a+num, x)-a)+1;
}


int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int xo, yo, xe, ye;
		tot=num=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d",&xo, &yo, &xe, &ye);
			a[num++]=yo;
			a[num++]=ye;
			if (xo==xe)
			{
				if (yo>ye) swap(yo, ye);
				q[tot++]=query(3, xo, yo, ye);
			}
			else
			{
				if (xo>xe) swap(xo, xe);
				q[tot++]=query(1, xo, yo, yo);
				q[tot++]=query(2, xe+1, ye, ye);
			}
		}
		sort(a, a+num);
		sort(q, q+tot);
		for (int i=0;i<tot;i++)
		{
			q[i].l=get_num(q[i].l);
			q[i].r=get_num(q[i].r);
		}
		//cout<<endl;
		//for (int i=0;i<tot;i++) cout<<q[i].tp<<' '<<q[i].x<<' '<<q[i].l<<' '<<q[i].r<<endl;
		s.init(num+100);
		ans=0;
		for (int i=0;i<tot;i++)
		{
			if (q[i].tp==1)
				s.add(q[i].l, 1);
			else if (q[i].tp==2)
				s.add(q[i].l, -1);
			else
			{
				//cout<<s.ask(q[i].r)-s.ask(q[i].l-1)<<endl;
				ans+=s.ask(q[i].r)-s.ask(q[i].l-1);
			}
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
