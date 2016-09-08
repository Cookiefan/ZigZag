//Lucas定理(求组合数取模,注意p<=10^5)
LL com(LL n,LL m,LL p)
{
	if (m>n) return 0;
	LL ans=1;
	for (int i=1;i<=m;i++)
	{
		ans=ans*(n-i+1)%p;
		ans=ans*exp(i,p-2,p)%p;
	}
	return ans;
}

LL lucas(LL n,LL m,LL p)
{
	if (m==0) return 1;
	return (com(n%p,m%p,p)*lucas(n/p,m/p,p))%p;
}

LL get_ans(LL n, LL m)
{
	return lucas(n+m,n,oo);
}