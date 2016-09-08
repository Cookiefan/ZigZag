#include <bits/stdc++.h>
using namespace std;
const char n_1[20][20]={"zero","one","two","three","four","five","six","seven","eight","nine",
                "ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
const int m_1[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};                
const char n_2[10][20]={"","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
const int m_2[10]={0,0,20,30,40,50,60,70,80,90};

string s; 

void write(int x)
{
	if (x==0) return ;
	if (x>=1000)
	{
		write(x/1000);
		s=s+" thousand";
		x=x%1000;
		if (x>0)
		{
			s=s+" ";
			write(x%1000);
		}
	}
	else
	{
		if (x>=100)
		{
			write(x/100);
			s=s+" hundred";
			x=x%100;
			if (x>0)
			{
				s=s+" and ";
				write(x%100);
			}
		}
		else
		{
			
			if (x>=20)
			{
				s=s+n_2[x/10];
				x=x%10;
				if (x>0)
				{
					s=s+"-";
					s=s+n_1[x];
				}
			}
			else
				s=s+n_1[x];
		}
	}
}
int n;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int ans=0;
		for (int i=1;i<=n;i++)
		{
			s.clear();
			write(i);
			int len=s.length();
			int tmp=0;
			for (int j=0;j<len;j++)
				if (islower(s[j]))
					tmp++;
			ans+=tmp;
		}
		printf("%d\n",ans);
	}
	return 0;
}
