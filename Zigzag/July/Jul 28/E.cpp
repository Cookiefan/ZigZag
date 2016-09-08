#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
typedef long long LL;
LL p[maxn],a[maxn];
vector<LL> b[20];
vector<LL> q, e;
int n;
LL low, high;


LL gcd(LL a, LL b)
{
	return (!b)?a:gcd(b, a%b);
}
LL lcm(LL a, LL b)
{
	return a*b/gcd(a,b);
}

// 扩展欧几里得
// a , b 任意
void EXT_GCD(LL a, LL b, LL &d, LL &x, LL &y)
{
  if(!b) {d = a, x = 1, y = 0;}
  else {EXT_GCD(b, a % b, d, y, x), y -= x * (a / b);}
}
LL slow_mul(LL a, LL b, LL p)
{
  if (b < 0 && a >= 0) swap(a, b);
  else if (a < 0 && b < 0) {a = -a; b = -b;}
  LL ret = 0;  
  while(b) {  
    if(b & 1) ret = (ret + a) % p;  
    a = (a + a) % p;
    b >>= 1;  
  }  
  return ret % p;  
}

// 中国剩余定理
// x ≡ a[i] (mod m[i])
// m[i] is coprime
LL CRT(vector<LL> a, vector<LL> m)
{
  int n = a.size();
  // printf("=====\n");
  // for (int i = 0; i < n; i++)
  // 	printf("%I64d %I64d\n", a[i], m[i]);
  LL M = 1, Mi, x0, y0, d, ret = 0;
  for(int i = 0; i < n; i++)
    M *= m[i];
  for(int i = 0; i < n; i++)
  {
    Mi = M/m[i];
    EXT_GCD(Mi, m[i], d, x0, y0);
    LL tmp = slow_mul(Mi, x0, M);
    tmp = slow_mul(tmp, a[i], M);
    ret = (ret + tmp) % M;
    //ret = (ret+Mi*x0*a[i]) % M;
  }
  if(ret <= 0)
    ret += M;
  return ret;
}

int count(int x)
{
	int tmp=0;
	while (x)
	{
		tmp+=(x&1);
		x>>=1;
	}
	return tmp;
}

LL get_ans(LL a, LL b, LL c)
{
	if (a<b) return 0;
	else return (a-b)/c+1;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%I64d%I64d",&n, &low, &high);
		int x,y;
		for (int i=0;i<n;i++)
			scanf("%I64d%I64d",&p[i], &a[i]);
		for (int i=0;i<=n;i++) b[i].clear();
		for (int msk=0;msk<=(1<<n)-1;msk++)
			b[count(msk)].push_back(msk);
		LL ans=0;
		for (int len=0;len<=n;len++)
			for (int j=0,ss=b[len].size();j<ss;j++)
			{
				LL k=7;
				int msk=b[len][j];
				q.clear(); e.clear();
				for (int i=0;i<n;i++)
					if ((msk>>i)&1)
					{
						q.push_back(p[i]);
						e.push_back(a[i]);
						k=lcm(k, p[i]);
					}
				q.push_back(7);
				e.push_back(0);
				LL tmp=CRT(e, q);
				//printf("tmp = %I64d\n", tmp);
				//cout<<k<<endl;

				//cout<<(len&1)<<endl;
				if (len&1) ans-=get_ans(high ,tmp, k)-get_ans(low-1, tmp, k);
				else ans+=get_ans(high ,tmp, k)-get_ans(low-1, tmp, k);


				//cout<<ans<<endl;
			}
		printf("Case #%d: %I64d\n",o,ans);
	}
	return 0;
}