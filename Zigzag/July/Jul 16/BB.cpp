#include <bits/stdc++.h>
using namespace std;

//=======计算几何=======
const double EPS=1e-10;
const double PI=acos(-1.0);

int dcmp(double x){ if (fabs(x)<EPS) return 0; else return x>0 ?1 :-1;}

//=======点与向量=======

struct Point
{
	double x, y;
	Point(){}
	Point(double xx, double yy):x(xx), y(yy){}
	friend bool operator <(Point A, Point B)
	{
		return A.x<B.x || (A.x==B.x && A.y<B.y);
	}
	friend bool operator ==(Point A, Point B)
	{
		return dcmp(A.x-B.x)==0 && dcmp(A.y-B.y)==0;
	};
};
typedef Point Vec;
typedef vector<Point> Points;
typedef vector<Point> Poly;

//向量加法
Vec operator +(Vec a, Vec b){ return Vec(a.x+b.x, a.y+b.y);}

//向量减法
Vec operator -(Point A, Point B){ return Vec(A.x-B.x, A.y-B.y);}

//向量数乘
Vec operator *(Vec a, double k){ return Vec(a.x*k, a.y*k);}

//向量数除
Vec operator /(Vec a, double k){ return Vec(a.x/k, a.y/k);}

//向量点积
double operator ^(Vec a, Vec b){ return a.x*b.x+a.y*b.y;}

//向量叉积
double operator *(Vec a, Vec b){ return a.x*b.y-a.y*b.x;}

//向量长度
double Len(Vec a) { return sqrt(a^a);}

//向量极角
double Ang(Vec a) { return atan2(a.y, a.x);}

//向量与向量夹角
double Ang(Vec a, Vec b) { return acos((a^b)/(Len(a)*Len(b)));}

//三角形有向面积的两倍
double Area2(Point A, Point B, Point C) { return (B-A)*(C-A);}

//向量逆时针旋转rad度
Vec Rotate(Vec a, double rad)
{
	return Vec(a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad));
}

//向量的单位方向向量
Vec Orient(Vec a)
{
	double l=Len(a);
	return a/l;
}

//向量的单位法向量
Vec Normal(Vec a)
{
	double l=Len(a);
	return Vec(-a.y/l, a.x/l);
}

//凸包
Poly ConvexHull(Points P)
{
	sort(P.begin(),P.end());
	P.erase(unique(P.begin(),P.end()),P.end());
	int n=P.size();
	Poly St(n+1);
	int m=0;
	for (int i=0;i<n;i++)
	{
		while (m>1 && dcmp((St[m-1]-St[m-2])*(P[i]-St[m-2])) <=0)
			m--;
		St[m++]=P[i];
	}
	int k=m;
	for (int i=n-2;i>=0;i--)
	{
		while (m>k && dcmp((St[m-1]-St[m-2])*(P[i]-St[m-2])) <=0)
			m--;
		St[m++]=P[i];
	}
	if (n>1) St.resize(--m);
	return St;
}

//多边形周长
double PolygonPerimeter(Poly P)
{
	double len=0;
	int n=P.size();
	for (int i=0;i<n-1;i++)
		len+=Len(P[i+1]-P[i]);
	return len+Len(P[0]-P[n-1]);
}

//=======直线与线段=======

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
	}
	Point point(double k)
	{
		return P+v*k;
	}
};

typedef vector<Line> Lines;


//直线交点(确保唯一)
Point GetIntersection(Line a, Line b)
{
	Point P=a.P, Q=b.P;
	Vec v=a.v, w=b.v;
	Vec u=P-Q;
	double t=(w*u)/(v*w);
	return a.point(t);
}

//点到直线距离
double DistanceToLine(Point P, Line l)
{
	Point A=l.P, B=l.P+l.v;
	Vec u=B-A, v=P-A;
	//不取绝对值得到有向距离
	return fabs((u*v)/Len(u));
}


//=======圆相关=======

struct Circle
{
	Point O;
	double r;
	Circle(Point O,double r):O(O),r(r){}
	Point point(double rad)
	{
		return Point(O.x+r*cos(rad), O.y+r*sin(rad));
	}
};

//圆和直线交点(几何法)
Points GetIntersection(Line L, Circle C)
{
	Points Sol; Sol.clear();
	double d=DistanceToLine(C.O, L);
	if (dcmp(d-C.r)>0) return Sol;//相离
	Point ans=GetIntersection(L,Line(C.O,Normal(L.v)));
	if (dcmp(d-C.r)==0)
		Sol.push_back(ans);
	else
	{
		double len=sqrt(C.r*C.r-d*d);
		Vec v=Orient(L.v);
		Sol.push_back(ans+v*len);
		Sol.push_back(ans-v*len);
	}
	return Sol;
}

//过点P到圆C的切线
Lines GetTangents(Point P,Circle C)
{
	Vec v=C.O-P,tmp;
	Lines Sol; Sol.clear();
	double d=Len(v);
	if (d<C.r) return Sol;
	if (dcmp(d-C.r)==0)
		Sol.push_back(Line(P,Normal(v)));
	else
	{
		double rad=asin(C.r/d);
		double l=C.r*C.r/d;
		double h=sqrt(C.r*C.r-l*l);
		Sol.push_back(Line(P, C.O+Orient(P-C.O)*l+Orient(Rotate(P-C.O,PI*0.5))*h));
		Sol.push_back(Line(P, C.O+Orient(P-C.O)*l+Orient(Rotate(P-C.O,-PI*0.5))*h));
	}
	return Sol;
}

//两圆公切线
Lines GetTangents(Circle C, Circle D)
{
	Point A,B;
	Lines Sol; Sol.clear();
	if (dcmp(C.r-D.r)<0) swap(C, D);
	double dd=(C.O.x-D.O.x)*(C.O.x-D.O.x)+(C.O.y-D.O.y)*(C.O.y-D.O.y);
	double rdif=C.r-D.r;
	double rsum=C.r+D.r;
	if (dcmp(dd-rdif*rdif)<0) return Sol;//内含
	if (dcmp(dd)==0 && dcmp(C.r-D.r)==0) return Sol;//重合
	double rad=atan2(D.O.y-C.O.y,D.O.x-C.O.x);
	if (dcmp(dd-rdif*rdif)==0)//内切
	{
		A=C.point(rad), B=D.point(rad);
		Sol.push_back(Line(A,B-A));
		//Sol.push_back(Line(A,Normal(C.O-D.O)));
		return Sol;
	}
	double th=acos((C.r-D.r)/sqrt(dd));
	A=C.point(rad+th), B=D.point(rad+th);
	Sol.push_back(Line(A,B-A));
	A=C.point(rad-th), B=D.point(rad-th);
	Sol.push_back(Line(A,B-A));
	if (dcmp(dd-rsum*rsum)==0)//外切
	{
		A=C.point(rad), B=D.point(rad+PI);
		Sol.push_back(Line(A,B-A));
		//Sol.push_back(Line(A,Normal(D.O-C.O)));
	}
	else if (dcmp(dd-rsum*rsum)>0)//相离
	{
		double ro=acos((C.r+D.r)/sqrt(dd));
		A=C.point(rad+ro), B=D.point(PI+rad+ro);
		Sol.push_back(Line(A,B-A));
		A=C.point(rad-ro), B=D.point(PI+rad-ro);
		Sol.push_back(Line(A,B-A));
	}
	return Sol;
}

Points PCins(Point P, Circle C)
{
	double a=C.r, c=Len(C.O-P), b=sqrt(c*c-a*a);
	double h=a*b/c;
	double y=sqrt(a*a-h*h), x=c-y;
	Vec u=Orient(C.O-P)*x;
	Vec v=Orient(Rotate(C.O-P, PI*0.5))*h;
	Points Sol; Sol.clear();
	Sol.push_back(P+u+v);
	Sol.push_back(P+u-v);
	// double l=Len(C.O-P), t=sqrt(l*l-C.r*C.r);
	// Vec u=Orient(Rotate(C.O-P, asin(C.r/l)))*t;
	// Vec v=Orient(Rotate(C.O-P, -asin(C.r/l)))*t;
	// Points Sol; Sol.clear();
	// Sol.push_back(P+u);
	// Sol.push_back(P+v);
	return Sol;
}

bool onCircle(Point a, Point b, Circle c)
{
	return !dcmp(Len(a-c.O)-c.r) && !dcmp(Len(b-c.O)-c.r);
}
vector<Point> tri,p;
vector<Circle> cir;

int n,m;

int main()
{
	int x,y,z;
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		for (int i=0;i<n;i++) 
		{
			scanf("%d%d%d",&x,&y,&z);
			cir.push_back(Circle(Point(x,y), z));
		}
		for (int i=0;i<m;i++)
			for (int k=0;k<3;k++)
			{
				scanf("%d%d",&x,&y);
				tri.push_back(Point(x,y));
				p.push_back(Point(x,y));
			}
		m=m*3;
		for (int i=0;i<n;i++)
			for (int j=i+1;j<n;j++)
			{
				Lines tmp=GetTangents(cir[i], cir[j]);
				int ss=tmp.size();
				for (int k=0;k<ss;k++)
				{
					Points b=GetIntersection(tmp[k], cir[i]);
					int bb=b.size();
					for (int e=0;e<bb;e++) p.push_back(b[e]);

					b=GetIntersection(tmp[k], cir[j]);
					bb=b.size();
					for (int e=0;e<bb;e++) p.push_back(b[e]);
				}
			}

		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
			{
				Points tmp=PCins(tri[j], cir[i]);
				p.push_back(tmp[0]);
				p.push_back(tmp[1]);
				//cout<<tmp[0].x<<' '<<tmp[0].y<<endl;;
				//cout<<tmp[1].x<<' '<<tmp[1].y<<endl;
				//Lines tmp=GetTangents(tri[j], cir[i]);
				// int ss=tmp.size();
				// for (int k=0;k<ss;k++)
				// {
					//Points b=GetIntersection(tmp[k], cir[i]);
					//int bb=b.size();
					//cout<<b[0].x<<' '<<b[0].y<<endl;
					// cout<<onCircle(b[0], b[0], cir[i])<<endl;
					//for (int e=0;e<bb;e++) p.push_back(b[e]);
				//}
			}
		Poly q=ConvexHull(p);
		//for (int i=0;i<q.size();i++) cout<<q[i].x<<' '<<q[i].y<<endl;
		double ans=PolygonPerimeter(q);
		//cout<<ans<<endl;
		int num=q.size();
		for (int i=0;i<n;i++)
			for (int j=0;j<num-1;j++)
			{
				if (onCircle(q[j], q[j+1], cir[i]))
				{
					double th=Ang(q[j]-cir[i].O, q[j+1]-cir[i].O);
					//cout<<th<<endl;
					double ls=cir[i].r*th;
					double lt=Len(q[j+1]-q[j]);
					//cout<<ls<<' '<<lt<<endl;
					ans=ans-lt+ls;
				}
			}
		printf("%.6f\n",ans);
	}
	return 0;
}
