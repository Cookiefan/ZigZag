#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#define maxn 120
#define maxm 12000
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

bool ProIntersection(Point A1, Point A2, Point B1, Point B2)
{
	double c1=(A2-A1)*(B1-A1);
	double c2=(A2-A1)*(B2-A1);
	double c3=(B2-B1)*(A1-B1);
	double c4=(B2-B1)*(A2-B1);
	return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

double length(Point A, Point B)
{
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

int tot, n, m, num;
int fir[maxn],inque[maxn];
double dis[maxn];
Points p, s, t;

struct edge
{
	int s,t, next;
	double val;
}e[maxm];

void add_edge(int x, int y, double z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z;
	e[tot].next=fir[x]; fir[x]=tot;
}

double spfa(int st, int ed)
{
	for (int i=st;i<=ed;i++) dis[i]=999999;
	memset(inque,0,sizeof(inque));
	deque<int> que;
	que.clear();
	que.push_back(st);
	inque[st]=1;
	dis[st]=0;
	while (!que.empty())
	{
		int now=que.front();
		que.pop_front();
		inque[now]=0;
		for (int j=fir[now];j;j=e[j].next)
		{
			int tmp=e[j].t;
			if (dcmp(dis[tmp]-dis[now]-e[j].val)==1)
			{
				//cout<<dis[tmp]<<' '<<dis[now]+e[j].val<<endl;
				dis[tmp]=dis[now]+e[j].val;
				if (!inque[tmp])
				{
					que.push_back(tmp);
					inque[tmp]=1;
				}
			}
		}

	}
	return dis[ed];
}

bool judge(Point A, Point B)
{
	for (int i=0;i<m;i++)
		if (ProIntersection(A, B, s[i], t[i]))
			return 0;
	return 1;
}

int main()
{
	double x,y_1,y_2,y_3,y_4;
	while (scanf("%d",&n) && n!=-1)
	{
		memset(fir,0,sizeof(fir));
		p.clear();
		s.clear();
		t.clear();
		tot=0;
		p.push_back(Point(0,5));
		for (int i=1;i<=n;i++)
		{
			scanf("%lf%lf%lf%lf%lf",&x,&y_1,&y_2,&y_3,&y_4);

			p.push_back(Point(x,y_1));
			p.push_back(Point(x,y_2));
			p.push_back(Point(x,y_3));
			p.push_back(Point(x,y_4));

			s.push_back(Point(x, 0));
			t.push_back(Point(x, y_1));

			s.push_back(Point(x, y_2));
			t.push_back(Point(x, y_3));

			s.push_back(Point(x, y_4));
			t.push_back(Point(x, 10));
		}
		p.push_back(Point(10,5));
		num=p.size();

		m=s.size();
		for (int i=0;i<num;i++)
			for (int j=i+1;j<num;j++)
				if (judge(p[i],p[j]))
					add_edge(i,j,length(p[i],p[j]));
		// for (int i=1;i<=tot;i++)
		// 	cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<endl;
		printf("%.2f\n",spfa(0,num-1));
	}

	return 0;
}