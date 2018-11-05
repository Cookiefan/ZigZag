//=======计算几何=======
#include <bits/stdc++.h>
using namespace std;
const double EPS=1e-10;
const double PI=acos(-1.0);

int dcmp(double x){ if (fabs(x)<EPS) return 0; else return x>0 ?1 :-1;}

//=======点与向量=======

struct Pot
{
	double x, y;
	Pot(){}
	Pot(double xx, double yy):x(xx), y(yy){}
	friend bool operator <(Pot A, Pot B)
	{
		return A.x<B.x || (A.x==B.x && A.y<B.y);
	}
	friend bool operator ==(Pot A, Pot B)
	{
		return dcmp(A.x-B.x)==0 && dcmp(A.y-B.y)==0;
	}
};
typedef Pot Vec;
typedef vector<Pot> Pots;
typedef vector<Pot> Poly;
double AngleOnEarth(Pot A,Pot B)
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
Vec operator -(Pot A, Pot B){ return Vec(A.x-B.x, A.y-B.y);}

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
double Area2(Pot A, Pot B, Pot C) { return (B-A)*(C-A);}

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
Poly ConvexHull(Pots P)
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
void RotatingCalipers(Pots &P,double &D, double &S, double &C)
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
	Pot P;
	Vec v;
	double ang;
	Line(){}
	Line(Pot pp, Vec vv):P(pp), v(Orient(vv)), ang(Ang(vv)){}
	friend bool operator <(Line a, Line b)
	{
		return a.ang<b.ang;
	}
	Pot pot(double k)
	{
		return P+v*k;
	}
};

typedef vector<Line> Lines;

//直线交点(确保唯一)
Pot GetIntsec(Line a, Line b)
{
	Pot P=a.P, Q=b.P;
	Vec v=a.v, w=b.v;
	Vec u=P-Q;
	double t=(w*u)/(v*w);
	return a.pot(t);
}

//点到直线距离
double DistanceToLine(Pot P, Line l)
{
	Pot A=l.P, B=l.P+l.v;
	Vec u=B-A, v=P-A;
	//不取绝对值得到有向距离
	return fabs((u*v)/Len(u));
}

//点到线段距离
double DistanceToSeg(Pot P, Pot A, Pot B)
{
	if (A==B) return Len(P-A);
	Vec u=B-A, v=P-A, w=P-B;
	if (dcmp(u^v)<0) return Len(v);
	else if (dcmp(u^w)>0) return Len(w);
	else return fabs((u*v)/Len(u));
}

//点在直线上投影
Pot GetProj(Pot P, Line l)
{
	Pot A=l.P, B=l.P+l.v;
	Vec v=B-A;
	return A+v*((v^(P-A))/(v^v));
}

//判断是否规范相交
bool ProIntsec(Pot A1, Pot A2, Pot B1, Pot B2)
{
	double c1=(A2-A1)*(B1-A1);
	double c2=(A2-A1)*(B2-A1);
	double c3=(B2-B1)*(A1-B1);
	double c4=(B2-B1)*(A2-B1);
	return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

//判断点在线段上
bool OnSegment(Pot P,Pot A1,Pot A2)
{
	return dcmp((A1-P)*(A2-P))==0 && dcmp((A1-P)^(A2-P))<0;
}

//点与多边形的位置关系
int InPolygon(Pot P,const Poly &Poly)
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
bool OnLeft(Pot P,Line l)
{
	return dcmp(l.v*(P-l.P))>=0;
}

Poly HalfIntsec(vector<Line> l)
{
	Poly Sol;
	Sol.clear();
	int n=l.size();
	sort(l.begin(),l.end());
	int first,last;
	Pot *p=new Pot[n];
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
		if (first<last) p[last-1]=GetIntsec(q[last-1], q[last]);
	}
	while (first<last && !OnLeft(p[last-1],q[first])) last--;
	if (last-first<=1) return Sol;
	p[last]=GetIntsec(q[last], q[first]);
	for (int i=first;i<=last;i++) Sol.push_back(p[i]);
	return Sol;
}

//=======圆相关=======

struct Circo
{
	Pot O;
	double r;
	Circo(Pot O,double r):O(O),r(r){}
	Pot pot(double rad)
	{
		return Pot(O.x+r*cos(rad), O.y+r*sin(rad));
	}
};

//圆和直线交点(方程法)
Pots GetIntsec(Line L, Circo C, double &t1, double &t2)
{
	Pots Sol; Sol.clear();
	double a=L.v.x, b=L.P.x-C.O.x, c=L.v.y, d=L.P.y-C.O.y;
	double e=a*a+c*c, f= 2*(a*b+c*d), g=b*b-C.r*C.r;
	double delta=f*f-4*e*g;
	if (dcmp(delta)<0) return Sol;
	if (dcmp(delta)==0)
	{
		t1=t2=-f/(2*e);
		Sol.push_back(L.pot(t1));
	}
	else//相交
	{
		t1=(-f-sqrt(delta))/(2*e);
		Sol.push_back(L.pot(t1));
		t2=(-f+sqrt(delta))/(2*e);
		Sol.push_back(L.pot(t2));
	}
	return Sol;
}

//圆和直线交点(几何法)
Pots GetIntsec(Line L, Circo C)
{
	Pots Sol; Sol.clear();
	double d=DistanceToLine(C.O, L);
	if (dcmp(d-C.r)>0) return Sol;//相离
	Pot ans=GetIntsec(L,Line(C.O,Normal(L.v)));
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
Pots GetIntsec(Circo C, Circo D)
{
	Vec v=D.O-C.O;
	Pots Sol; Sol.clear();
	double d=Len(v);
	if (dcmp(C.r-D.r)>0) swap(C,D);
	if (dcmp(d)==0 || dcmp(C.r+D.r-d) <0 || dcmp(D.r-C.r-d) >0) return Sol;//同心 | 外离 | 内含
	if (dcmp(C.r+D.r-d)==0 || dcmp(D.r-C.r-d)==0)//相切
		Sol.push_back(C.O+Orient(v)*C.r);
	else//相交
	{
		double rad=Ang(v);
		double th=acos((C.r*C.r+d*d-D.r*D.r)/(2*C.r*d));
		Pot P=C.pot(rad+th);
		Pot Q=C.pot(rad-th);
		Sol.push_back(P);
		Sol.push_back(Q);
	}
	return Sol;
}

//过点P到圆C的切线
Lines GetTangents(Pot P,Circo C)
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
Lines GetTangents(Circo C, Circo D)
{
	Pot A,B;
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
		A=C.pot(rad), B=D.pot(rad);
		Sol.push_back(Line(A,B-A));
		//Sol.push_back(Line(A,Normal(C.O-D.O)));
		return Sol;
	}
	double th=acos((C.r-D.r)/sqrt(dd));
	A=C.pot(rad+th), B=D.pot(rad+th);
	Sol.push_back(Line(A,B-A));
	A=C.pot(rad-th), B=D.pot(rad-th);
	Sol.push_back(Line(A,B-A));
	if (dcmp(dd-rsum*rsum)==0)//外切
	{
		A=C.pot(rad), B=D.pot(rad+PI);
		Sol.push_back(Line(A,B-A));
		//Sol.push_back(Line(A,Normal(D.O-C.O)));
	}
	else if (dcmp(dd-rsum*rsum)>0)//相离
	{
		double ro=acos((C.r+D.r)/sqrt(dd));
		A=C.pot(rad+ro), B=D.pot(PI+rad+ro);
		Sol.push_back(Line(A,B-A));
		A=C.pot(rad-ro), B=D.pot(PI+rad-ro);
		Sol.push_back(Line(A,B-A));
	}
	return Sol;
}

 
// 三维几何部分
  
typedef struct Point_3D {
    double x, y, z;
    Point_3D(double xx = 0, double yy = 0, double zz = 0): x(xx), y(yy), z(zz) {}
 
    bool operator == (const Point_3D& A) const {
        return x==A.x && y==A.y && z==A.z;
    }
}Vector_3D;
 
Point_3D read_Point_3D() {
    double x,y,z;
    scanf("%lf%lf%lf",&x,&y,&z);
    return Point_3D(x,y,z);
}
 
Vector_3D operator + (const Vector_3D & A, const Vector_3D & B) {
    return Vector_3D(A.x + B.x, A.y + B.y, A.z + B.z);
}
 
Vector_3D operator - (const Point_3D & A, const Point_3D & B) {
    return Vector_3D(A.x - B.x, A.y - B.y, A.z - B.z);
}
 
Vector_3D operator * (const Vector_3D & A, double p) {
    return Vector_3D(A.x * p, A.y * p, A.z * p);
}
 
Vector_3D operator / (const Vector_3D & A, double p) {
    return Vector_3D(A.x / p, A.y / p, A.z / p);
}
 
double Dot(const Vector_3D & A, const Vector_3D & B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}
 
double Length(const Vector_3D & A) {
    return sqrt(Dot(A, A));
}
 
double Angle(const Vector_3D & A, const Vector_3D & B) {
    return acos(Dot(A, B) / Length(A) / Length(B));
}
 
Vector_3D Cross(const Vector_3D & A, const Vector_3D & B) {
    return Vector_3D(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}
 
double Area2(const Point_3D & A, const Point_3D & B, const Point_3D & C) {
    return Length(Cross(B - A, C - A));
}
 
double Volume6(const Point_3D & A, const Point_3D & B, const Point_3D & C, const Point_3D & D) {
    return Dot(D - A, Cross(B - A, C - A));
}
 
// 四面体的重心
Point_3D Centroid(const Point_3D & A, const Point_3D & B, const Point_3D & C, const Point_3D & D) {
    return (A + B + C + D) / 4.0;
}
 
/************点线面*************/
// 点p到平面p0-n的距离。n必须为单位向量
double DistanceToPlane(const Point_3D & p, const Point_3D & p0, const Vector_3D & n)
{
    return fabs(Dot(p - p0, n)); // 如果不取绝对值，得到的是有向距离
}
 
// 点p在平面p0-n上的投影。n必须为单位向量
Point_3D GetPlaneProjection(const Point_3D & p, const Point_3D & p0, const Vector_3D & n)
{
    return p - n * Dot(p - p0, n);
}
 
//直线p1-p2 与平面p0-n的交点
Point_3D LinePlaneIntersection(Point_3D p1, Point_3D p2, Point_3D p0, Vector_3D n)
{
    Vector_3D v= p2 - p1;
    double t = (Dot(n, p0 - p1) / Dot(n, p2 - p1)); //分母为0，直线与平面平行或在平面上
    return p1 + v * t; //如果是线段 判断t是否在0~1之间
}
 
// 点P到直线AB的距离
double DistanceToLine(const Point_3D & P, const Point_3D & A, const Point_3D & B)
{
    Vector_3D v1 = B - A, v2 = P - A;
    return Length(Cross(v1, v2)) / Length(v1);
}
 
//点到线段的距离
double DistanceToSeg(Point_3D p, Point_3D a, Point_3D b)
{
    if(a == b)
        return Length(p - a);
 
    Vector_3D v1 = b - a, v2 = p - a, v3 = p - b;
 
    if(Dot(v1, v2) + EPS < 0)
        return Length(v2);
    else
        if(Dot(v1, v3) - EPS > 0)
            return Length(v3);
        else
            return Length(Cross(v1, v2)) / Length(v1);
}
 
//求异面直线 p1+s*u与p2+t*v的公垂线对应的s 如果平行|重合，返回false
bool LineDistance3D(Point_3D p1, Vector_3D u, Point_3D p2, Vector_3D v, double & s)
{
    double b = Dot(u, u) * Dot(v, v) - Dot(u, v) * Dot(u, v);
 
    if(abs(b) <= EPS)
        return false;
 
    double a = Dot(u, v) * Dot(v, p1 - p2) - Dot(v, v) * Dot(u, p1 - p2);
    s = a / b;
    return true;
}
 
// p1和p2是否在线段a-b的同侧
bool SameSide(const Point_3D & p1, const Point_3D & p2, const Point_3D & a, const Point_3D & b)
{
    return Dot(Cross(b - a, p1 - a), Cross(b - a, p2 - a)) - EPS >= 0;
}
 
// 点P在三角形P0, P1, P2中
bool PointInTri(const Point_3D & P, const Point_3D & P0, const Point_3D & P1, const Point_3D & P2)
{
    return SameSide(P, P0, P1, P2) && SameSide(P, P1, P0, P2) && SameSide(P, P2, P0, P1);
}
 
// 三角形P0P1P2是否和线段AB相交
bool TriSegIntersection(const Point_3D & P0, const Point_3D & P1, const Point_3D & P2, const Point_3D & A, const Point_3D & B, Point_3D & P)
{
    Vector_3D n = Cross(P1 - P0, P2 - P0);
 
    if(abs(Dot(n, B - A)) <= EPS)
        return false;    // 线段A-B和平面P0P1P2平行或共面
    else   // 平面A和直线P1-P2有惟一交点
    {
        double t = Dot(n, P0 - A) / Dot(n, B - A);
 
        if(t + EPS < 0 || t - 1 - EPS > 0)
        {
            return false;    // 不在线段AB上
        }
 
        P = A + (B - A) * t; // 交点
        return PointInTri(P, P0, P1, P2);
    }
}
 
//空间两三角形是否相交
bool TriTriIntersection(Point_3D * T1, Point_3D * T2)
{
    Point_3D P;
 
    for(int i = 0; i < 3; i++){
        if(TriSegIntersection(T1[0], T1[1], T1[2], T2[i], T2[(i + 1) % 3], P))
            return true;
 
        if(TriSegIntersection(T2[0], T2[1], T2[2], T1[i], T1[(i + 1) % 3], P))
            return true;
    }
 
    return false;
}
 
//空间两直线上最近点对 返回最近距离 点对保存在ans1 ans2中
double SegSegDistance(Point_3D a1, Point_3D b1, Point_3D a2, Point_3D b2, Point_3D& ans1, Point_3D& ans2)
{
    Vector_3D v1 = (a1 - b1), v2 = (a2 - b2);
    Vector_3D N = Cross(v1, v2);
    Vector_3D ab = (a1 - a2);
    double ans = Dot(N, ab) / Length(N);
    Point_3D p1 = a1, p2 = a2;
    Vector_3D d1 = b1 - a1, d2 = b2 - a2;
    double t1, t2;
    t1 = Dot((Cross(p2 - p1, d2)), Cross(d1, d2));
    t2 = Dot((Cross(p2 - p1, d1)), Cross(d1, d2));
    double dd = Length((Cross(d1, d2)));
    t1 /= dd * dd;
    t2 /= dd * dd;
    ans1 = (a1 + (b1 - a1) * t1);
    ans2 = (a2 + (b2 - a2) * t2);
    return fabs(ans);
}
 
// 判断P是否在三角形A, B, C中，并且到三条边的距离都至少为mindist。保证P, A, B, C共面
bool InsideWithMinDistance(const Point_3D & P, const Point_3D & A, const Point_3D & B, const Point_3D & C, double mindist)
{
    if(!PointInTri(P, A, B, C))
        return false;
 
    if(DistanceToLine(P, A, B) < mindist)
        return false;
 
    if(DistanceToLine(P, B, C) < mindist)
        return false;
 
    if(DistanceToLine(P, C, A) < mindist)
        return false;
 
    return true;
}
 
// 判断P是否在凸四边形ABCD（顺时针或逆时针）中，并且到四条边的距离都至少为mindist。保证P, A, B, C, D共面
bool InsideWithMinDistance(const Point_3D & P, const Point_3D & A, const Point_3D & B, const Point_3D & C, const Point_3D & D, double mindist)
{
    if(!PointInTri(P, A, B, C))
        return false;
 
    if(!PointInTri(P, C, D, A))
        return false;
 
    if(DistanceToLine(P, A, B) < mindist)
        return false;
 
    if(DistanceToLine(P, B, C) < mindist)
        return false;
 
    if(DistanceToLine(P, C, D) < mindist)
        return false;
 
    if(DistanceToLine(P, D, A) < mindist)
        return false;
 
    return true;
}
 
 
/*************凸包相关问题*******************/
//加干扰
double rand01()
{
    return rand() / (double)RAND_MAX;
}
double randeps()
{
    return (rand01() - 0.5) * EPS;
}
Point_3D add_noise(const Point_3D & p)
{
    return Point_3D(p.x + randeps(), p.y + randeps(), p.z + randeps());
}
 
struct Face
{
    int v[3];
    Face(int a, int b, int c)
    {
        v[0] = a;
        v[1] = b;
        v[2] = c;
    }
    Vector_3D Normal(const vector<Point_3D> & P) const
    {
        return Cross(P[v[1]] - P[v[0]], P[v[2]] - P[v[0]]);
    }
    // f是否能看见P[i]
    int CanSee(const vector<Point_3D> & P, int i) const
    {
        return Dot(P[i] - P[v[0]], Normal(P)) > 0;
    }
};
 
// 增量法求三维凸包
// 注意：没有考虑各种特殊情况（如四点共面）。实践中，请在调用前对输入点进行微小扰动
vector<Face> CH3D(const vector<Point_3D> & P)
{
    int n = P.size();
    vector<vector<int> > vis(n);
 
    for(int i = 0; i < n; i++)
    {
        vis[i].resize(n);
    }
 
    vector<Face> cur;
    cur.push_back(Face(0, 1, 2)); // 由于已经进行扰动，前三个点不共线
    cur.push_back(Face(2, 1, 0));
 
    for(int i = 3; i < n; i++)
    {
        vector<Face> next;
 
        // 计算每条边的“左面”的可见性
        for(int j = 0; j < cur.size(); j++)
        {
            Face & f = cur[j];
            int res = f.CanSee(P, i);
 
            if(!res)
                next.push_back(f);
 
            for(int k = 0; k < 3; k++)
                vis[f.v[k]][f.v[(k + 1) % 3]] = res;
        }
 
        for(int j = 0; j < cur.size(); j++)
            for(int k = 0; k < 3; k++)
            {
                int a = cur[j].v[k], b = cur[j].v[(k + 1) % 3];
 
                if(vis[a][b] != vis[b][a] && vis[a][b]) // (a,b)是分界线，左边对P[i]可见
                    next.push_back(Face(a, b, i));
            }
 
        cur = next;
    }
 
    return cur;
}
 
struct ConvexPolyhedron
{
    int n;
    vector<Point_3D> P, P2;
    vector<Face> faces;
 
    bool read()
    {
        if(scanf("%d", &n) != 1)
            return false;
 
        P.resize(n);
        P2.resize(n);
 
        for(int i = 0; i < n; i++)
        {
            P[i] = read_Point_3D();
            P2[i] = add_noise(P[i]);
        }
 
        faces = CH3D(P2);
        return true;
    }
 
    //三维凸包重心
    Point_3D centroid()
    {
        Point_3D C = P[0];
        double totv = 0;
        Point_3D tot(0, 0, 0);
 
        for(int i = 0; i < faces.size(); i++)
        {
            Point_3D p1 = P[faces[i].v[0]], p2 = P[faces[i].v[1]], p3 = P[faces[i].v[2]];
            double v = -Volume6(p1, p2, p3, C);
            totv += v;
            tot = tot + Centroid(p1, p2, p3, C) * v;
        }
 
        return tot / totv;
    }
    //凸包重心到表面最近距离
    double mindist(Point_3D C)
    {
        double ans = 1e30;
 
        for(int i = 0; i < faces.size(); i++)
        {
            Point_3D p1 = P[faces[i].v[0]], p2 = P[faces[i].v[1]], p3 = P[faces[i].v[2]];
            ans = min(ans, fabs(-Volume6(p1, p2, p3, C) / Area2(p1, p2, p3)));
        }
 
        return ans;
    }
};