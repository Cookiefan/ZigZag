#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#define oo 1000000007
#define maxn 12000

using namespace std;

struct bit
{
	int b[maxn];
	int num;
	bit(){}
	bit(int n):num(n){}
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) b[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i;i-=(i&-i)) tmp+=b[i];
		return tmp;
	}
	void clear()
	{
		memset(b,0,sizeof(b));
	}
}s;
int n;
int a[maxn], b[maxn], c[maxn], v[maxn];
map<int, int> ans;

int get_kth(int k)
{
	int l=1, r=n, tmp;
	while (l<=r)
	{
		int mid=(l+r)>>1;
		if (s.ask(mid)>=k)
		{
			r=mid-1;
			tmp=mid;
		}
		else
			l=mid+1;
	}
	return tmp;
}

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		memcpy(b, a, sizeof(b));
		sort(b+1, b+n+1);
		for (int i=1;i<=n;i++) c[i]=lower_bound(b+1, b+n+1, a[i])-b, v[c[i]]=a[i];
		s=bit(n+1);
		ans.clear();
		for (int i=1;i<=n;i++)
		{
			s.clear();
			for (int j=i;j<=n;j++)
			{
				//cout<<i<<' '<<j<<' ';
				s.add(c[j], 1);
				if ((j-i+1)%2==1)
				{
					int x=v[get_kth((j-i)/2+1)];
					//cout<<x<<endl;
					if (ans.find(x)==ans.end()) ans[x]=0;
					ans[x]++;
				}
				else
				{
					int x=v[get_kth((j-i)/2+1)];
					int y=v[get_kth((j-i)/2+2)];
					//cout<<x<<' '<<y<<endl;
					if ((x+y)%2==0)
					{
						if (ans.find((x+y)/2)==ans.end()) ans[(x+y)/2]=0;
						ans[(x+y)/2]++;
					}
				}
			}
		}
		for (int i=1;i<=n;i++)
			if (ans.find(a[i])!=ans.end())
				printf(i==n?"%d\n":"%d ",ans[a[i]]);
			else
				printf(i==n?"%d\n":"%d ",0);
	}
	return 0;
}