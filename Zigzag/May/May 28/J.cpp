#include <bits/stdc++.h>
const double EPS=1e-10;
const double PI=acos(-1.0);
using namespace std;

int dcmp(double x){ if (fabs(x)<EPS) return 0; else return x>0 ?1 :-1;}
struct Point
{
	double x, y;
	Point(){}
	Point(double xx, double yy):x(xx), y(yy){}
	friend bool operator <(Point A, Point B)
	{
		return A.x<B.x || (A.x==B.x && A.y<B.y);
	};
	friend bool operator ==(Point A, Point B)
	{
		return dcmp(A.x-B.x)==0 && dcmp(A.y-B.y)==0;
	};
};
typedef Point Vec;
Vec operator +(Vec a, Vec b){ return Vec(a.x+b.x, a.y+b.y);}
Vec operator -(Point A, Point B){ return Vec(A.x-B.x, A.y-B.y);}
Vec operator *(Vec a, double k){ return Vec(a.x*k, a.y*k);}
Vec operator /(Vec a, double k){ return Vec(a.x/k, a.y/k);}
double operator *(Vec a, Vec b){ return a.x*b.y-a.y*b.x;}
double operator ^(Vec a, Vec b){ return a.x*b.x+a.y*b.y;}
double Len(Vec a) { return sqrt(a^a);}

//向量的单位方向向量
Vec Orient(Vec a)
{
	double l=Len(a);
	return a/l;
}
double Ang(Vec a) { return atan2(a.y, a.x);}

typedef vector<Point> Poly;
struct Line
{
	Point P;
	Vec v;
	double ang;
	Line(){}
	Line(Point pp, Vec vv):P(pp), v(Orient(vv)), ang(Ang(vv)){}
	friend bool operator <(Line a, Line b)
	{
		return a.ang<b.ang;
	};
	Point point(double k)
	{
		return P+v*k;
	}
};
typedef vector<Line> Lines;

Point GetIntersection(Line a, Line b)
{
	Point P=a.P, Q=b.P;
	Vec v=a.v, w=b.v;
	Vec u=P-Q;
	double t=(w*u)/(v*w);
	return a.point(t);
}

double PolygonArea(Poly P)
{
	double area=0;
	int n=P.size();
	for (int i=1;i<n-1;i++)
		area+=(P[i]-P[0])*(P[i+1]-P[0]);
	return area/2;
}
//半平面交
bool OnLeft(Point P,Line l)
{
	return dcmp(l.v*(P-l.P))>=0;
}
Poly HalfPlaneIntersection(vector<Line> l)
{
	Poly Sol;
	Sol.clear();
	int n=l.size();
	sort(l.begin(),l.end());
	int first,last;
	Point *p=new Point[n];
	Line *q=new Line[n];
	q[first=last=0]=l[0];
	for (int i=1;i<n;i++)
	{
		while (first<last && !OnLeft(p[last-1],l[i])) last--;
		while (first<last && !OnLeft(p[first],l[i])) first++;
		q[++last]=l[i];
		if (dcmp(q[last].v*q[last-1].v)==0)
		{
			last--;
			if (OnLeft(l[i].P,q[last])) q[last]=l[i];
		}
		if (first<last) p[last-1]=GetIntersection(q[last-1], q[last]);
	}
	while (first<last && !OnLeft(p[last-1],q[first])) last--;
	if (last-first<=1) return Sol;
	p[last]=GetIntersection(q[last], q[first]);
	for (int i=first;i<=last;i++) Sol.push_back(p[i]);
	return Sol;
}

int n,m;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x,y;
		Poly N,M;
		Lines f;
		for (int i=0;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			N.push_back(Point(x,y));
		}
		for (int i=0;i<n;i++) f.push_back(Line(N[i], N[(i+1)%n]-N[i]));
		for (int i=0;i<m;i++)
		{
			scanf("%d%d",&x,&y);
			M.push_back(Point(x,y));
		}
		for (int i=0;i<m;i++) f.push_back(Line(M[i], M[(i+1)%m]-M[i]));
		Poly Q=HalfPlaneIntersection(f);
		printf("%.4f\n", PolygonArea(Q));
	}
	return 0;
}
