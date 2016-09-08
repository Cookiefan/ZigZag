#include <bits/stdc++.h>
using namespace std;

string s;
int p[4];
char ch[4]={'G','P','L','T'};

int main()
{
	cin>>s;
	int len=s.length();
	memset(p,0,sizeof(p));
	for (int i=0;i<len;i++)
	{
		if (s[i]=='G' || s[i]=='g') p[0]++;
		if (s[i]=='P' || s[i]=='p') p[1]++;
		if (s[i]=='L' || s[i]=='l') p[2]++;
		if (s[i]=='T' || s[i]=='t') p[3]++;
	}
	while (p[0]+p[1]+p[2]+p[3])
	{
		for (int i=0;i<4;i++)
			if (p[i]) printf("%c",ch[i]), p[i]--;
	}
	printf("\n");
	return 0;
}