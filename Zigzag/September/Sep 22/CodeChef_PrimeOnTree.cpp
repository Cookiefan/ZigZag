#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define maxn 50020
#define inf 999999999
#define PI acos(-1.0)
using namespace std;

int np[maxn*2];
vector<int> prime;
void get_prime(int n)
{
	memset(np,0,sizeof(np));
	np[0]=np[1]=1;
	prime.clear();
	for (int i=2;i<=n;i++)
	{
		if (!np[i]) prime.push_back(i);
		for (int j=0;j<prime.size()&&prime[j]*i<=n;j++)
		{
			np[prime[j]*i]=1;
			if (i%prime[j]==0) break;
		}
	}
}
typedef double LD;//long double
typedef long long LL;
//typedef complex<LD> cpx;
struct cpx
{
	LD x, y;
	cpx(){}
	cpx(LD x, LD y):x(x),y(y){}
};
cpx operator +(cpx a, cpx b)
{
	return cpx(a.x+b.x, a.y+b.y);
}
cpx operator -(cpx a, cpx b)
{
	return cpx(a.x-b.x, a.y-b.y);
}
cpx operator *(cpx a, cpx b)
{
	return cpx(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
}

int rev(int x, int n)
{
    int tmp=0;
    for (int i=n>>1;i;i>>=1,x>>=1)
        tmp=tmp<<1|x&1;
    return tmp;
}

void fft(cpx *a, int n, int flag)
{
	for (int i=0,j=i;i<n;i++,j=rev(i, n))
		if (i<j) swap(a[i], a[j]);
	for (int k=1;k<n;k<<=1)
	{
		cpx wn(cos(PI/k), flag*sin(PI/k));
		cpx w(1, 0);
		for (int i=0;i<k;i++,w=w*wn)
			for (int j=i;j<n;j+=(k<<1))
			{
				cpx x=a[j], y=w*a[j|k];
				a[j]=x+y;
				a[j|k]=x-y;
			}
	}
	if (flag==-1) 
		for (int i=0;i<n;i++)
			a[i].x/=n, a[i].y/=n;
}

cpx A[maxn*2];

struct edge
{
	int t, val;
	edge(){}
	edge(int t, int val):t(t),val(val){}
};
vector<edge> e[maxn];

int size[maxn], mx_size[maxn], dep[maxn], vis[maxn];
LL a[maxn*2], b[maxn*2];
int n, rot,  cnt, m, num;
LL ans;

void chose(int x, int fa, int sz)
{
	size[x]=1; mx_size[x]=0;
	for (int j=0;j<e[x].size();j++)
	{
		int y=e[x][j].t;
		if (!vis[y] && y!=fa)
		{
			chose(y, x, sz);
			size[x]+=size[y];
			mx_size[x]=max(mx_size[x], size[y]);
		}
	}
	mx_size[x]=max(mx_size[x], sz-size[x]);
	if (mx_size[x]<mx_size[rot]) rot=x;
}

int chose_rot(int x, int sz)
{
	rot=0;
	chose(x, 0, sz);
	return rot;
}

vector<int> q;

void get_dep(int x, int fa)
{
	q.push_back(dep[x]);
	for (int j=0;j<e[x].size();j++)
	{
		int y=e[x][j].t;
		if (!vis[y] && y!=fa)
		{
			dep[y]=dep[x]+e[x][j].val;
			get_dep(y, x);
		}
	}
}

LL get_ans(int x, int h)
{
	dep[x]=h;
	q.clear();
	get_dep(x, 0);
	int mx=0;
	for (int i=0;i<q.size();i++) mx=max(mx, q[i]);
	num=1;
	while (num<(mx<<1)+2) num<<=1;
	for (int i=0;i<num;i++) a[i]=0;
	for (int i=0;i<q.size();i++) a[q[i]]++;
	//cout<<(h==0?"+":"-")<<"x: "<<x<<endl;
	for (int i=0;i<num;i++) A[i]=cpx(a[i], 0);
	fft(A, num, 1);
	for (int i=0;i<num;i++) A[i]=A[i]*A[i];
	fft(A, num, -1);
	for (int i=0;i<num;i++)
		if ((i<<1)<num) b[i<<1]=a[i];
	//for (int i=0;i<num;i++) cout<<(LL)(A[i].x+0.5)-b[i]<<' '; cout<<endl;
	LL tmp=0;
	for (int i=0;i<num;i++)
		if (!np[i])
			tmp+=(LL)(A[i].x+0.5)-b[i];
	//cout<<tmp<<endl;
	return tmp;
}

void solve(int x)
{
	vis[x]=1;
	ans+=get_ans(x, 0);
	for (int j=0;j<e[x].size();j++)
	{
		int y=e[x][j].t;
		if (!vis[y])
			ans-=get_ans(y, dep[y]);
	}
	for (int j=0;j<e[x].size();j++)
	{
		int y=e[x][j].t;
		if (!vis[y])
			solve(chose_rot(y, size[y]));
	}
}

void init()
{
	for (int i=1;i<=n;i++) e[i].clear();
	memset(vis,0,sizeof(vis));
	ans=0;
	mx_size[0]=inf;
}

int main()
{
	//freopen("A.in","r",stdin);
	scanf("%d",&n);
	num=1; m=0;
	while (num<n+1) num<<=1;
	get_prime(num);
	int x,y,z;
	init();
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		e[x].push_back(edge(y,1));
		e[y].push_back(edge(x,1));
	}		
	solve(chose_rot(1, n));
	LL sum=(LL)n*(n-1);
	printf("%.7f\n",ans*1.0/sum);
	return 0;

}

