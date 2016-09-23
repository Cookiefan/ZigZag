struct bit
{
	int sum[maxn];
	int num;
	bit(){
		memset(sum,0,sizeof(sum));}
	bit(int n):num(n){
		memset(sum,0,sizeof(sum));}
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i))
			sum[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i>=1;i-=(i&-i)) 
			tmp+=sum[i];
		return tmp;
	}
	void clear()
	{
		memset(sum,0,sizeof(sum));
	}
};