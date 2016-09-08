#include <bits/stdc++.h>
using namespace std;
int n;

long long gcd(long long a,long long b)
{
	//cout<<a<<' '<<b<<endl;
    return (b==0?a:gcd(b, a%b));
}


int main()
{
	scanf("%d",&n);
	for (int o=1;o<=n;o++)
	{
		int ans=o*o;
		for (int i=0;i<o;i++)
		{
			ans-=gcd(o, i);
			// 	cout<<(i*j%n!=0)<<' ';
			// cout<<endl;
		}
		cout<<o<<":  "<<ans<<endl;
	}

	return 0;
}