#include <bits/stdc++.h>
#define maxn 100200
using namespace std;
char s[maxn];
vector<int> pos;
int n,m;

int main()
{
	while (scanf("%d",&m) && m)
	{
		scanf(" %s",s);
		n=strlen(s);
		int mx=-1;
		for (int i=0;i<n;i++)
			mx=max(mx, s[i]-'a');
		pos.clear();
		for (int i=0;i<n;i++)
			if (s[i]-'a'==mx)
				pos.push_back(i);
		int tot=pos.size();
		for (int i=0;i<n;i++)
			if (s[i]-'a'!=mx && (i==0 || s[i-1]-'a'==mx))
				tot++;
		if (k>=tot) printf("%c\n",'a'+mx);
		


	}
	return 0;
}