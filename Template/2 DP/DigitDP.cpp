//数位动归
int get_ans(int x)
{
	if (!x) return 1;
	int len=0,tmp=0;
	while (x)
	{
		b[++len]=x%10;
		x=x/10;
	}
	b[1]++;
	b[len+1]=0;
	b[len+2]=0;
	for (int i=len;i>=1;i--)//固定第i+1位之前的位
	{
		if (b[i+1]==4) break;
		if (b[i+2]==6&&b[i+1]==2) break;
		for (int j=0;j<b[i];j++)//枚举第i位
		{
			if ((b[i+1]==6&&j==2)||(j==4)) continue ;
			tmp+=f[i-1][0]+f[i-1][1]*(j!=6);
		}
	}
	return tmp;
}