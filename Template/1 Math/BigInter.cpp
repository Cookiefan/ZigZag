//高精度
struct high
{
	int e[100];
	void clean()
	{
		memset(e,0,sizeof(e));
	}
}a;

high operator +(high a,high b)
{
	high c; c.clean();
	c.e[0]=max(a.e[0],b.e[0]);
	for (int i=1;i<=c.e[0];i++)
	{
		c.e[i]+=a.e[i]+b.e[i];
		c.e[i+1]+=c.e[i]/p;
		c.e[i]=c.e[i]%p;
	}
	if (c.e[c.e[0]+1]) c.e[0]++;
	return c;
}

high operator -(high a, high b)
{
	high c; c.clean();
	int add=0;
	c.e[0]=max(a.e[0],b.e[0]);
	for (int i=1;i<=c.e[0];i++)
	{
		c.e[i]=a.e[i]-add-b.e[i];
		if (c.e[i]<0) c.e[i]+=p, add=1;
		else add=0;
	}
	while (c.e[c.e[0]]==0) c.e[0]--;
	return c;
}

high operator *(high a,high b)
{
	high c; c.clean();
	c.e[0]=a.e[0]+b.e[0]-1;
	for (int i=1;i<=a.e[0];i++)
		for (int j=1;j<=b.e[0];j++)
			c.e[i+j-1]+=a.e[i]*b.e[j];
	for (int i=1;i<=c.e[0];i++)
	{
		c.e[i+1]+=c.e[i]/p;
		c.e[i]=c.e[i]%p;
	}
	if (c.e[c.e[0]+1]) c.e[0]++;;
	return c;
}

high operator /(high a,int b)
{
	int down=0;
	high c; c.clean();
	c.e[0]=a.e[0];
	for (int i=a.e[0];i;i--)
	{
		c.e[i]=(a.e[i]+down*p)/b;
		down=(a.e[i]+down*p)-c.e[i]*b;
	}
	while ((c.e[c.e[0]]==0)&&(c.e[0]>0)) c.e[0]--;
	return c;
}

int operator %(high a,int b)
{
	int mod;
	for (int i=a.e[0];i;i--)
		mod=((mod*p%b)+a.e[i])%b;
	return mod;
}

high max(high a,high b)
{
	if (a.e[0]>b.e[0]) return a;
	if (a.e[0]<b.e[0]) return b;
	for (int i=a.e[0];i;i--)
	{
		if (a.e[i]>b.e[i]) return a;
		if (a.e[i]<b.e[i]) return b;
	}
	return a;
}

void read(high &a)
{
	char ch=getchar(); high x; x.clean();
	for (;ch<'0'||ch>'9';ch=getchar());
	for (;ch>='0'&&ch<='9';ch=getchar()) x.e[++x.e[0]]=ch-'0';
	for (int i=1;i<=x.e[0];i++) a.e[x.e[0]-i+1]=x.e[i];
	a.e[0]=x.e[0];
}

void write(high a)
{
	printf("%d",a.e[a.e[0]]);
	for (int i=a.e[0]-1;i>0;i--) printf("%d",a.e[i]);
	printf("\n");
}