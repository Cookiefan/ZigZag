#include <bits/stdc++.h>
using namespace std;

int main()
{
	string s;
	cin>>s;
	int sum=0;
	int len=s.length();
	for (int i=0;i<len;i++)
		if (s[i]=='2') sum++;
	double ans=(double)sum*1.0/(len-(s[0]=='-'));
	if (s[0]=='-') ans*=1.5;
	if ((s[len-1]-'0')%2==0) ans*=2;
	printf("%.2f",ans*100);
	cout<<'%'<<endl;
	return 0;
}