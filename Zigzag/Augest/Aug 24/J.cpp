#include <bits/stdc++.h>
using namespace std;

struct point
{
	int x, y;
	point(){}
	point(int x, int y):x(x), y(y){}
};
bool operator <(point a, point b)
{
	return a.x==b.x?a.y<b.y:a.x<b.x;
}
point operator +(point a, point b)
{
	return point(a.x+b.x, a.y+b.y);
}
point operator -(point a, point b)
{
	return point(a.x-b.x, a.y-b.y);
}
vector<point> p;

int gcd(int a,int b)
{
    return b==0?a:gcd(b, a%b);
}

int main()
{
	for (int i=0;i<50;i++)
		for (int j=0;j<50;j++)
			p.push_back(point(i,j));
	int ans=0;
	int tmp=0;
	for (auto a:p)
		for (auto b:p)
			if (a<b)
			{
				point v=b-a, c=a-v, d=b+v;
				if (c.x>=0 && c.y>=0) continue;
				if (d.x<50 && d.y<50) continue;
				ans++;
				if (gcd(abs(a.x-b.x), abs(a.y-b.y))>1) tmp++;
			}
	

				
	cout<<ans-tmp;

	return 0;
}