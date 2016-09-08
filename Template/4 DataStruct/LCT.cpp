//LCT
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