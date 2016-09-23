//树链剖分
vector<int> t[maxn];
int dep[maxn], pos[maxn], top[maxn], size[maxn], fa[maxn];
int sum[6*maxn], mx[6*maxn];
int n,m,num;

void dfs_one(int x)
{
	size[x]=1;
	int ss=t[x].size();
	for (int j=0;j<ss;j++)
	{
		int y=t[x][j];
		if (y==fa[x]) continue;
		dep[y]=dep[x]+1;
		fa[y]=x;
		dfs_one(y);
		size[x]+=size[y];
	}
}
void dfs_two(int x, int anc)
{
	pos[x]=++num;
	top[x]=anc;
	int son=0, ss=t[x].size();
	for (int j=0;j<ss;j++)
	{
		int y=t[x][j];
		if (y!=fa[x] && size[y]>size[son]) son=y;
	}
	if (son) dfs_two(son, anc);
	for (int j=0;j<ss;j++)
	{
		int y=t[x][j];
		if (y!=fa[x] && y!=son) dfs_two(y, y);
	}
}
void update(int x)
{
	sum[x]=sum[x<<1]+sum[x<<1|1];
	mx[x]=max(mx[x<<1], mx[x<<1|1]);
}
void build(int x, int l, int r)
{
	if (l==r)
	{
		sum[x]=0;
		mx[x]=-inf;
		return ;
	}
	int mid=(l+r)>>1;
	build(x<<1, l, mid);
	build(x<<1|1, mid+1, r);
}
void change(int x, int l, int r, int p, int z)
{
	if (l==r)
	{
		sum[x]=mx[x]=z;
		return ;
	}
	int mid=(l+r)>>1;
	if (p<=mid) change(x<<1, l, mid, p, z);
	else change(x<<1|1, mid+1, r, p, z);
	update(x);
}
int ask_sum(int x, int l, int r, int ll, int rr)
{
	if (ll<=l && r<=rr) return sum[x]; 
	int mid=(l+r)>>1, tmp=0;
	if (ll<=mid) tmp+=ask_sum(x<<1, l, mid, ll, rr);
	if (rr>mid) tmp+=ask_sum(x<<1|1, mid+1, r, ll, rr);
	return tmp;
}
int ask_max(int x, int l, int r, int ll, int rr)
{
	if (ll<=l && r<=rr) return mx[x];
	int mid=(l+r)>>1, tmp=-inf;
	if (ll<=mid) tmp=max(tmp, ask_max(x<<1, l, mid, ll, rr));
	if (rr>mid) tmp=max(tmp, ask_max(x<<1|1, mid+1, r, ll, rr));
	return tmp;
}
int get_sum(int x, int y)
{
	int tmp=0;
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x, y);
		tmp+=ask_sum(1, 1, n, pos[top[x]], pos[x]);
		x=fa[top[x]];
	}
	if (pos[x]>pos[y]) swap(x, y);
	tmp+=ask_sum(1, 1, n, pos[x], pos[y]);
	return tmp;
}
int get_max(int x, int y)
{
	int tmp=-inf;
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x, y);
		tmp=max(tmp, ask_max(1, 1, n, pos[top[x]], pos[x]));
		x=fa[top[x]];
	}
	if (pos[x]>pos[y]) swap(x, y);
	tmp=max(tmp, ask_max(1, 1, n, pos[x], pos[y]));
	return tmp;
}
int change_value(int x, int z)
{
	change(1, 1, n, pos[x], z);
}

int main()
{
	scanf("%d",&n);
	int x, y;
	for (int i=1;i<=n;i++) t[i].clear();
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		t[x].push_back(y);
		t[y].push_back(x);
	}
	num=0;
	dfs_one(1);
	dfs_two(1, 1);
	build(1,1,n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		change_value(i, x);
	}
	char sign[10];
	int z;
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		scanf(" %s%d%d",sign,&x,&y);
		if (sign[0]=='C')
			change_value(x, y);
		else if (sign[1]=='M')
			printf("%d\n",get_max(x, y));
		else
			printf("%d\n",get_sum(x, y));
	}
	return 0;
}