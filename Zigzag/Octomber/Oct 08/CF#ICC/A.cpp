#include <bits/stdc++.h>
using namespace std;

map<string,int> mp;
char s[10], t[10];

int main()
{
	mp["monday"]=0;
	mp["tuesday"]=1;
	mp["wednesday"]=2;
	mp[ "thursday"]=3;
	mp["friday"]=4;
	mp["saturday"]=5;
	mp["sunday"]=6;
	scanf(" %s",s);
	scanf(" %s",t);
	int tmp=(mp[t]-mp[s]+7)%7;
	if (tmp==0 || tmp==2 || tmp==3)
		printf("YES\n");
	else
		printf("NO\n");	

	return 0;
}