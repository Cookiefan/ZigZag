#include <bits/stdc++.h>
#define maxn 1200
using namespace std;

typedef long long llg;
typedef llg LL;
const llg oo=1000000007;
struct point
{
	llg x, y;
	int p;
	point (){
		if (y==0) p=(x>0); else p=(y>0);
	}
	point(llg x, llg y):x(x),y(y){
		if (y==0) p=(x>0); else p=(y>0);
	}
	llg len(){ return x*x+y*y;}
}O;

//向量加法
point operator +(point a, point b){ return point(a.x+b.x, a.y+b.y);}
//向量减法
point operator -(point a, point b){ return point(a.x-b.x, a.y-b.y);}
//向量点积
llg operator ^(point a, point b){ return a.x*b.x+a.y*b.y;}
//向量叉积
llg operator *(point a, point b){ return a.x*b.y-a.y*b.x;}

bool online(point a, point b)
{
	return (a*b)==0 && (a^b)>=0;
}

bool operator <(point a, point b)
{
	//return dcmp(Ang(a-O)-Ang(b-O))<0;
	return ((a-O).p==(b-O).p)?(((a-O)*(b-O))>0):((a-O).p<(b-O).p);
}

bool operator ==(point a, point b)
{
	return a.x==b.x && a.y==b.y;
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
point p[maxn],q[maxn];
int n;
llg ans;

int main()
{
	//freopen("E.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		int x,y;
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&x,&y);
			p[i-1]=point(x,y);
			q[i-1]=point(x,y);
		}
		ans=0;
		O=point(0,0);
		sort(q, q+n);

		for (int i=0;i<n;i++)
		{
			if (i>0 && q[i]==q[i-1]) continue;
			O=q[i];
			sort(p, p+n);			
			llg sum=0, cnt=0;
			for (int j=0;j<n;j++) if (p[j]==O) swap(p[cnt++], p[j]);
			//for (int j=0;j<n;j++) cout<<p[j].x<<','<<p[j].y<<' '; cout<<endl;
			//cout<<cnt<<' ';
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