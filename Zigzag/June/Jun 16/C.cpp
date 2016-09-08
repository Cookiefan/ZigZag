#include <bits/stdc++.h>
#define maxn 1200
const double EPS=1e-8;
const double PI=acos(-1.0);
const double inf=999999999;
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
	}
	friend bool operator ==(Point A, Point B)
	{
		return dcmp(A.x-B.x)==0 && dcmp(A.y-B.y)==0;
	};
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

Point GetIntersection(Line a, Line b)
{
	Point P=a.P, Q=b.P;
	Vec v=a.v, w=b.v;
	Vec u=P-Q;
	double t=(w*u)/(v*w);
	return a.point(t);
}

bool ProIntersection(Point A1, Point A2, Point B1, Point B2)
{
	double c1=(A2-A1)*(B1-A1);
	double c2=(A2-A1)*(B2-A1);
	double c3=(B2-B1)*(A1-B1);
	double c4=(B2-B1)*(A2-B1);
	return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

typedef vector<Line> Lines;
int n, w, h;
Poly p, rect;
Lines edge;
Point lp[maxn], rp[maxn];
double r[maxn], ll[maxn], rr[maxn], f[maxn][2], g[maxn][2];

int main()
{
	int x,y;
	while (scanf("%d%d%d",&n, &w, &h)!=EOF)
	{	
		p.clear();
		rect.clear();
		edge.clear();
		rect.push_back(Point(0,0));
		rect.push_back(Point(w,0));
		rect.push_back(Point(w,h));
		rect.push_back(Point(0,h));
		for (int i=0;i<4;i++) edge.push_back(Line(rect[i], rect[(i+1)%4]-rect[i]));
		for (int i=0;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			p.push_back(Point(x,y));
		}
		double ans=0;
		for (int i=0;i<n;i++) ans+=Len(p[i]-p[(i-1+n)%n]);
		for (int i=0;i<n;i++)
		{
			Line l=Line(p[i], p[i]-p[(i+1)%n]);
			if (dcmp(l.v.x)>0)
			{
				Point t=GetIntersection(l, edge[1]);
				if (dcmp(t.y)>=0 && dcmp(h-t.y)>=0)
					lp[i]=t;
			}
			else if (dcmp(l.v.x<0))
			{
				Point t=GetIntersection(l, edge[3]);
				if (dcmp(t.y)>=0 && dcmp(h-t.y)>=0)
					lp[i]=t;
			}
			if (dcmp(l.v.y)>0)
			{
				Point t=GetIntersection(l, edge[2]);
				if (dcmp(t.x)>=0 && dcmp(w-t.x)>=0)
					lp[i]=t;
			}
			else if (dcmp(l.v.y<0))
			{
				Point t=GetIntersection(l, edge[0]);
				if (dcmp(t.x)>=0 && dcmp(w-t.x)>=0)
					lp[i]=t;
			}
			//cout<<lp[i].x<<","<<lp[i].y<<' ';
		}
		//cout<<endl;
		for (int i=0;i<n;i++)
		{
			Line l=Line(p[i], p[i]-p[(i-1+n)%n]);
			if (dcmp(l.v.x)>0)
			{
				Point t=GetIntersection(l, edge[1]);
				if (dcmp(t.y)>=0 && dcmp(h-t.y)>=0)
					rp[i]=t;
			}
			else if (dcmp(l.v.x<0))
			{
				Point t=GetIntersection(l, edge[3]);
				if (dcmp(t.y)>=0 && dcmp(h-t.y)>=0)
					rp[i]=t;
			}
			if (dcmp(l.v.y)>0)
			{
				Point t=GetIntersection(l, edge[2]);
				if (dcmp(t.x)>=0 && dcmp(w-t.x)>=0)
					rp[i]=t;
			}
			else if (dcmp(l.v.y<0))
			{
				Point t=GetIntersection(l, edge[0]);
				if (dcmp(t.x)>=0 && dcmp(w-t.x)>=0)
					rp[i]=t;
			}
			//cout<<rp[i].x<<","<<rp[i].y<<' ';
		}
		//cout<<endl;
		for (int i=0;i<n;i++)
		{
			ll[i]=Len(p[i]-lp[i]);
			rr[i]=Len(p[i]-rp[i]);
			 
			int j=(i-1)%n;
			if (ProIntersection(p[i],lp[i],p[j],rp[j]))
			{
				Line l1=Line(p[i], p[i]-p[(i+1)%n]);
				Line l2=Line(p[j], p[j]-p[(j-1+n)%n]);
				Point t=GetIntersection(l1, l2);
				r[i]=max(Len(t-lp[i]), Len(t-rp[j]));
			}
			else
				r[i]=0;
			//cout<<ll[i]<<' '<<rr[i]<<' '<<r[i]<<endl;
		}
		double tmp=inf;
		for (int k=0;k<n;k++)
		{
			f[k][0]=inf;
			f[k][1]=rr[k]+ll[(k-1+n)%n];
			for (int i=k+1;i<=k+n-2;i++)
			{
				f[i%n][0]=min(f[(i-1)%n][0], f[(i-1)%n][1]-r[i%n])+ll[i%n];
				f[i%n][1]=min(f[(i-1)%n][0], f[(i-1)%n][1])+rr[i%n];
			}
			f[(k+n-2)%n][1]-=r[(k-1)%n];
			tmp=min(tmp, min(f[(k+n-2)%n][0], f[(k+n-2)%n][1]));
		}
		ans+=tmp;
		printf("%.6f\n",ans);
	}
	return 0;
}