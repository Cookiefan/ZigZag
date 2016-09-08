//BIT改段求段
struct bit
{
	int b[maxn];
	int num;
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) b[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i;i-=(i&-i)) tmp+=b[i];
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(b,0,sizeof(b));
	}
}s,t;

void ins(int x,int y,int z)
{
	s.add(x,z); s.add(y+1,-z);
	t.add(x,z*x); t.add(y+1,-z*(y+1));
}

int query(int x,int y)
{
	int tmp=s.ask(y)*(y+1)-s.ask(x-1)*x-(t.ask(y)-t.ask(x-1));
	return tmp;
}