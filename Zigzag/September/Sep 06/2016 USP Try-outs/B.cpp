#include <bits/stdc++.h>
#define maxn 66
using namespace std;

LL f[maxn][maxn][maxn][2];

LL dp(int p1, int p2, int p3, int p4, int flag){
	if (p1+p2+p3+p4) return flag;
	LL *tmp=&f[p1][p2][p3][p4][flag];
	if (tmp!=-1) return tmp;
	tmp=0;
	for (int i=1;i<=p1;i++) tmp+=dp(p1-i, p2)
	for (int i=1;i<=p2;i++) 
	for (int i=1;i<=p3;i++) 


}

int main()
{
	return 0;
}