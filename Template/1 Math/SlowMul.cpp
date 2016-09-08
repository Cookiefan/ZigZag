//慢速乘
llg mul(llg a,llg b,llg p)
{
	a%=p,b%=p;
	llg tmp=0;
	while (b)
	{
		if (b&1) tmp=(tmp+a)%p;
		a=(a+a)%p;
		b/=2;
	}
	return tmp;
}
