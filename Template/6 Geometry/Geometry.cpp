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
	}
};
typedef Point Vec;
typedef vector<Point> Points;
typedef vector<Point> Poly;
double AngleOnEarth(Point A,Point B)
{
	double x1=PI*A.x/180.0;
	double y1=PI*A.y/180.0;
	double x2=PI*B.x/180.0;
	double y2=PI*B.y/180.0;
	return acos( cos(x1-x2)*cos(y1)*cos(y2)+sin(y1)*sin(y2) );
}

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

//旋转卡壳
//t为卡壳上顶点，l,r分别为左右顶点
//D为最大直径，S为外接矩形的最小面积，C为最小周长
void RotatingCalipers(Points &P,double &D, double &S, double &C)
{
	P=ConvexHull(P);
	int n=P.size();
	S=C=1e15,D=0;
	int t=1,l=1,r=1;
	for (int i=0;i<n;i++)
	{
		while (dcmp( (P[(i+1)%n]-P[i]) * (P[(t+1)%n]-P[t]) ) > 0) t=(t+1)%n;
		while (dcmp( (P[(i+1)%n]-P[i]) ^ (P[(r+1)%n]-P[r]) ) > 0) r=(r+1)%n;
		if (i==0) l=t;
		while (dcmp( (P[(i+1)%n]-P[i]) ^ (P[(l+1)%n]-P[l]) ) < 0) l=(l+1)%n;
		double h=(P[(i+1)%n]-P[i]) * (P[t]-P[i]) / Len(P[(i+1)%n]-P[i]);
		double w=(P[(i+1)%n]-P[i]) ^ (P[r]-P[l]) / Len(P[(i+1)%n]-P[i]);
		D=max(D,h);
		S=min(S,w*h);
		C=min(C,(w+h)*2);
	}
}

//多边形有向面积
double PolygonArea(Poly P)
{
	double area=0;
	int n=P.size();
	for (int i=1;i<n-1;i++)
		area+=(P[i]-P[0])*(P[i+1]-P[0]);
	return area/2;
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

//点到线段距离
double DistanceToSeg(Point P, Point A, Point B)
{
	if (A==B) return Len(P-A);
	Vec u=B-A, v=P-A, w=P-B;
	if (dcmp(u^v)<0) return Len(v);
	else if (dcmp(u^w)>0) return Len(w);
	else return fabs((u*v)/Len(u));
}

//点在直线上投影
Point GetProjection(Point P, Line l)
{
	Point A=l.P, B=l.P+l.v;
	Vec v=B-A;
	return A+v*((v^(P-A))/(v^v));
}

//判断是否规范相交
bool ProIntersection(Point A1, Point A2, Point B1, Point B2)
{
	double c1=(A2-A1)*(B1-A1);
	double c2=(A2-A1)*(B2-A1);
	double c3=(B2-B1)*(A1-B1);
	double c4=(B2-B1)*(A2-B1);
	return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

//判断点在线段上
bool OnSegment(Point P,Point A1,Point A2)
{
	return dcmp((A1-P)*(A2-P))==0 && dcmp((A1-P)^(A2-P))<0;
}

//点与多边形的位置关系
int InPolygon(Point P,const Poly &Poly)
{
	int cnt=0, n=Poly.size();
	for (int i=0;i<n;i++)
	{
		if (OnSegment(P,Poly[i], Poly[(i+1)%n])) return -1;
		int k=dcmp((Poly[(i+1)%n]-Poly[i])*(P-Poly[i]));
		int d1=dcmp(Poly[i].y-P.y);
		int d2=dcmp(Poly[(i+1)%n].y-P.y);
		if (k>0 && d1<=0 && d2>0) cnt++;
		if (k<0 && d2<=0 && d1>0) cnt--;
	}
	if (cnt!=0)  return 1;
	else return 0;
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

//圆和直线交点(方程法)
Points GetIntersection(Line L, Circle C, double &t1, double &t2)
{
	Points Sol; Sol.clear();
	double a=L.v.x, b=L.P.x-C.O.x, c=L.v.y, d=L.P.y-C.O.y;
	double e=a*a+c*c, f= 2*(a*b+c*d), g=b*b-C.r*C.r;
	double delta=f*f-4*e*g;
	if (dcmp(delta)<0) return Sol;
	if (dcmp(delta)==0)
	{
		t1=t2=-f/(2*e);
		Sol.push_back(L.point(t1));
	}
	else//相交
	{
		t1=(-f-sqrt(delta))/(2*e);
		Sol.push_back(L.point(t1));
		t2=(-f+sqrt(delta))/(2*e);
		Sol.push_back(L.point(t2));
	}
	return Sol;
}

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

//圆与圆的交点
Points GetIntersection(Circle C, Circle D)
{
	Vec v=D.O-C.O;
	Points Sol; Sol.clear();
	double d=Len(v);
	if (dcmp(C.r-D.r)>0) swap(C,D);
	if (dcmp(d)==0 || dcmp(C.r+D.r-d) <0 || dcmp(D.r-C.r-d) >0) return Sol;//同心 | 外离 | 内含
	if (dcmp(C.r+D.r-d)==0 || dcmp(D.r-C.r-d)==0)//相切
		Sol.push_back(C.O+Orient(v)*C.r);
	else//相交
	{
		double rad=Ang(v);
		double th=acos((C.r*C.r+d*d-D.r*D.r)/(2*C.r*d));
		Point P=C.point(rad+th);
		Point Q=C.point(rad-th);
		Sol.push_back(P);
		Sol.push_back(Q);
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
		Sol.push_back(Line(P,Rotate(v,rad)));
		Sol.push_back(Line(P,Rotate(v,-rad)));
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