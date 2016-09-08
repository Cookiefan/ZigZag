#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#define inf 999999999
#define mo 1000000007
#define LL long long 
const double EPS = 1e-8;
const int maxn = 50010;
using namespace std;
vector <int> ma[maxn];
int dep[maxn];                    //记录每个点在树中的深度
int siz[maxn];					  //记录以这个点为根的子树中结点的个数
int fa[maxn];                     //记录每个点的父亲 结点是什么
int son[maxn];                    //记录每个点的重儿子
int top[maxn];                    //记录每条链的顶点
int w[maxn];                      //记录每个点在线段树中的位置
int v[maxn];                      //记录每个点的权值
int tot,n,ans;
char s;
int sum[maxn*4];                    //线段树
int sign[maxn*4];
int kind[maxn];
int nk;
struct query
{
	int x,y,v;
	query(){}
	query(int _x,int _y,int _v):x(_x),y(_y),v(_v){}
};
vector<query> p[maxn], q[maxn];
//   线段树
void pushup(int rt)
{
	if (sum[rt*2]==sum[rt*2+1] && kind[rt*2]==kind[rt*2+1])
	{
		sum[rt]=sum[rt*2];
		kind[rt]=kind[rt*2]+1;
	} 
	else
	{
		kind[rt]=0;
		sum[rt]=-1;
	}
}

void Add(int b,int e,int v,int l,int r,int rt)
{
    if(l>=b && r<=e) 
    {	
    	if (v>sum[rt])
    	{
    		sign[rt]=v;
        	sum[rt]=v;
        	kind[rt]=nk;
        	rt/=2;
        	while (rt!=0) {pushup(rt);rt/=2;}
        	return;
    		
    	}

   	}
    int m=(l+r)/2;
    if (sign[rt]>=0)
    {
	    if (sign[rt]>sum[rt*2])
	    {
	    	sign[rt*2]=sign[rt];
	    	sum[rt*2]=sign[rt];
	    	kind[rt*2]=kind[rt];
	    }
	    if (sign[rt]>sum[rt*2+1])
	    {
	    	sign[rt*2+1]=sign[rt];
	    	sum[rt*2+1]+=sign[rt];
	    	kind[rt*2+1]=kind[rt];
	    }
	    sign[rt]=-1;
	    kind[rt]=0;
    }
    if (m>=b) Add(b,e,v,l,m,rt*2);
    if (m<e) Add(b,e,v,m+1,r,rt*2+1);

    pushup(rt);
}

void Query(int b,int e,int l,int r,int rt)
{
	// cout<<b<<' '<<e<<' '<<endl;
	if(l>=b && r<=e && sum[rt]>=0)
	{
		ans=kind[rt];
		// cout<<b<<' '<<e<<' '<<l<<' '<<r<<' '<<sum[rt].s<<' '<<sum[rt].m<<endl;
		return;
	}
	int m=(l+r)/2;
	if (sign[rt]>=0)
    {
	    if (sign[rt]>sum[rt*2])
	    {
	    	sign[rt*2]=sign[rt];
	    	sum[rt*2]=sign[rt];
	    	kind[rt*2]=kind[rt];
	    }
	    if (sign[rt]>sum[rt*2+1])
	    {
	    	sign[rt*2+1]=sign[rt];
	    	sum[rt*2+1]+=sign[rt];
	    	kind[rt*2+1]=kind[rt];
	    }
	    sign[rt]=-1;
	    kind[rt]=0;
    }
	if (m>=b) Query(b,e,l,m,rt*2);
    if (m<e) Query(b,e,m+1,r,rt*2+1);
	return;
}
// ============================================================================

//dfs1处理出每个点的dep siz son fa
void dfs1(int x,int d)
{
	dep[x]=d;
	int num=-1,y;
	siz[x]=1;
	for(int i=0;i<ma[x].size();i++)
	{
		y=ma[x][i];
		if (y==fa[x]) continue;
		fa[y]=x;
		dfs1(y,d+1);
		siz[x]+=siz[y];
		if(siz[y]>num) 
		{
			num=siz[y];
			son[x]=y;
		}
	}
}

//将点放入线段树中  w记录点在线段树中的位置
void dfs2(int x,int r)
{
	// cout<<x<<' '<<r<<endl;
	int y;
	tot++;
	Add(tot,tot,v[x],1,n,1);
	w[x]=tot;
	top[x]=r;
	if (siz[x]==1) return;
	dfs2(son[x],r);
	for (int i=0;i<ma[x].size();i++)
	{
		y=ma[x][i];
		if (y==son[x] || y==fa[x]) continue;
		dfs2(y,y);
	}	
}

// =============================================

//进行需要的操作
/*
记f1 = top[u]，f2 = top[v]。
当f1 <> f2时：不妨设dep[f1] >= dep[f2]，那么就更新u到f1的父边的权值(logn)，并使u = fa[f1]。
当f1 = f2时：u与v在同一条重链上，若u与v不是同一点，就更新u到v路径上的边的权值(logn)，否则修改完成；
*/
void Slove(int x,int y,int v)
{
	int f1,f2;
	f1=top[x];f2=top[y];
	while (f1!=f2)
	{
		if (dep[f1]>=dep[f2])
		{
			p.push_back(w[f1], w[x], v);
			//Add(w[f1],w[x],v,1,n,1);
			x=fa[f1];
		}
		else
		{
			p.push_back(w[f2], w[y], v);
			//Add(w[f2],w[y],v,1,n,1);
			y=fa[f2];
		}
		// cout<<ans_s<<endl;
		f1=top[x];f2=top[y];
	}
	p.push_back(min(w[x], w[y]), max(w[x], w[y]), v);
	//Add(min(w[x],w[y]),max(w[x],w[y]),v,1,n,1);
	return;
}

void clear()
{
	memset(sum,0,sizeof(sum));
	memset(sign,-1,sizeof(sign));
	memset(v,0,sizeof(v));
	memset(dep,0,sizeof(dep));
	memset(siz,0,sizeof(siz));
	memset(fa,0,sizeof(fa));
	memset(son,0,sizeof(son));
	memset(top,0,sizeof(top));
	memset(w,0,sizeof(w));
	memset(kind,0,sizeof(kind));
	for (int i=1;i<=n;i++) ma[i].clear();

}

struct bit
{
	int b[maxn];
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
}s,t;

void sadd(int x,int y,int z)
{
	s.add(x,z); s.add(y+1,-z);
	t.add(x,z*x); t.add(y+1,-z*(y+1));
}

int sask(int x,int y)
{
	int tmp=s.ask(y)*(y+1)-s.ask(x-1)*x-(t.ask(y)-t.ask(x-1));
	return tmp;
}

void modify(VQ &p, VQ &q);
{
	int n=p.size();
	for (int i=0;i<n;i++) sadd(p[i].x, p[i].y, 1);

	for (int i=0;i<n;i++) st[2*i]=p[i].x, st[2*i+1]=p[i].y;
	int m=unique(st, st+2*n)-st;
	for (int i=0;i<m-1;i++) q.push_back(query(st[i], st[i+1], sask(st[i], st[i+1])));

	for (int i=0;i<n;i++) sadd(p[i].x, p[i].y, -1);
}

int main()
{
	int x,y,qu,m,z,v;
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		clear();
		for (int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			ma[x].push_back(y);
			ma[y].push_back(x);
		}	


		dfs1(1,1);
		tot=0;
		dfs2(1,1);
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			
			mx=max(mx, z);
		}
		s.init(n+1);
		t.init(n+1);
		for (int i=1;i<=mx;i++) modify(p[i], q[i]);
		solve(x, y, z);
		
	}
	
}
