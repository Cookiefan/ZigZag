#include <bits/stdc++.h>
#define maxn 52000
using namespace std;
int n,cnt=0;

char s[maxn][55];

bool cmp(const char *a,const char *b)
{
	int la=strlen(a),lb=strlen(b);
	int len=la*lb;
	for (int i=0;i<len;i++)
	{
		if (a[i%la]<b[i%lb]) return 1;
		if (a[i%la]>b[i%lb]) return 0;
	}
	return 0;
}

int main()
{
	//freopen("C.in","r",stdin);
	scanf("%d ",&n);
	for (int i=0;i<n;i++) cin>>s[i];
	sort(s,s+n,cmp);
	for (int i=0;i<n;i++) cout<<s[i];
	cout<<endl;
	return 0;
}