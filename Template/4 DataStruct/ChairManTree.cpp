//主席树
struct node
{
	node *lc,*rc;
	int s;
	node () {s=0;}
}*rot[maxn],*sum[maxn],*p;
vector <node*> st[4];
struct et
{
	int s,t,next;
}e[maxn*2];
int ll[maxn],rr[maxn],fir[maxn],key[maxn];
int w[maxn*2],dep[maxn],fa[maxn][20];
int x[maxn],y[maxn],z[maxn];
int n,m,tot,low,cnt,num;
int v[5];

node *build(int l,int r)
{
	node *now=new node();
	if (l==r) return now;
	int mid=(l+r)>>1;
	now->lc=build(l,mid);
	now->rc=build(mid+1,r);
	return now;
}

node *change(int l,int r,int x,int z)
{
	node *now=new node();
	now->lc=p->lc; now->rc=p->rc;
	now->s=p->s+z;
	if (l==r) return now;
	int mid=(l+r)>>1;
	if (x<=mid) p=p->lc,now->lc=change(l,mid,x,z);
	else p=p->rc,now->rc=change(mid+1,r,x,z);
	return now;
}
	
void adj(int x,int y,int z)
{
	if (x==0) return ;
	for (int i=x;i<=n;i+=(i&-i)) p=rot[i],rot[i]=change(0,num,y,z);
}       

void fill(int k)
{
	st[k].clear();
	st[k].push_back(sum[v[k]]);
	for (int i=ll[v[k]];i>0;i-=(i&-i)) st[k].push_back(rot[i]);
}

int getsum(int k)
{
	int ans=0, n=st[k].size();
	for (int i=0;i<n;i++) ans+=st[k][i]->s;
	return ans;
}

int getsize(int k)
{
	int ans=0, n=st[k].size();
	for (int i=0;i<n;i++) ans+=st[k][i]->rc->s;
	return ans;
}

void goleft(int k)
{
	int n=st[k].size();
	for (int i=0;i<n;i++) st[k][i]=st[k][i]->lc;
}

void goright(int k)
{
	int n=st[k].size();
	for (int i=0;i<n;i++) st[k][i]=st[k][i]->rc;
}

int query(int l,int r,int k)
{
	if (k>getsum(1)+getsum(2)-getsum(3)-getsum(4)) return 0;
	if (l==r) return l;
	int tmp=getsize(1)+getsize(2)-getsize(3)-getsize(4);
	//cout<<l<<' '<<r<<"tmp:"<<tmp<<endl;
	int mid=(l+r)>>1;
	if (k<=tmp)
	{
		//cout<<"right\n";
		goright(1),goright(2),goright(3),goright(4);
		return query(mid+1,r,k);
	}
	else
	{
		//cout<<"left\n";
		goleft(1),goleft(2),goleft(3),goleft(4);
		return query(l,mid,k-tmp);
	}
}

int lca(int x,int y)
{
	if (dep[x]>dep[y]) swap(x,y);
	for (int i=low;i>=0;i--) 
		if (dep[fa[y][i]]>=dep[x]) y=fa[y][i];
	if (x==y) return x;
	for (int i=low;i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

void write(node *now,int l,int r)
{
	if (l==r)
	{
		cout<<now->s;
		return ;
	}
	int mid=(l+r)>>1;
	write(now->lc,l,mid);
	write(now->rc,mid+1,r);
}

void dfs(int now)
{
	ll[now]=rr[now]=++cnt;
	p=sum[fa[now][0]];
	sum[now]=change(0,num,key[now],1);

	for (int j=fir[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (fa[now][0]!=k)
		{
			fa[k][0]=now; dep[k]=dep[now]+1;
			for (int i=1;i<=low;i++) fa[k][i]=fa[fa[k][i-1]][i-1];
			dfs(k);
			rr[now]=rr[k];
		}       
	} 
}

void add(int x,int y)
{       
	e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x]; fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].next=fir[y]; fir[y]=tot; 
}
	
int main()
{
	//freopen("network10.in","r",stdin);
	//freopen("network.out","w",stdout);
	scanf("%d%d",&n,&m);
	low=log(n)/log(2.0);
	for (int i=1;i<=n;i++) scanf("%d",&key[i]),w[++num]=key[i];
	int st,ed;
	for (int i=1;i<n;i++) scanf("%d%d",&st,&ed),add(st,ed);
	num=n;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&z[i],&x[i],&y[i]);
		if (!z[i]) w[++num]=y[i];
	}
	sort(w+1,w+num+1);
	num=unique(w+1,w+num+1)-w;
	for (int i=1;i<=n;i++) key[i]=lower_bound(w+1, w+num+1, key[i])-w;
	for (int i=1;i<=m;i++) if (!z[i]) y[i]=lower_bound(w+1, w+num+1, y[i])-w;

	sum[0]=rot[0]=build(0,num);
	for (int i=1;i<=n;i++) rot[i]=rot[0];
	int root=rand()%n+1; dep[root]=1;
	dfs(root);

	for (int i=1;i<=m;i++)
	{
		if (z[i])
		{
			int tmp;
			v[1]=x[i],v[2]=y[i],v[3]=tmp=lca(x[i],y[i]),v[4]=fa[tmp][0];
			fill(1); fill(2); fill(3); fill(4);
			int ans=query(0,num,z[i]);
			if (ans)
				printf("%d\n",w[ans]);
			else 
				printf("invalid request!\n");
		}
		else
		{
			adj(ll[x[i]],key[x[i]],-1),adj(rr[x[i]]+1,key[x[i]],1);
			key[x[i]]=y[i];
			adj(ll[x[i]],key[x[i]],1),adj(rr[x[i]]+1,key[x[i]],-1);
		}
	}

	return 0;
}