#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define maxn 10020
#define inf 999999999
#define PI acos(-1.0)
using namespace std;

int np[maxn];
vector<int> prime;
void get_prime(int n)
{
	memset(np,0,sizeof(np));
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
		//cpx wn(cosl(PI/i), flag*sinl(PI/i));
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

cpx A[maxn];

struct edge
{
	int t, val;
	edge(){}
	edge(int t, int val):t(t),val(val){}
};
vector<edge> e[maxn];
vector<int> q;

int size[maxn], mx_size[maxn], dep[maxn], vis[maxn];
int a[maxn*2], b[maxn*2];
int n, rot, ans, cnt, m, num;

void chose(int x, int fa, int num)
{
	size[x]=1; mx_size[x]=0;
	for (int j=0;j<e[x].size();j++)
	{
		int y=e[x][j].t;
		if (!vis[y] && y!=fa)
		{
			chose(y, x, num);
			size[x]+=size[y];
			mx_size[x]=max(mx_size[x], size[y]);
		}
	}
	mx_size[x]=max(mx_size[x], num-size[x]);
	if (mx_size[x]<mx_size[rot]) rot=x;
}

int chose_rot(int x, int num)
{
	rot=0;
	chose(x, 0, num);
	return rot;
}

void get_dep(int x, int fa)
{
	a[dep[x]]++;
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

int get_ans(int x, int h)
{
	memset(a, 0, sizeof(*a)<<m);
	dep[x]=h;
	get_dep(x, 0);
	cout<<"x: "<<x<<endl;
	for (int i=0;i<num;i++) A[i]=cpx(a[i], 0);
	fft(A, num, 1);
	for (int i=0;i<num;i++) A[i]=A[i]*A[i];
	fft(A, num, -1);
	for (int i=0;i<num;i++)
		if (i+i<num) b[i+i]=a[i];
	for (int i=0;i<num;i++) cout<<(LL)(A[i].x+0.5)<<' '; cout<<endl;
	for (int i=0;i<num;i++) cout<<b[i]<<' '; cout<<endl;
	LL tmp=0;
	for (int i=0;i<num;i++)
		if (!np[i])
			tmp+=(LL)(A[i].x+0.5)-b[i];
	cout<<tmp<<endl;
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
		{
			ans-=get_ans(y, dep[y]);
			solve(chose_rot(y, size[y]));
		}
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
	scanf("%d",&n);
	get_prime(n);
	num=1; m=0;
	while (num<n) num<<=1,m++;
	int x,y,z;
	init();
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		e[x].push_back(edge(y,1));
		e[y].push_back(edge(x,1));
	}		
	solve(chose_rot(1, n));
	printf("%d\n",ans);
	return 0;

}

