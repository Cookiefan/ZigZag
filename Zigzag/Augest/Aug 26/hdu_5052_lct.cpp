#include <bits/stdc++.h>
#define maxn 50200
using namespace std;

vector<int> t[maxn];
int fa[maxn],c[maxn][2];
int mx[maxn],mi[maxn],key[maxn],add[maxn],rev[maxn],up[maxn],dw[maxn];
int n,m;

void update(int x)
{
	if (!x) return ;
	mx[x]=max(key[x], max(mx[c[x][0]], mx[c[x][1]]));
	mi[x]=min(key[x], min(mi[c[x][0]], mi[c[x][1]]));
	up[x]=max(up[c[x][0]], up[c[x][1]]);
	up[x]=max(up[x], mx[c[x][0]]-mi[c[x][1]]);
	up[x]=max(up[x], max(mx[c[x][0]]-key[x], key[x]-mi[c[x][1]]));
	dw[x]=max(dw[c[x][1]], dw[c[x][0]]);
	dw[x]=max(dw[x], mx[c[x][1]]-mi[c[x][0]]);
	dw[x]=max(dw[x], max(mx[c[x][1]]-key[x], key[x]-mi[c[x][0]]));
}

void add_key(int x,int z)
{
	if (!x) return ;
	key[x]+=z;
	add[x]+=z;
	mx[x]+=z;
	mi[x]+=z;
}

void reverse(int x)
{
	if (!x) return ;
	swap(c[x][0], c[x][1]);
	swap(up[x], dw[x]);
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
	if (add[x])
	{
		add_key(c[x][0],add[x]);
		add_key(c[x][1],add[x]);
		add[x]=0;
	}
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
	int y=fa[x],z=fa[y];
	int p=(c[y][1]==x), q=p^1;
	if (!is_root(y))
		if (c[z][0]==y) c[z][0]=x;
		else c[z][1]=x;
	fa[x]=z; fa[y]=x; fa[c[x][q]]=y;
	c[y][p]=c[x][q]; c[x][q]=y;
	update(y);
}

void splay(int x)
{
	relax(x);
	while (!is_root(x))
	{
		int y=fa[x],z=fa[y];
		if (!is_root(y))
			if ((c[y][0]==x)^(c[z][0]==y)) zigzag(x);
			else zigzag(y);
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

void split(int x, int y)
{
	make_root(y);
	access(x);
	splay(x);
}

void dfs(int x)
{
	for (int y:t[x])
	{
		if (y==fa[x]) continue;
		fa[y]=x;
		dfs(y);
	}
}

void init()
{	
	for (int i=1;i<=n;i++) t[i].clear();
	memset(fa,0,sizeof(fa));
	memset(c,0,sizeof(c));
	memset(mx,-0x3f,sizeof(mx));
	memset(mi,0x3f,sizeof(mi));
	memset(add,0,sizeof(add));
	memset(rev,0,sizeof(rev));
	memset(up,0,sizeof(up));
	memset(dw,0,sizeof(dw));
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		int x, y, z;
		scanf("%d",&n);
		init();
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			mi[i]=mx[i]=key[i]=x;
		}
		for (int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			t[x].push_back(y);
			t[y].push_back(x);
		}
		dfs(1);
		//cout<<mx[0]<<' '<<mi[0]<<endl;
		scanf("%d",&m);
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			split(x, y);
			//for (int i=1;i<=n;i++) cout<<i<<' '<<fa[i]<<' '<<c[i][0]<<' '<<c[i][1]<<' '<<mi[i]<<' '<<mx[i]<<' '<<up[i]<<' '<<dw[i]<<endl;
			printf("%d\n",up[x]);
			add_key(x, z);
		}
	}
	return 0;
}