#include <bits/stdc++.h>
#define maxn 1200
using namespace std;

string s,t;
string ax,ay;
typedef pair<int,int> pii;
vector<pii> q;
int f[maxn][maxn];
int n,m,x,y,ans;

void waterman()
{
	memset(f,0,sizeof(f));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			f[i][j]=max(f[i-1][j-1]+(s[i-1]==t[j-1]?3:-1),max(f[i-1][j]-2, f[i][j-1]-2));
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<=m;j++)
		{
			if (f[i][j]>ans)
			{
				ans=f[i][j];
				x=i;
				y=j;
			}
			cout<<f[i][j]<<' ';
		}
		cout<<endl;
	}
}

void find_path()
{
	while (x && y)
	{
		if (f[x][y]==f[x-1][y]-2 || !y)
		{
			ax='-'+ax;
			ay=t[--x]+ay;
		}
		else if (f[x][y]==f[x][y-1]-2 || !x)
		{
			ay='-'+ay;
			ax=s[--y]+ax;
		}
		else if (f[x][y]==f[x-1][y-1]+3 || f[x][y]==f[x-1][y-1]-1)
		{
			ax=s[--y]+ax;
			ay=t[--x]+ay;
		}
	}
	cout<<ax<<endl;
	cout<<ay<<endl;

}

int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	cout<<"Please input two strings with ACGT:\n";
	cin>>s>>t;
	n=s.length(), m=t.length();
	cout<<"the process of algorithm is:\n";
	waterman();
	cout<<"the result of the program is:\n";
	cout<<f[n][m]<<endl;
	find_path();
	return 0;
}
/*
ACACACTA
AGCACACA
*/