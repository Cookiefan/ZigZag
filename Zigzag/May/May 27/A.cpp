#include <bits/stdc++.h>
using namespace std;

class TriangleTriples
{
public:
	long long oo;
	TriangleTriples(){oo=1000000007;}
	long long rev(long long x)
	{
		if (x==1) return x;
		else return (oo-oo/x)*rev(oo%x)%oo;
	}
	long long cal(long long n)
	{
		if (n<0) return 0;
		else return (((n-1)*n%oo)*(n+1)%oo)*rev(6)%oo;
	}
	long long cnt(int a, int b, int c)
	{
		long long ans=(long long)(cal(c)+(oo-cal(c-a))+(oo-cal(c-b))+cal(c-a-b))%oo;
		//cout<<ans<<endl;
		return ans;
	}
	int count(int A, int B, int C)
	{
		long long ans=((long long)A*B%oo)*C%oo;
		//cout<<ans<<endl;
		ans=(ans+(oo-cnt(A,B,C))+(oo-cnt(C,A,B))+(oo-cnt(B,C,A)))%oo;
		return ans;
	}
};

int main()
{
	TriangleTriples T;
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	printf("%d\n",T.count(a,b,c));
	return 0;
}