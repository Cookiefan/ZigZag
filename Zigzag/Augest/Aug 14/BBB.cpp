#include <bits/stdc++.h>
#define maxn 500
using namespace std;

typedef long long LL;
LL oo=1000000007;
LL b[maxn];
LL a[maxn][maxn], ans;
vector<int> prime;
int np[5000];
int num, n;

LL exp(LL a, LL b, LL p)
{
	a%=p;
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp=(tmp*a)%p;
		a=a*a%p;
		b=b/2;
	}
	return tmp;
}

int gauss(int n, int m)
{
    int k=1;
    for (int i=1;i<=m;i++)
    {
        int p=0;
        for (int j=k;j<=n;j++) if (a[j][i]) {    p=j; break;    }
        if (!p) continue;
        for (int l=1;l<=m;l++) swap(a[p][l],a[k][l]);
        for (int j=k+1;j<=n;j++)
        	if (a[j][i]==1)
	           for (int l=1;l<=m;l++)
    	           	a[j][l]=a[j][l]^a[k][l];
        k++;
    }
    return k-1;
}

void get_prime(int n)
{
	memset(np,0,sizeof(np));
	for (int i=2;i<=n;i++)
	{
		if (!np[i])
			prime.push_back(i);
		for (int j=0;j<prime.size()&&prime[j]*i<=n;j++)
		{
			np[prime[j]*i]=1;
			if (i%prime[j]==0)
				break;
		}
	}
}

// const int BufferSize=1<<16;
// char buffer[BufferSize],*head,*tail;
// inline char Getchar() {
//     if(head==tail) {
//         int l=fread(buffer,1,BufferSize,stdin);
//         tail=(head=buffer)+l;
//     }
//     return *head++;
// }
inline LL read() {
    LL x=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    return x*f;
}

int main()
{
	get_prime(2001);
	num=prime.size();
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) b[i]=read();
		for (int i=1;i<=n;i++)
		{
			for (int j=0;j<num;j++)	
			{
				int tmp=0;			
				while (b[i]%prime[j]==0)
				{
					b[i]/=prime[j];
					tmp^=1;
				}
				a[i][j+1]=tmp;
			}
		}
		int cnt=gauss(n, num);
		LL ans=(exp(2, n-cnt, oo)-1+oo)%oo;
		printf("Case #%d:\n%I64d\n",o, ans);
	}
	return 0;
}