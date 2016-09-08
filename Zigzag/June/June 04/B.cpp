#include <bits/stdc++.h>
using namespace std;

int main()
{
	char s[100];
	scanf("%s",s);
	int h, m;
	h=(s[0]-'0')*10+(s[1]-'0');
	m=(s[3]-'0')*10+(s[4]-'0');
	if (0<=h && h<12 || h==12 && m==0) printf("Only %s.  Too early to Dang.\n",s);
	else
	{
		h=h-12;
		if (m>0) h=h+1;
		for (int i=1;i<=h;i++) printf("Dang");
		printf("\n");
	}
	return 0;
}