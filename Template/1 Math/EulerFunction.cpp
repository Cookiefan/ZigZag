//欧拉函数
long long phi(long long x)
{
	long long cnt=x;
	for (long long i=2;i*i<=x;i++)
		if (x%i==0)
		{
			cnt=cnt/i*(i-1);
			while (x%i==0) x=x/i;
		}
	if (x>1) cnt=cnt/x*(x-1);
	return cnt;
}