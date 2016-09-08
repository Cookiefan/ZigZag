#include <bits/stdc++.h>
#define maxn 1200
#define p 10
using namespace std;

struct high
{
	int e[12000];
	void clean(){
		memset(e,0,sizeof(e));
	}
}a;

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
}

int main()
{
	high a;
	a.clean();
	read(a);
	int sum=0;
	for (int i=1;i<=a.e[0];i++) sum+=a.e[i];
	if (sum%3==0)
	{
		write(a/3); cout<<' ';
		write(a/3); cout<<' ';
		write(a/3);
	}
	else
		printf("-1\n");
	return 0;
}