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
	map<point,int> mp;
	point (){}
	point(llg x, llg y):x(x),y(y)
	{
		mp.clear();
	}
	friend point Unit(point a)
	{
		int g=gcd(abs(a.x),abs(a.y));
		if (!a.x && !a.y) return point(0,0);
		else if (!a.x && a.y) return point(0,1);
		else if (a.x && !a.y) return point(1,0);
		else return point(a.x/g, a.y/g);
	};
	void cut(point v){
		mp[Unit(v)]=1;
	}
	bool check(point v){
		return  (mp.find(Unit(v))!=mp.end());
	}
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
point p[maxn];
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
		}
		ans=0;
		for (int i=0;i<n;i++)
		{
			sort(p, p+n);
			if (i>0 && p[i]==p[i-1]) continue;
			O=p[i];
			sort(p+i, p+n, cmp);
			//for (int j=i;j<n;j++) cout<<p[j].x<<','<<p[j].y<<' '; cout<<endl;
			llg cnt=0;
			for (int j=i;j<n;j++)
				if (p[j]==p[i]) cnt++;
			//(ans+=(exp(2, cnt, oo)-cnt-1+oo)%oo)%oo;
			if (i+cnt<n)
			{
				point fst=p[i+cnt];
				llg sum=1;
				for (int j=i+cnt+1;j<n;j++)
				{
					if (online(fst-O, p[j]-O)) sum++;
					else
					{
						if (fst.check(fst-O)==0)
						{
							(ans+=(exp(2, sum+cnt, oo)-sum-cnt-1+oo)%oo)%oo;
							//cout<<i<<' '<<j<<' '<<sum<<endl;
							for (int k=j-1;k>=j-sum;k--)
								p[k].cut(fst-O);
						}
						sum=1;
						fst=p[j];
					}
				}
				//cout<<fst.check(fst-O)<<endl;
				if (fst.check(fst-O)==0)
				{
					//cout<<sum+cnt<<endl;
					(ans+=(exp(2, sum+cnt, oo)-sum-cnt-1+oo)%oo)%oo;
					for (int k=n-1;k>=n-sum;k--)
						p[k].cut(fst-O);
				}
			}
		}
		sort(p, p+n);
		int sum=1;
		for (int i=1;i<n;i++)
		{
			if (p[i]==p[i-1]) 
			{
				sum++;
				continue;
			}
			else
			{
				int cnt=p[i].mp.size();
				cout<<cnt<<endl;
				ans=(ans-((exp(2, sum, oo)-sum-1+oo)%oo*(cnt-1))%oo+oo)%oo;
				sum=1;
			}
		}			
		printf("%I64d\n",ans);
	}
	return 0;
}