#include <bits/stdc++.h>
#define maxn 100200
#define oo 51061
using namespace std;

unsigned int key[maxn], sum[maxn], add[maxn], mul[maxn];
int siz[maxn], rev[maxn];
int fa[maxn], c[maxn][2];
int n,m;

void update(int x)
{
	if (!x) return ;
	sum[x]=(sum[c[x][0]]+sum[c[x][1]]+key[x])%oo;
	siz[x]=(siz[c[x][0]]+siz[c[x][1]]+1)%oo;
}

void change(int x, int mu, int ad)
{
	if (!x) return ;
	key[x]=(key[x]*mu%oo+ad)%oo;
	mul[x]=mul[x]*mu%oo;
	add[x]=(add[x]*mu%oo+ad)%oo;
	sum[x]=(sum[x]*mu%oo+ad*siz[x]%oo)%oo;
}

void reverse(int x)
{
	if (!x) return ;
	swap(c[x][0], c[x][1]);
	rev[x]^=1;
}

void down(int x)
{
	if (rev[x])
	{
		reverse(c[x][0]);
		reverse(c[x][1]);
		rev[x]=0;
	}
	change(c[x][0], mul[x], add[x]);
	change(c[x][1], mul[x], add[x]);
	mul[x]=1;
	add[x]=0;
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
	for (int y=0; x; y=x, x=fa[x])
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

void split(int x, int y)
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
	split(y, x);
	c[y][0]=fa[x]=0;
}

int main()
{
	scanf("%d%d",&n,&m);
	int x, y, u, v, z;
	char sign;
	for (int i=1;i<=n;i++)
	{
		siz[i]=key[i]=mul[i]=1;
		sum[i]=add[i]=rev[i]=0;
		fa[i]=c[i][0]=c[i][1]=0;
	}
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		link(x, y);
	}
	for (int i=1;i<=m;i++)
	{
		scanf(" %c",&sign);
		switch (sign)
		{
			case '+':
				scanf("%d%d%d",&x,&y,&z);
				split(x, y);
				change(x, 1, z);
			break;
			case '-':
				scanf("%d%d%d%d",&u,&v,&x,&y);
				cut(u,v);
				link(x,y);
			break;
			case '*':
				scanf("%d%d%d",&x,&y,&z);
				split(x, y);
				change(x, z, 0);
			break;
			case '/':
				scanf("%d%d",&x,&y);
				split(x, y);
				printf("%d\n",sum[x]);
			break;
		}	
	}
	return 0;
}