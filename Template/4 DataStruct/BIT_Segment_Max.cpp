//BIT求最值
struct mx_bit
{
	int mx[maxn],key[maxn];
	int num;
	void cov(int x,int z)
	{
		key[x]=z;
		for (int i=x;i<=num;i+=(i&-i))
			mx[i]=max(mx[i],z);
	}
	int ask(int l,int r)
	{
		int tmp=-inf;
		while (l<=r)
		{
			tmp=max(tmp,key[r]);
			for (r-=1;r-(r&-r)>=l;r-=(r&-r))
				tmp=max(tmp,mx[r]);
		}
		return tmp;
	}
	void init(int x)
	{
		num=x;
		memset(mx,0,sizeof(mx));
		memset(key,0,sizeof(key));
	}
}tree;