//慢速乘
LL mul(LL a,LL b,LL p)
{
	a%=p,b%=p;
	LL tmp=0;
	while (b)
	{
		if (b&1) tmp=(tmp+a)%p;
		a=(a+a)%p;
		b/=2;
	}
	return tmp;
}
//黑科技
LL mul( LL x, LL y, LL p )
{
    LL tmp=((LL)((double)x*y/p+1e-6 )*p);
    return x*y - tmp;
}
//汇编乘法
inline LL mul(LL x, LL y, LL mod)
{
    LL ret = 0;
    __asm__("movq %1,%%rax\n imulq %2\n idivq %3\n":"=d"(ret):"m"(x),"m"(y),"m"(mod):"%rax");
    return ret;
}
