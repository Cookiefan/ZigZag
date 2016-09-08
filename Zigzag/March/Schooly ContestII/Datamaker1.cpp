#include <bits/stdc++.h>
#define maxn 120
using namespace std;
int a[maxn][maxn],b[maxn][maxn];
int n,m;

int main()
{
	freopen("Escape.in","w",stdout);
	cout<<10<<endl;
	cout<<"1 1\n";
	cout<<"1\n";
	cout<<"2\n";
	cout<<"3 4\n";
	cout<<"2 2\n";
	cout<<"2 1\n";
	cout<<"1 2\n";
	cout<<"2 2\n";
	cout<<"2 1 2\n";
	cout<<"2 1 2\n";
	srand(time(0));
	for (int k=1;k<=5;k++)
	{
		n=k*(rand()%10+10); m=k*(rand()%10+10);
		cout<<n<<' '<<m<<endl;
		for (int i=1;i<=n+1;i++)
		{
			for (int j=1;j<=m-1;j++)
				cout<<rand()%100<<' ';
			cout<<rand()%100<<endl;
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
				cout<<rand()%100<<' ';
			cout<<rand()%100<<endl;
		}
	}
	n=99, m=99;
	cout<<n<<' '<<m<<endl;
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=n+1;j++)
			a[i][j]=b[i][j]=rand()%10;
	for (int i=1;i<=n/2+2;i++)
		for (int j=i;j<=m-i+1;j++)
			a[i][j]=100;
	for (int i=n/2+3;i<=n+1;i++)
		for (int j=n-i+3;j<=i-1;j++)
			a[i][j]=100;
	for (int j=1;j<=m/2+1;j++)
		for (int i=j;i<=n-j+2;i++)
			b[i][j]=100;
	for (int j=m/2+2;j<=m+1;j++)
		for (int i=n-j+2;i<=j-1;i++)
			b[i][j]=100;
	for (int i=1;i<=n+1;i++)
	{
		for (int j=1;j<m;j++)
			cout<<a[i][j]<<' ';
		cout<<a[i][m]<<endl;
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			cout<<b[i][j]<<' ';
		cout<<b[i][m+1]<<endl;
	}
	n=100, m=100;
	cout<<n<<' '<<m<<endl;
	for (int i=1;i<=n+1;i++)
	{
		for (int j=1;j<m;j++)
			cout<<rand()%10<<' ';
		cout<<rand()%10<<endl;
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			cout<<100<<' ';
		cout<<100<<endl;
	}

	n=99, m=88;
	cout<<n<<' '<<m<<endl;
	for (int i=1;i<=n+1;i++)
	{
		for (int j=1;j<m;j++)
			cout<<1<<' ';
		cout<<1<<endl;
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			cout<<1<<' ';
		cout<<1<<endl;
	}

	return 0;
}