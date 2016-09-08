//中国剩余定理(互质)
LL crt(int n, LL* a, LL* p)
{
    LL pp=1, tmp=0;
    for(int i=0;i<n;i++) pp=pp*p[i];
    for(int i=0;i<n;i++)
    {
        LL m=pp/p[i], x, y;
        ex_gcd(m,p[i],x,y);
        x=(x%p[i]+p[i])%p[i];
        tmp=(tmp+(a[i]*m%pp*x)%pp)%pp;//注意overflow
    }
    return tmp;
}