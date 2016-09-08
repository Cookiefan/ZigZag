//Link-Cut-Tree
//支持4种操作
//1.连接x-y将两棵树合并
//2.将x变成根，并切除y与其父亲的连边
//3.将x-y路径上的节点权值+z
//4.询问x-y路径上的最大值
int n,m,tot,q;
int fir[maxn],fa[maxn],c[maxn][2];
int mxv[maxn],key[maxn],rev[maxn],add[maxn];
struct edge
{
	int s,t,val,next;
}e[maxm];
void add_edge(int x,int y)
{
	e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x];fir[x]=tot;
}
void dfs(int x)
{
	for (int j=fir[x];j;j=e[j].next)
	{
		int k=e[j].t;
		if (k!=fa[x])
		{
			fa[k]=x;
			dfs(k);
		}
	}
}

void update(int x)
{
	if (!x) return ;
	mxv[x]=max(max(mxv[c[x][0]],mxv[c[x][1]]),key[x]);
}
void reverse(int x)
{
	if (!x) return ;
	swap(c[x][0],c[x][1]);
	rev[x]^=1;
}
void add_key(int x,int z)
{
	if (!x) return ;
	key[x]+=z;
	mxv[x]+=z;
	add[x]+=z;
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
	{
		if (c[z][0]==y) c[z][0]=x; else c[z][1]=x;
	}
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
		{
			if ((c[y][0]==x)^(c[z][0]==y)) zigzag(x); else zigzag(y);
		}
		zigzag(x);
	}
	update(x);
}

int access(int x)
{
	int y=0;
	for (;x;x=fa[x])
	{
		splay(x);
		c[x][1]=y;
		update(x);
		y=x;
	}
	return y;
}

void make_root(int x)
{
	access(x);
	splay(x);
	reverse(x);
}

int root(int x)
{
	while (fa[x]) x=fa[x];
	return x;
}

void link(int x, int y)
{
	make_root(x);
	fa[x]=y;
}

void cut(int x, int y)
{
	make_root(x);
	splay(y);
	if (c[y][0])
	{
		fa[c[y][0]]=fa[y];	
		c[y][0]=0;
	}
	fa[y]=0;
}

void change(int x, int y, int z)
{
	access(x);
	int lca=access(y);
	splay(x);
	key[lca]+=z;
	add_key(c[lca][1],z);
	if (x!=lca) add_key(x,z);
}

int ask(int x, int y)
{
	access(x); 
	int lca=access(y);
	splay(x);
	if (x==lca) return max(mxv[c[lca][1]],key[lca]);
	else return max(max(mxv[c[lca][1]],key[lca]),mxv[x]);
}

void init()
{
	tot=1;
	memset(fir,0,sizeof(fir));
	memset(key,0,sizeof(key));
	memset(mxv,0,sizeof(mxv));
	memset(rev,0,sizeof(rev));
	memset(add,0,sizeof(add));
	memset(c,0,sizeof(c));
	memset(fa,0,sizeof(fa));
}

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		int x,y,z,s;
		init();
		for (int i=2;i<=n;i++)
		{
			scanf("%d",&x);
			link(i, x);
		}
		dfs(1);
		scanf("%d",&m);
		for (int i=1;i<=m;i++)
		{
			scanf("%d",&s);
			switch(s)
			{
				case 1:
					scanf("%d%d",&x,&y);
					if (root(x)!=root(y)) link(x,y);
					else printf("-1\n");
				break;

				case 2:
					scanf("%d%d",&x,&y);
					if (root(x)==root(y) && x!=y) cut(x,y);
					else printf("-1\n");
				break;

				case 3:
					scanf("%d%d%d",&z,&x,&y);
					if (root(x)==root(y)) change(x,y,z);
					else printf("-1\n");
				break;

				case 4:
					scanf("%d%d",&x,&y);
					if (root(x)==root(y)) printf("%d\n",ask(x,y));
					else printf("-1\n");
				break;
			}
		}
		printf("\n");
	}
	return 0;
}