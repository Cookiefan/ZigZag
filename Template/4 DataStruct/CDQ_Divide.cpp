//CDQ分治(带修改区间k大)
int n,m,tot,cnt;
int a[maxn], ans[maxm];

struct query
{
	int id,x,y,k,cur;
	query(){}
	query(int id,int x,int y,int k,int cur):
		id(id),x(x),y(y),k(k),cur(cur){}
}q[maxm],q1[maxm],q2[maxm];

struct bit
{
	int num;
	int s[maxn];
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) s[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i>=1;i-=(i&-i)) tmp+=s[i];
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(s,0,sizeof(s));
	}
}tree;

void solve(int st,int ed,int l,int r)
{
	if (st>ed) return ;
	if (l==r)
	{
		for (int i=st;i<=ed;i++) ans[q[i].id]=l;
		return ;
	}
	int mid=(l+r)>>1, n1=0, n2=0;;
	for (int i=st;i<=ed;i++)
	{
		if (q[i].id==0)
		{
			if (q[i].y<=mid)
			{
				tree.add(q[i].x, q[i].k);
				q1[n1++]=q[i];
			}
			else
				q2[n2++]=q[i];
		}
		else
		{
			int tmp=tree.ask(q[i].y)-tree.ask(q[i].x-1);
			if (q[i].cur+tmp>=q[i].k) 
				q1[n1++]=q[i];
			else 
			{
				q[i].cur+=tmp;
				q2[n2++]=q[i];
			}
		}
	}
	for (int i=st;i<=ed;i++)
		if (q[i].id==0 && q[i].y<=mid) tree.add(q[i].x, -q[i].k);
	for (int i=0;i<n1;i++) q[st+i]=q1[i];
	for (int i=0;i<n2;i++) q[st+n1+i]=q2[i];
	solve(st,st+n1-1,l,mid);
	solve(st+n1,ed,mid+1,r);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--)
	{
		scanf("%d%d",&n,&m);
		tot=cnt=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			q[tot++]=query(0,i,a[i],1,0);
		}
		int x,y,z;
		char sign;
		for (int i=1;i<=m;i++)
		{
			scanf(" %c",&sign);
			if (sign=='C')
			{
				scanf("%d%d",&x,&y);
				q[tot++]=query(0,x,a[x],-1,0);
				a[x]=y;
				q[tot++]=query(0,x,a[x],1,0);
			}
			else
			{	
				scanf("%d%d%d",&x,&y,&z);
				q[tot++]=query(++cnt,x,y,z,0);
			}
			
		}
		tree.init(n);
		solve(0,tot-1,0,inf);
		for (int i=1;i<=cnt;i++) printf("%d\n",ans[i]);
	}
	return 0;
}