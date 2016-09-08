//匈牙利算法(二分图匹配)
bool match(int i)
{
	for (int j=fir[i];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!vis[k])
		{
			vis[k]=1;
			if ((!mch[k])||(match(mch[k])))
			{
				mch[k]=i;
				return 1;
			}
		}
	}
	return 0;
}

int hungary()
{
	int tmp=0;
	memset(mch,0,sizeof(mch));
	for (int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if (match(i)) tmp++;
	}
	return tmp;
}
