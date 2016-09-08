#include <bits/stdc++.h>
#define maxn 220000
using namespace std;

int fa[maxn], f[maxn], a[maxn];
vector<int> s;
int n;

int find(int x)
{
	return (f[x]==-1)?x:f[x]=find(f[x]);
}

bool merge(int x, int y)
{
	int fx=find(x), fy=find(y);
	if (fx!=fy)
	{
		f[fx]=fy;
		return 1;
	}
	else
		return 0;
}

int main()
{
	scanf("%d",&n);
	memset(f,-1,sizeof(f));
	s.clear();
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) 
	{
		fa[i]=a[i];
		if (!merge(i, fa[i])) s.push_back(i);
	}
	int num=s.size(), cnt=0, st=0;
	for (int i=0;i<num;i++)
		if (a[s[i]]==s[i])
			st=i;
	for (int i=0;i<num;i++) fa[s[i]]=s[st];
	for (int i=1;i<=n;i++) cnt+=(a[i]!=fa[i]);
	printf("%d\n",cnt);
	for (int i=1;i<=n;i++)
		printf(i==n?"%d\n":"%d ", fa[i]);
	return 0;
}
