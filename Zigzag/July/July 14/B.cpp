#include <bits.stdc++.h>
#define maxn 1200
using namespace std;

int p[100][100];
string s;

int main()
{
	memset(p,0,sizeof(p));
	p['A'-'A']['A'-'A']=1;
	p['H'-'A']['H'-'A']=1;
	p['I'-'A']['I'-'A']=1;
	p['M'-'A']['M'-'A']=1;
	p['o'-'A']['o'-'A']=1;
	p['O'-'A']['O'-'A']=1;
	p['b'-'A']['d'-'A']=1;
	p['d'-'A']['b'-'A']=1;
	cin>>s;
	return 0;
}
