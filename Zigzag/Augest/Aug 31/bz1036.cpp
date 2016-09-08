#include <bits/stdc++.h>
#define maxn 32000
using namespace std;

int key[maxn], mx[maxn], sum[maxn], rev[maxn];
int fa[maxn], c[maxn][2];
int n,m;

void update(int x)
{
	if (!x) return ;
	mx[x]=max(key[x], max(mx[c[x][0]], mx[c[x][1]]));
	sum[x]=sum[c[x][0]]+sum[c[x][1]]+key[x];
}

void reverse(int x)
{
	if (!x) return ;
	swap(c[x][0], c[x][1]);
	rev[x]^=1;
}

void down(int x)
{
	if (!rev[x]) return ;
	reverse(c[x][0]);
	reverse(c[x][1]);
	rev[x]=0;
}

bool is_root(int x)
{
	return c[fa[x]][0]!=x && c[fa[x]][1]!=x;
}

void relax(int x)
{
	if (!is_root(x)) relax(fa[x]);
	down(x);
}

void zigzag(int x)
{
	int y=fa[x], z=fa[y];
	int p=(c[y][1]==x), q=p^1;
	if (!is_root(y)) c[z][c[z][0]!=y]=x;
	fa[x]=z; fa[y]=x; fa[c[x][q]]=y;
	c[y][p]=c[x][q]; c[x][q]=y;
	update(y);
}

void splay(int x)
{
	relax(x);
	while (!is_root(x))
	{
		int y=fa[x], z=fa[y];
		if (!is_root(y)) 
			((c[y][0]==x) ^ (c[z][0]==y))?zigzag(x):zigzag(y);
		zigzag(x);
	}
	update(x);
}

void access(int x)
{
	for (int y=0;x;y=x, x=fa[x])
	{
		splay(x);
		c[x][1]=y;
		update(x);
	}
}

int root(int x)
{
	while (fa[x]) x=fa[x];
	return x;
}

void make_root(int x)
{
	access(x);
	splay(x);
	reverse(x);
}

void split(int x, int y)//x is root and y in left subtree of x
{
	make_root(y);
	access(x);
	splay(x);
}

void link(int x, int y)
{
	make_root(x);
	fa[x]=y;
}

void cut(int x, int y)
{
	make_root(x);
	access(y);
	splay(y);
	c[y][0]=fa[x]=0;
}

void change(int x, int z)
{
	make_root(x);
	key[x]=z;
	update(x);
}

void init()
{
	memset(sum,0,sizeof(sum));
	memset(mx,-0x3f,sizeof(mx));
}

int main()
{
	scanf("%d",&n);
	int x, y;
	char sign[10];
	init();
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		link(x,y);
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		change(i, x);
	}
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		scanf(" %s %d %d",sign,&x,&y);
		if (sign[0]=='C') change(x, y);
		else
		{
			split(x, y);
			if (sign[1]=='S') printf("%d\n",sum[x]);
			else printf("%d\n",mx[x]);
		}
	}
	return 0;
}