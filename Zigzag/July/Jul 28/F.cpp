#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
typedef LL long long;
string s;
char c;
int n;
int p[maxn];
LL ans;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%c ",&c);
		cin>>s;
		int n=s.length();
		p[n]=-1;
		for (int i=n-1;i>=0;i--)
			if (s[i]!=ch)
				p[i]=p[i+1]
			else
				p[i]=i;
	}

	return 0;
}