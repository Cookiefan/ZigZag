//欧拉筛法
void get_prime(int n)
{
	memset(np,0,sizeof(np));
	phi[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (!np[i])
		{
			prime.push_back(i);
			phi[i]=i-1;
		}
		for (int j=0;j<prime.size()&&prime[j]*i<=n;j++)
		{
			np[prime[j]*i]=1;
			if (i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}
