#include <stdio.h>
#include <string.h>
const char n_1[20][20]={"zero","one","two","three","four","five","six","seven","eight","nine",
                "ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
const int m_1[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};                
const char n_2[10][20]={"","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
const int m_2[10]={0,0,20,30,40,50,60,70,80,90};
char x[20], y[20], s[20];
int get_num(char *a)
{
	if (strcmp(a,"and")==0) return 0;
	int len=strlen(a);
	int i;
	for (i=0;i<len;i++)
		if (a[i]=='-')
		{
			strncpy(x, a, i);
			x[i]='\0';
			//cout<<x<<endl;
			strncpy(y, a+i+1, len-i-1);
			y[len-i-1]='\0';
			//cout<<y<<endl;
			return get_num(x)+get_num(y);
		}
	for (i=0;i<20;i++)
		if (strcmp(a,n_1[i])==0)
			return m_1[i];
	for (i=0;i<10;i++)
		if (strcmp(a,n_2[i])==0)
			return m_2[i];
	if (strcmp(a,"hundred")==0) return 100;
	if (strcmp(a,"thousand")==0) return 1000;
	return 0;
}

void write(int x)
{
	if (x==0) return ;
	if (x>=1000)
	{
		write(x/1000);
		printf(" thousand");
		x=x%1000;
		if (x>0)
		{
			printf(" ");
			write(x%1000);
		}
	}
	else
	{
		if (x>=100)
		{
			write(x/100);
			printf(" hundred");
			x=x%100;
			if (x>0)
			{
				printf(" and ");
				write(x%100);
			}
		}
		else
		{
			
			if (x>=20)
			{
				printf("%s",n_2[x/10]);
				x=x%10;
				if (x>0)
				{
					printf("-");
					printf("%s",n_1[x]);
				}
			}
			else
				printf("%s",n_1[x]);
		}
	}
}

int main()
{
	int a=0, b=0, c, now=0, tmp;
	while (scanf(" %s",s) && s[0]!='+')
	{
		tmp=get_num(s);
		//printf("%s %d\n",s, tmp);
		if (tmp>=100)
		{
			now=now*tmp;
			if (tmp>=1000)
			{
				a+=now;
				now=0;
			}
		}
		else
			now=now+tmp;
	}
	a+=now;
	now=0;
	while (scanf("%s",s) && s[0]!='=')
	{
		tmp=get_num(s);
		if (tmp>=100)
		{
			now=now*tmp;
			if (tmp>=1000)
			{
				b+=now;
				now=0;
			}
		}
		else
			now=now+tmp;
	}
	b+=now;
	//cout<<a<<' '<<b<<endl;
	c=a+b;
	//cout<<c<<endl;
	write(c);
	printf("\n");
	return 0;
}
