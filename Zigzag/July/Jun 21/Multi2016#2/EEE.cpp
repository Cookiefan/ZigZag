#include <bits/stdc++.h>
#define maxn 1200
using namespace std;

typedef long long llg;
typedef llg LL;

const llg oo=1000000007;

long long gcd(long long a, long long b){
	return (!a)?b:gcd(b%a, a);
}
struct point
{
	llg x, y;
	point (){}
	point(llg x, llg y):x(x),y(y){}
	friend point Unit(point a)
	{
		int g=gcd(abs(a.x),abs(a.y));
		if (!a.x && !a.y) return point(0,0);
		else if (!a.x && a.y) return point(0,1);
		else if (a.x && !a.y) return point(1,0);
		else return point(a.x/g, a.y/g);
	};
}O;
//向量减法
point operator -(point a, point b){ return point(a.x-b.x, a.y-b.y);}
//向量叉积
llg operator *(point a, point b){ return a.x*b.y-a.y*b.x;}

bool operator <(point a, point b)
{
	return a.x==b.x?a.y<b.y:a.x<b.x;
}

bool operator ==(point a, point b)
{
	return a.x==b.x && a.y==b.y;
}

bool cmp(point a, point b)
{
	return Unit(a-O)<Unit(b-O);
}

bool online(point a, point b)
{
	return Unit(a)==Unit(b);
}

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

LL rev(LL x, LL oo)
{
	if (x==1) return 1;
	else return (oo-oo/x)*rev(oo%x, oo)%oo;
}

point p[maxn], q[maxn];
int n, x, y;
llg ans;


int main()
{
	//freopen("E.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=0;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			p[i]=point(x,y);
			q[i]=p[i];
		}
		ans=0;
		for (int i=0;i<n;i++)
		{
			if (i>0 && q[i]==q[i-1]) continue;
			O=q[i];
			sort(p, p+n, cmp);
			llg cnt=0, sum=1;
			for (int j=0;j<n;j++) if (p[j]==O) swap(p[cnt++], p[j]);
			//for (int j=0;j<n;j++) cout<<p[j].x<<','<<p[j].y<<' '; cout<<endl;
			//(ans+=(exp(2, cnt, oo)-cnt-1+oo)%oo)%oo;
			if (cnt<n)
			{
				point v=p[cnt]-O;
				sum=1;
				for (int j=cnt+1;j<n;j++)
				{
					if (online(v, p[j]-O)) sum++;
					else
					{
						(ans+=(exp(2, cnt, oo)-1+oo)*(exp(2, sum, oo)-1+oo)%oo)%=oo;
						//cout<<sum<<' ';
						//cout<<": "<<ans<<' ';
						v=p[j]-O;
						sum=1;
					}
				}
				(ans+=(exp(2, cnt, oo)-1+oo)*(exp(2, sum, oo)-1+oo)%oo)%=oo;
				//cout<<sum<<endl;;
				//cout<<": "<<ans<<endl;
			}
		//	cout<<ans<<endl;
			(ans+=(exp(2, cnt, oo)-1-cnt+oo)*2%oo)%=oo;
		}
		printf("%I64d\n",ans*rev(2, oo)%oo);
	}
	return 0;
}