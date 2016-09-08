//floyd最小环
for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
		a[i][j]=d[i][j]=inf;
for (int i=1;i<=m;i++)
{
	scanf("%d%d%d",&x,&y,&z);
	if (z<a[x][y])
	{
		a[x][y]=a[y][x]=z;
		d[x][y]=d[y][x]=z;
	}
}
ans=inf;
for (int k=1;k<=n;k++)
{
	for (int i=1;i<k;i++)
		for (int j=i+1;j<k;j++)
			ans=min(ans,d[i][j]+a[j][k]+a[k][i]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			d[i][j]=min(d[i][j],dis[i][k]+dis[k][j]);
}