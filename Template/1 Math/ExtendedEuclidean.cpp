//扩展欧几里得
LL ex_gcd(LL a, LL b, LL &x, LL &y)
{
    if (!b)
    {
        x=1, y=0;
        return a;
    }
    else
    {
        LL d=ex_gcd(b, a % b, y, x);
        y-=a/b*x;
        return d;
    }
}
//求乘法逆元
LL inv(LL a, LL p)
{
    LL gcd, x, y;
    gcd=ex_gcd(a, p, x, y);
    if (gcd==1) return (x+p)%p;
    else return -1;
}