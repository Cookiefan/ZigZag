#include <bits/stdc++.h>
#define maxn 100200
using namespace std;
int v[256];
vector<int> q;
int n, x, y;
char s[maxn];

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf(" %s",s);
		n=strlen(s);
		memset(v,0,sizeof(v));
		q.clear();
		for (int i=0;i<n;i++)
			if (!v[s[i]]) v[s[i]]=1, q.push_back(s[i]);

		sort(q.begin(), q.end());
		memset(v,-1,sizeof(v));
		for (int i=0;i<q.size();i++)
			v[q[i]]=i;

		int now=0;
		x=y=0;
		for (int i=0;i<n;i++)
		{
			if (v[s[i]]<now) continue;
			else if (v[s[i]]==now) now++;
			else
			{
				x=s[i]; y=q[now];
				break;
			}
		}
		for (int i=0;i<n;i++)
		{
			if (s[i]==x)
				printf("%c",y);
			else if (s[i]==y)
				printf("%c",x);
			else
				printf("%c",s[i]);
		}
		printf("\n");
	}
	return 0;
}