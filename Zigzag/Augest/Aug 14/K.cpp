#include <bits/stdc++.h>
using namespace std;

int v[1000];
int n;
string s;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		cin>>s;
		n=s.length();
		memset(v,0,sizeof(v));
		int ans=0;
		for (int i=0;i<n;i++)
			if (!v[s[i]-'a'])
			{
				v[s[i]-'a']=1;
				ans++;
			}
		printf("Case #%d: %d\n",o,ans);
	}
	return 0;

}