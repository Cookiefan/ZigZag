#include <bits/stdc++.h>
using namespace std;

string s;
int a[1200];
int n, t, m;

int main()
{
	cin>>s;
	memset(a,0,sizeof(a));
	a[n=0]=s[0]-'0';
	int len=s.length();
	for (int i=2;i<len;i++)
		if (s[i]=='e')
		{
			m=i;
			break;
		}
		else
			a[++n]=s[i]-'0';
	int p=0;
	for (int i=m+1;i<len;i++)
		p=p*10+s[i]-'0';
	bool zero;
	if (a[0]==0) zero=1; else zero=0;
	for (int i=0;i<=p;i++)
	{
		if (zero && a[i]==0)
			zero=1;
		else
		{
			zero=0;
			printf("%d",a[i]);
		}
	}
	if (zero==1) printf("0");
	zero=1;
	for (int i=p+1;i<=n;i++) if (a[i]!=0) zero=0;
	if (p<n && !zero)
	{
		printf(".");
		for (int i=p+1;i<=n;i++)
			printf("%d",a[i]);
	}
	printf("\n");

	return 0;
}