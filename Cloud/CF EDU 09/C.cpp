#include <bits/stdc++.h>
#define maxn 52000
using namespace std;
int n,cnt=0;


// class Str
// {
// public:
// 	char s[66];
// public:
// 	int len()
// 	{
// 		return strlen(s);
// 	}
// }s[maxn];
// bool operator <(const Str &a, const Str &b)
// {
// 	// int la=a.len(),lb=b.len();
// 	// int len=la*lb;
// 	// for (int i=0;i<len;i++)
// 	// {
// 	// 	if (a.s[i%la]<b.s[i%lb]) return 1;
// 	// 	if (a.s[i%la]>b.s[i%lb]) return 0;
// 	// }
// 	// return 0;
// 	return strcmp(a.s,b.s)<0;
// }

string s[maxn];

bool cmp(string a, string b)
{
	int la=a.length(),lb=b.length();
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
	for (int i=1;i<=n;i++) cin>>s[i];
	sort(s+1,s+n+1,cmp);
	for (int i=1;i<=n;i++) cout<<s[i];
	cout<<endl;
	return 0;
}