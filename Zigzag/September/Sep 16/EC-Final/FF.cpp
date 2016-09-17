#include <bits/stdc++.h>
#define maxn 1200000
using namespace std;
typedef long long LL;
const LL oo=1e9+7;

int n,m;
LL s[maxn];
int a[maxn];

const int sz=13;

int solve(int msk)
{
	for (int i=0;i<sz;i++)
		a[i]=((msk>>i)&1);
	int sum=0;
	for (int i=0;i<sz;i++)
		if (a[i]==1)
		{
			sum+=i+1;
			a[i]=0;
		}
		else
		{
			a[i]=(sum+i+1);
			sum=0;
		}
	if (sum>0) a[sz-1]=sum;
	// for (int i=0;i<sz;i++)
	// 	cout<<a[i]<<' '; cout<<endl;
	int now=-1, val=0;
	for (int i=0;i<sz;i++)
		if (a[i]>0)
		{
			if (now==-1)
			{
				now=i;
				val=a[i];
			}
			else
			{
				if (val<a[i])
					now=i;
				val+=a[i];
			}
		}
	return now;
}

void write(int x)
{
	for (int i=0;i<sz;i++)
		cout<<((x>>i)&1);
	cout<<"   ";
}

int v[100];

int main()
{
	s[0]=0;
	for (int i=1;i<=1000000;i++) s[i]=s[i-1]+i;
	for (int i=0;i<(1<<sz);i++)
	{
		// if (solve(i)+1==2)
		// {
		// 	write(i);
		// 	cout<<' '<<solve(i)+1<<endl;
		// }
		v[solve(i)+1]++;
	}
	for (int i=1;i<=sz;i++)
		cout<<i<<' '<<v[i]<<endl;
	return 0;
}