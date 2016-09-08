//四边形不等式
for (int len=2;len<=n;len++)
{
	for (int i=1;i<=n-len+1;i++)
	{
		int j=i+len-1;
		f[i][j]=inf;
		for (int k=K[i][j-1];k<=min(j-1,K[i+1][j]);k++)
		{
			if (f[i][j]>f[i][k]+f[k+1][j]+x[k+1]-x[i]+y[k]-y[j])
			{
				f[i][j]=f[i][k]+f[k+1][j]+x[k+1]-x[i]+y[k]-y[j];
				K[i][j]=k;
			}
		}
	}
}