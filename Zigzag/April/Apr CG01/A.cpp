#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const double EPS=1e-10;

int dcmp(double x){ if (fabs(x)<EPS) return 0; else return x>0 ?1 :-1;}

struct Point
{
	double x, y;
	Point(){}
	Point(double xx, double yy):x(xx), y(yy){}
};
typedef Point Vec;
typedef vector<Point> Points;

Vec operator +(Vec a, Vec b){ return Vec(a.x+b.x, a.y+b.y); }
Vec operator -(Vec a, Vec b){ return Vec(a.x-b.x, a.y-b.y); }
double operator *(Vec a, Vec b){ return a.x*b.y-a.y*b.x; }

int n,m;
Points s,u,l;
int sum[12000];

int main()
{
	double ux, uy, lx, ly, xa, xb, x, y;
	bool first=1;
	while (scanf("%d",&m) && m)
	{
		if (first) first=0;
		else printf("\n");
		scanf("%d%lf%lf%lf%lf",&n,&ux,&uy,&lx,&ly);
		u.clear();
		l.clear();
		s.clear();
		u.push_back(Point(ux, uy));
		l.push_back(Point(ux, ly));
		for (int i=1;i<=m;i++)
		{
			scanf("%lf%lf",&xa,&xb);
			u.push_back(Point(xa, uy));
			l.push_back(Point(xb, ly));
		}
		u.push_back(Point(lx, uy));
		l.push_back(Point(lx, ly));
		for (int i=0;i<n;i++)
		{
			scanf("%lf%lf",&x,&y);
			s.push_back(Point(x,y));
		}
		memset(sum,0,sizeof(sum));
		for (int i=0;i<n;i++)
			for (int j=0;j<=m;j++)
				if (dcmp((u[j]-s[i])*(l[j]-s[i]))==1 && dcmp((u[j+1]-s[i])*(l[j+1]-s[i]))==-1)
					sum[j]++;
		for (int i=0;i<=m;i++)
			printf("%d: %d\n",i, sum[i]);
	}
	return 0;
}