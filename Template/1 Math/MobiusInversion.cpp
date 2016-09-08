//莫比乌斯反演
void get_prime(int n)
{
    memset(np,0,sizeof(np));
    tot=0;
    mu[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!np[i])
        {
            prime[++tot]=i;
            mu[i]=-1;
        }
        for (int j=1;j<=tot && i*prime[j]<=n;j++)
        {
            np[i*prime[j]]=1;
            if (i%prime[j]) mu[i*prime[j]]=-mu[i];
            else
            {
                mu[i*prime[j]]=0;
                break;
            }
        }
    }
}
//求与序列中第j个数互质数的个数
int main()
{
    for (int i=1;i<=100000;i++)
        for (int j=i;j<=100000;j+=i)
            sum[i]+=v[j];
    for (int i=1;i<=100000;i++)
    {
        for (int j=i;j<=100000;j+=i) f[j]+=sum[i]*mu[i];
        if (i==1) f[i]--;
    }
}