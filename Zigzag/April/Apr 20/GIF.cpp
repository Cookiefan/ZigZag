#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
string word[maxn];
int n;
int a[maxn];
string code, s;

int main()
{
	cin>>code;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		cin>>s;
		word[i]=s;
	}
	int len=code.length();
	for (int i=0;i<len;i++)
	{
		int x=code[i]-'0';
		cout<<word[x];
		if (i!=len-1)
		{
			int y=code[i+1]-'0';
			word[n++]=word[x]+word[y][0];
		}
	}	
	return 0;
}