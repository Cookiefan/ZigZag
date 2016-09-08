#include <bits/stdc++.h>
#define sqr(p) p*p
using namespace std;

const double eps=1e-7;

struct Point
{
	double x, y, z;
	Point(){}
	Point(int x, int y, int z): x(x),y(y),z(z){}
}

struct Plane
{
	Point A, B, C;
	Plane(Point A, Point B, Point C):A(A), B(B), C(C){}
}

double operator -(Point A, Point B)
{
	return Point(A.x-B.x, A.y-B.y, A.z-B.z);
}

double operator *(Point A, Point B)
{
	return Point(A.y*B.z-A.z*B.y, A.x*B.y-A.y*B.x, A.x*B.y-A.y*B.x);
}

double length(Point A)
{
	return sqrt(sqr(A.x)+sqr(A.y)+sqr(A.z));
}


Point A, B, C, D;
vector<Plane>Plane p[4];

int main()
{
	int x,y,z;
	while (scanf("%d%d%d%d%d%d%d%d%d%d%d%d",&A.x, &A.y, &A.z, &B.x, &B.y, &B.z, &C.x, &C.y, &C.z, &D.x, &D.y, &D.z)!=EOF)
	{

	}
	return 0;

}