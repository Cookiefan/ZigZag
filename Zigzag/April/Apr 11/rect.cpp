#include <bits/stdc++.h>
#define maxn 2020
#define oo 1000000007
using namespace std;
const char a[200][200]={
"..+----+",
"./    /|",
"+----+ |",
"|    | +",
"|    |/.",
"+----+.."};
const int p[7]={1,1,1,2,4,8,16};
char s[1000][1000];

void cube(int x, int y)
{
	for (int i=0;i<6;i++)
	{
		if (i==0)
			for (int j=2;j<8;j++)
				s[x+i][y+j]=a[i][j];
		if (i==1)
			for (int j=1;j<8;j++)
				s[x+i][y+j]=a[i][j];
		if (1<i && i<4)
			for (int j=0;j<8;j++)
				s[x+i][y+j]=a[i][j];
		if (i==4)
			for (int j=0;j<7;j++)
				s[x+i][y+j]=a[i][j];
		if (i==5)
			for (int j=0;j<6;j++)
				s[x+i][y+j]=a[i][j];
	}
}

void draw(int x, int y, int k)
{
	if (k==1)
	{
		cube(x,y);
	}
	else
	{
		draw(x+3*p[k], y+2*p[k], k-1);
		draw(x+3*p[k], y+7*p[k], k-1);
		draw(x+5*p[k], y+0*p[k], k-1);
		draw(x+5*p[k], y+5*p[k], k-1);
		draw(x+0*p[k], y+2*p[k], k-1);
		draw(x+0*p[k], y+7*p[k], k-1);
		draw(x+2*p[k], y+0*p[k], k-1);
		draw(x+2*p[k], y+5*p[k], k-1);
	}
}

int main()
{
	freopen("out.txt","w",stdout);
	draw(0,0,3);
	for (int i=0;i<=50;i++)
	{
		for (int j=0;j<=50;j++)
			printf("%c",s[i][j]);
		cout<<endl;
	}
	return 0;
}