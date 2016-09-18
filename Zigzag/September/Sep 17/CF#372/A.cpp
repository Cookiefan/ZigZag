#include <bits/stdc++.h>
using namespace std;

int n;
typedef long long LL;
LL now, sum;

// bool judge(LL x, LL k)
// {
// 	if (now%k!=0) return 0;
// 	if ((now/k)%k!=0) return 0;
// 	if (now%(k+1)!=0) return 0;
// 	if ((now/(k+1))%(k+1)!=0) return 0;
// 	return 1;
// }
int main()
{
	scanf("%d",&n);
	LL tmp;
	for (int i=1;i<=n;i++)
	{
		tmp=(LL)i*(i+1)*(i+1)-(i-1);
		if (i==1) tmp=2;
		printf("%I64d\n",tmp);
	}

	return 0;
}