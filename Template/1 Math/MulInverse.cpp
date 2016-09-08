//递归求逆元
LL rev(LL x)
{
	if (x==1) return 1;
	else return (oo-oo/x)*rev(oo%x)%oo;
}