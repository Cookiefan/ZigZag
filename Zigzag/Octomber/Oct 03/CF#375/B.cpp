#include <bits/stdc++.h>
#define maxn 1002
using namespace std;

char c;
int main()
{
	int n;
	scanf("%d",&n);
	string s;
	s.clear();
	int mx=0, sum=0, pa=0;
	for (int i=0;i<n;i++)
	{
		scanf(" %c",&c);
		if (isupper(c) || islower(c))
			s.push_back(c);
		else
		{
			if (pa) sum+=(s.length()>0);
			else mx=max(mx, (int)s.length());
			if (c=='(')
				pa=1;
			else if (c==')')
				pa=0;
			s.clear();
		}
	}
	mx=max(mx, (int)s.length());
		
	printf("%d %d\n", mx, sum);
	return 0;
}