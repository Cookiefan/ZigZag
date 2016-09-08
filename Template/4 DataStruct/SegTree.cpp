//线段树最大连续1
struct segtree
{
	int mx[maxn*8], lmx[maxn*8], rmx[maxn*8], size[maxn*8];
	void update(int x)
	{
		mx[x]=max(max(mx[x*2],mx[x*2+1]),rmx[x*2]+lmx[x*2+1]);
		if (lmx[x*2]==size[x*2]) lmx[x]=size[x*2]+lmx[x*2+1];
		else lmx[x]=lmx[x*2];
		if (rmx[x*2+1]==size[x*2+1]) rmx[x]=size[x*2+1]+rmx[x*2];
		else rmx[x]=rmx[x*2+1];
	}
	void build(int x,int l,int r)
	{
		if (l==r)
		{
			size[x]=1;
			return ;
		}
		int mid=(l+r)>>1;
		build(x*2,l,mid);
		build(x*2+1,mid+1,r);
		size[x]=size[x*2]+size[x*2+1];
	}
	void add(int x, int l, int r, int pos, int z)
	{
		if (l==r)
		{
			mx[x]=lmx[x]=rmx[x]=z;
			return ;
		}
		int mid=(l+r)>>1;
		if (pos<=mid) add(x*2, l, mid, pos, z);
		else add(x*2+1, mid+1, r, pos, z);
		update(x);
	}
	int ask(int x, int l, int r, int ll, int rr, int &res)
	{
		if (ll<=l && r<=rr)
		{
			int tmp=max(res+lmx[x], mx[x]);
			if (rmx[x]==size[x]) res+=size[x];
			else res=rmx[x];
			return tmp;
		}
		int mid=(l+r)>>1, tmp=0;
		if (ll<=mid) tmp=max(tmp,ask(x*2, l, mid, ll, rr, res));
		if (rr>mid) tmp=max(tmp,ask(x*2+1, mid+1, r, ll, rr, res));
		return tmp;
	}
	void init()
	{
		memset(mx,0,sizeof(mx));
		memset(lmx,0,sizeof(lmx));
		memset(rmx,0,sizeof(rmx));
	}
}tree;