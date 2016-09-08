#include <bits/stdc++.h>
using namespace std;

class Sunnygraphs2
{
public:
	long long two[64];
	int v[64], mark[64];
	vector<int> comp;
	long long count(vector <int> a)
	{
		two[0]=1;
		for (int i=1;i<=51;i++) two[i]=two[i-1]*2;
		long long ans=1;
		int n=a.size();
		memset(v,-1,sizeof(v));
		memset(mark,0,sizeof(mark));
		comp.clear();
		for (int i=0;i<n;i++)
		{
			int x=i;
			while (1)
			{
				v[x]=i;
				if (v[a[x]]!=i) x=a[x];
				else
				{
					if (mark[a[x]]) break;
					int tmp=a[x], cnt=1;
					while (tmp!=x)
					{
						mark[tmp]=1;
						tmp=a[tmp];
						cnt++;
					}
					mark[x]=1;
					comp.push_back(cnt);
					break;
				}
			}
		}
		int remain=n, num=comp.size();
		for (int i=0;i<num;i++)
		{
			//cout<<comp[i]<<endl;
			ans*=(two[comp[i]]-1);
			remain-=comp[i];
		}
		ans*=two[remain];
		if (num<=1) ans++;
		return ans;
	}
}T;

int main()
{
	vector<int> a;
	int n,x;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&x), a.push_back(x);
	printf("%I64d\n",T.count(a));
	
	return 0;
}