#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
char a[maxn][10];
bool flag;
int n;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf(" %s",a[i]);
	flag=0;
	for (int i=1;i<=n;i++)
	{
		if (a[i][0]=='O' && a[i][1]=='O')
		{
			a[i][0]=a[i][1]='+';
			flag=1;
			break;
		}
		if (a[i][3]=='O' && a[i][4]=='O')
		{
			a[i][3]=a[i][4]='+';
			flag=1;
			break;
		}
	}
	if (!flag) printf("NO\n");
	else
	{
		printf("YES\n");
		for (int i=1;i<=n;i++) cout<<a[i]<<endl;
	}

	return 0;
}