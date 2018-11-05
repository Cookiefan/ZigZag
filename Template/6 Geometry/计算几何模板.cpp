计算几何模板
目录：
1.计算几何 2

1.1 注意 2
1.2几何公式 2
1.3 多边形 4
1.4多边形切割 7
1.5 浮点函数 8
1.6 面积 14
1.7球面 15
1.8三角形 18
1.9三维几何 21
1.10 凸包 29
水平序 29
极角序 30
卷包裹法 31
1.11 网格 33
1.12 圆 34
1.13 矢量运算求几何模板 36
1.14结构体表示几何图形 48
1.15四城部分几何模板 53
1.16  一些代码 55
1.16.1 最小圆覆盖_zju1450 55
1.16.2 直线旋转_两凸包的最短距离(poj3608)59
1.16.3 扇形的重心 63
1.16.4 根据经度纬度求球面距离 64
1.16.5 多边形的重心 65
1.16.6 存不存在一个平面把两堆点分开(poj3643)67
1.16.7 pku_3335_判断多边形的核是否存在68
1.16.8 pku_2600_二分+圆的参数方程75
1.16.9 pku_1151_矩形相交的面积77
1.16.10 pku_1118_共线最多的点的个数79
1.16.11 pku2826_线段围成的区域可储水量81
1.16.12 Pick公式 85
1.16.13 N点中三个点组成三角形面积最大87
1.16.14 直线关于圆的反射 90
1.16.15 pku2002_3432_N个点最多组成多少个正方形(hao)95
1.16.16 pku1981_单位圆覆盖最多点(poj1981)CircleandPoints98
1.16.17 pku3668_GameofLine_N个点最多确定多少互不平行的直线(poj3668)100
1.16.18 求凸多边形直径 101
1.16.19 矩形面积并，周长并 103
1.16.20 pku2069 最小球覆盖 103
1.16.21 最大空凸包、最大空矩形 106
1.16.22 求圆和多边形的交 106
半平面交 110
Nlgn 110
N^2 112

 

1.计算几何
1.1 注意
1. 注意舍入方式(0.5的舍入方向);防止输出-0.
2. 几何题注意多测试不对称数据.
3. 整数几何注意xmult和dmult是否会出界;
   符点几何注意eps的使用.
4. 避免使用斜率;注意除数是否会为0.
5. 公式一定要化简后再代入.
6. 判断同一个2*PI域内两角度差应该是
   abs(a1-a2)<beta||abs(a1-a2)>pi+pi-beta;
   相等应该是
   abs(a1-a2)<eps||abs(a1-a2)>pi+pi-eps;
7. 需要的话尽量使用atan2,注意:atan2(0,0)=0,
   atan2(1,0)=pi/2,atan2(-1,0)=-pi/2,atan2(0,1)=0,atan2(0,-1)=pi.
8. cross product = |u|*|v|*sin(a)
   dot product = |u|*|v|*cos(a)
9. (P1-P0)x(P2-P0)结果的意义:
   正: <P0,P1>在<P0,P2>顺时针(0,pi)内
   负: <P0,P1>在<P0,P2>逆时针(0,pi)内
   0 : <P0,P1>,<P0,P2>共线,夹角为0或pi
10. 误差限缺省使用1e-8!
1.2几何公式
三角形:
1. 半周长 P=(a+b+c)/2
2. 面积 S=aHa/2=absin(C)/2=sqrt(P(P-a)(P-b)(P-c))
3. 中线 Ma=sqrt(2(b^2+c^2)-a^2)/2=sqrt(b^2+c^2+2bccos(A))/2
4. 角平分线 Ta=sqrt(bc((b+c)^2-a^2))/(b+c)=2bccos(A/2)/(b+c)
5. 高线 Ha=bsin(C)=csin(B)=sqrt(b^2-((a^2+b^2-c^2)/(2a))^2)
6. 内切圆半径 r=S/P=asin(B/2)sin(C/2)/sin((B+C)/2)
               =4Rsin(A/2)sin(B/2)sin(C/2)=sqrt((P-a)(P-b)(P-c)/P)
               =Ptan(A/2)tan(B/2)tan(C/2)
7. 外接圆半径 R=abc/(4S)=a/(2sin(A))=b/(2sin(B))=c/(2sin(C))

 


四边形:
D1,D2为对角线,M对角线中点连线,A为对角线夹角
1. a^2+b^2+c^2+d^2=D1^2+D2^2+4M^2
2. S=D1D2sin(A)/2
(以下对圆的内接四边形)
3. ac+bd=D1D2
4. S=sqrt((P-a)(P-b)(P-c)(P-d)),P为半周长

 


正n边形:
R为外接圆半径,r为内切圆半径
1. 中心角 A=2PI/n
2. 内角 C=(n-2)PI/n
3. 边长 a=2sqrt(R^2-r^2)=2Rsin(A/2)=2rtan(A/2)
4. 面积 S=nar/2=nr^2tan(A/2)=nR^2sin(A)/2=na^2/(4tan(A/2))

 


圆:
1. 弧长 l=rA
2. 弦长 a=2sqrt(2hr-h^2)=2rsin(A/2)
3. 弓形高 h=r-sqrt(r^2-a^2/4)=r(1-cos(A/2))=atan(A/4)/2
4. 扇形面积 S1=rl/2=r^2A/2
5. 弓形面积 S2=(rl-a(r-h))/2=r^2(A-sin(A))/2

 


棱柱:
1. 体积 V=Ah,A为底面积,h为高
2. 侧面积 S=lp,l为棱长,p为直截面周长
3. 全面积 T=S+2A

 


棱锥:
1. 体积 V=Ah/3,A为底面积,h为高
(以下对正棱锥)
2. 侧面积 S=lp/2,l为斜高,p为底面周长
3. 全面积 T=S+A

 


棱台:
1. 体积 V=(A1+A2+sqrt(A1A2))h/3,A1.A2为上下底面积,h为高
(以下为正棱台)
2. 侧面积 S=(p1+p2)l/2,p1.p2为上下底面周长,l为斜高
3. 全面积 T=S+A1+A2

 


圆柱:
1. 侧面积 S=2PIrh
2. 全面积 T=2PIr(h+r)
3. 体积 V=PIr^2h

 


圆锥:
1. 母线 l=sqrt(h^2+r^2)
2. 侧面积 S=PIrl
3. 全面积 T=PIr(l+r)
4. 体积 V=PIr^2h/3

 


圆台:
1. 母线 l=sqrt(h^2+(r1-r2)^2)
2. 侧面积 S=PI(r1+r2)l
3. 全面积 T=PIr1(l+r1)+PIr2(l+r2)
4. 体积 V=PI(r1^2+r2^2+r1r2)h/3

 


球:
1. 全面积 T=4PIr^2
2. 体积 V=4PIr^3/3

 


球台:
1. 侧面积 S=2PIrh
2. 全面积 T=PI(2rh+r1^2+r2^2)
3. 体积 V=PIh(3(r1^2+r2^2)+h^2)/6

 


球扇形:
1. 全面积 T=PIr(2h+r0),h为球冠高,r0为球冠底面半径
2. 体积 V=2PIr^2h/3

 

1.3 多边形
#include <stdlib.h>
#include <math.h>
#define MAXN 1000
#define offset 10000
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
#define _sign(x) ((x)>eps?1:((x)<-eps?2:0))
struct point{double x,y;};
struct line{point a,b;};


double xmult(point p1,point p2,point p0){
 return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}


//判定凸多边形,顶点按顺时针或逆时针给出,允许相邻边共线
int is_convex(int n,point* p){
 int i,s[3]={1,1,1};
 for (i=0;i<n&&s[1]|s[2];i++)
  s[_sign(xmult(p[(i+1)%n],p[(i+2)%n],p[i]))]=0;
 return s[1]|s[2];
}


//判定凸多边形,顶点按顺时针或逆时针给出,不允许相邻边共线
int is_convex_v2(int n,point* p){
 int i,s[3]={1,1,1};
 for (i=0;i<n&&s[0]&&s[1]|s[2];i++)
  s[_sign(xmult(p[(i+1)%n],p[(i+2)%n],p[i]))]=0;
 return s[0]&&s[1]|s[2];
}


//判点在凸多边形内或多边形边上,顶点按顺时针或逆时针给出
int inside_convex(point q,int n,point* p){
 int i,s[3]={1,1,1};
 for (i=0;i<n&&s[1]|s[2];i++)
  s[_sign(xmult(p[(i+1)%n],q,p[i]))]=0;
 return s[1]|s[2];
}


//判点在凸多边形内,顶点按顺时针或逆时针给出,在多边形边上返回0
int inside_convex_v2(point q,int n,point* p){
 int i,s[3]={1,1,1};
 for (i=0;i<n&&s[0]&&s[1]|s[2];i++)
  s[_sign(xmult(p[(i+1)%n],q,p[i]))]=0;
 return s[0]&&s[1]|s[2];
}


//判点在任意多边形内,顶点按顺时针或逆时针给出
//on_edge表示点在多边形边上时的返回值,offset为多边形坐标上限
int inside_polygon(point q,int n,point* p,int on_edge=1){
 point q2;
 int i=0,count;
 while (i<n)
  for (count=i=0,q2.x=rand()+offset,q2.y=rand()+offset;i<n;i++)
   if (zero(xmult(q,p[i],p[(i+1)%n]))&&(p[i].x-q.x)*(p[(i+1)%n].x-q.x)<eps&&(p[i].y-q.y)*(p[(i+1)%n].y-q.y)<eps)
    return on_edge;
   else if (zero(xmult(q,q2,p[i])))
    break;
   else if (xmult(q,p[i],q2)*xmult(q,p[(i+1)%n],q2)<-eps&&xmult(p[i],q,p[(i+1)%n])*xmult(p[i],q2,p[(i+1)%n])<-eps)
    count++;
 return count&1;
}


inline int opposite_side(point p1,point p2,point l1,point l2){
 return xmult(l1,p1,l2)*xmult(l1,p2,l2)<-eps;
}


inline int dot_online_in(point p,point l1,point l2){
 return zero(xmult(p,l1,l2))&&(l1.x-p.x)*(l2.x-p.x)<eps&&(l1.y-p.y)*(l2.y-p.y)<eps;
}


//判线段在任意多边形内,顶点按顺时针或逆时针给出,与边界相交返回1
int inside_polygon(point l1,point l2,int n,point* p){
 point t[MAXN],tt;
 int i,j,k=0;
 if (!inside_polygon(l1,n,p)||!inside_polygon(l2,n,p))
  return 0;
 for (i=0;i<n;i++)
  if (opposite_side(l1,l2,p[i],p[(i+1)%n])&&opposite_side(p[i],p[(i+1)%n],l1,l2))
   return 0;
  else if (dot_online_in(l1,p[i],p[(i+1)%n]))
   t[k++]=l1;
  else if (dot_online_in(l2,p[i],p[(i+1)%n]))
   t[k++]=l2;
  else if (dot_online_in(p[i],l1,l2))
   t[k++]=p[i];
 for (i=0;i<k;i++)
  for (j=i+1;j<k;j++){
   tt.x=(t[i].x+t[j].x)/2;
   tt.y=(t[i].y+t[j].y)/2;
   if (!inside_polygon(tt,n,p))
    return 0;   
  }
 return 1;
}


point intersection(line u,line v){
 point ret=u.a;
 double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
   /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
 ret.x+=(u.b.x-u.a.x)*t;
 ret.y+=(u.b.y-u.a.y)*t;
 return ret;
}


point barycenter(point a,point b,point c){
 line u,v;
 u.a.x=(a.x+b.x)/2;
 u.a.y=(a.y+b.y)/2;
 u.b=c;
 v.a.x=(a.x+c.x)/2;
 v.a.y=(a.y+c.y)/2;
 v.b=b;
 return intersection(u,v);
}


//多边形重心
point barycenter(int n,point* p){
 point ret,t;
 double t1=0,t2;
 int i;
 ret.x=ret.y=0;
 for (i=1;i<n-1;i++)
  if (fabs(t2=xmult(p[0],p[i],p[i+1]))>eps){
   t=barycenter(p[0],p[i],p[i+1]);
   ret.x+=t.x*t2;
   ret.y+=t.y*t2;
   t1+=t2;
  }
 if (fabs(t1)>eps)
  ret.x/=t1,ret.y/=t1;
 return ret;
}


1.4多边形切割
//多边形切割
//可用于半平面交
#define MAXN 100
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point{double x,y;};


double xmult(point p1,point p2,point p0){
 return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}


int same_side(point p1,point p2,point l1,point l2){
 return xmult(l1,p1,l2)*xmult(l1,p2,l2)>eps;
}


point intersection(point u1,point u2,point v1,point v2){
 point ret=u1;
 double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
   /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
 ret.x+=(u2.x-u1.x)*t;
 ret.y+=(u2.y-u1.y)*t;
 return ret;
}


//将多边形沿l1,l2确定的直线切割在side侧切割,保证l1,l2,side不共线
void polygon_cut(int& n,point* p,point l1,point l2,point side){
 point pp[MAXN];
 int m=0,i;
 for (i=0;i<n;i++){
  if (same_side(p[i],side,l1,l2))
   pp[m++]=p[i];
  if (!same_side(p[i],p[(i+1)%n],l1,l2)&&!(zero(xmult(p[i],l1,l2))&&zero(xmult(p[(i+1)%n],l1,l2))))
   pp[m++]=intersection(p[i],p[(i+1)%n],l1,l2);
 }
 for (n=i=0;i<m;i++)
  if (!i||!zero(pp[i].x-pp[i-1].x)||!zero(pp[i].y-pp[i-1].y))
   p[n++]=pp[i];
 if (zero(p[n-1].x-p[0].x)&&zero(p[n-1].y-p[0].y))
  n--;
 if (n<3)
  n=0;
}


1.5 浮点函数
//浮点几何函数库
#include <math.h>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point{double x,y;};
struct line{point a,b;};


//计算cross product (P1-P0)x(P2-P0)
double xmult(point p1,point p2,point p0){
 return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double xmult(double x1,double y1,double x2,double y2,double x0,double y0){
 return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}


//计算dot product (P1-P0).(P2-P0)
double dmult(point p1,point p2,point p0){
 return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
double dmult(double x1,double y1,double x2,double y2,double x0,double y0){
 return (x1-x0)*(x2-x0)+(y1-y0)*(y2-y0);
}


//两点距离
double distance(point p1,point p2){
 return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double distance(double x1,double y1,double x2,double y2){
 return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}


//判三点共线
int dots_inline(point p1,point p2,point p3){
 return zero(xmult(p1,p2,p3));
}
int dots_inline(double x1,double y1,double x2,double y2,double x3,double y3){
 return zero(xmult(x1,y1,x2,y2,x3,y3));
}


//判点是否在线段上,包括端点
int dot_online_in(point p,line l){
 return zero(xmult(p,l.a,l.b))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&(l.a.y-p.y)*(l.b.y-p.y)<eps;
}
int dot_online_in(point p,point l1,point l2){
 return zero(xmult(p,l1,l2))&&(l1.x-p.x)*(l2.x-p.x)<eps&&(l1.y-p.y)*(l2.y-p.y)<eps;
}
int dot_online_in(double x,double y,double x1,double y1,double x2,double y2){
 return zero(xmult(x,y,x1,y1,x2,y2))&&(x1-x)*(x2-x)<eps&&(y1-y)*(y2-y)<eps;
}


//判点是否在线段上,不包括端点
int dot_online_ex(point p,line l){
 return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y))&&(!zero(p.x-l.b.x)||!zero(p.y-l.b.y));
}
int dot_online_ex(point p,point l1,point l2){
 return dot_online_in(p,l1,l2)&&(!zero(p.x-l1.x)||!zero(p.y-l1.y))&&(!zero(p.x-l2.x)||!zero(p.y-l2.y));
}
int dot_online_ex(double x,double y,double x1,double y1,double x2,double y2){
 return dot_online_in(x,y,x1,y1,x2,y2)&&(!zero(x-x1)||!zero(y-y1))&&(!zero(x-x2)||!zero(y-y2));
}


//判两点在线段同侧,点在线段上返回0
int same_side(point p1,point p2,line l){
 return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>eps;
}
int same_side(point p1,point p2,point l1,point l2){
 return xmult(l1,p1,l2)*xmult(l1,p2,l2)>eps;
}


//判两点在线段异侧,点在线段上返回0
int opposite_side(point p1,point p2,line l){
 return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-eps;
}
int opposite_side(point p1,point p2,point l1,point l2){
 return xmult(l1,p1,l2)*xmult(l1,p2,l2)<-eps;
}


//判两直线平行
int parallel(line u,line v){
 return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
}
int parallel(point u1,point u2,point v1,point v2){
 return zero((u1.x-u2.x)*(v1.y-v2.y)-(v1.x-v2.x)*(u1.y-u2.y));
}


//判两直线垂直
int perpendicular(line u,line v){
 return zero((u.a.x-u.b.x)*(v.a.x-v.b.x)+(u.a.y-u.b.y)*(v.a.y-v.b.y));
}
int perpendicular(point u1,point u2,point v1,point v2){
 return zero((u1.x-u2.x)*(v1.x-v2.x)+(u1.y-u2.y)*(v1.y-v2.y));
}


//判两线段相交,包括端点和部分重合
int intersect_in(line u,line v){
 if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
  return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
 return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
int intersect_in(point u1,point u2,point v1,point v2){
 if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))
  return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);
 return dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);
}


//判两线段相交,不包括端点和部分重合
int intersect_ex(line u,line v){
 return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
int intersect_ex(point u1,point u2,point v1,point v2){
 return opposite_side(u1,u2,v1,v2)&&opposite_side(v1,v2,u1,u2);
}


//计算两直线交点,注意事先判断直线是否平行!
//线段交点请另外判线段相交(同时还是要判断是否平行!)
point intersection(line u,line v){
 point ret=u.a;
 double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
   /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
 ret.x+=(u.b.x-u.a.x)*t;
 ret.y+=(u.b.y-u.a.y)*t;
 return ret;
}
point intersection(point u1,point u2,point v1,point v2){
 point ret=u1;
 double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
   /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
 ret.x+=(u2.x-u1.x)*t;
 ret.y+=(u2.y-u1.y)*t;
 return ret;
}


//点到直线上的最近点
point ptoline(point p,line l){
 point t=p;
 t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
 return intersection(p,t,l.a,l.b);
}
point ptoline(point p,point l1,point l2){
 point t=p;
 t.x+=l1.y-l2.y,t.y+=l2.x-l1.x;
 return intersection(p,t,l1,l2);
}


//点到直线距离
double disptoline(point p,line l){
 return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
}
double disptoline(point p,point l1,point l2){
 return fabs(xmult(p,l1,l2))/distance(l1,l2);
}
double disptoline(double x,double y,double x1,double y1,double x2,double y2){
 return fabs(xmult(x,y,x1,y1,x2,y2))/distance(x1,y1,x2,y2);
}


//点到线段上的最近点
point ptoseg(point p,line l){
 point t=p;
 t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
 if (xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
  return distance(p,l.a)<distance(p,l.b)?l.a:l.b;
 return intersection(p,t,l.a,l.b);
}
point ptoseg(point p,point l1,point l2){
 point t=p;
 t.x+=l1.y-l2.y,t.y+=l2.x-l1.x;
 if (xmult(l1,t,p)*xmult(l2,t,p)>eps)
  return distance(p,l1)<distance(p,l2)?l1:l2;
 return intersection(p,t,l1,l2);
}


//点到线段距离
double disptoseg(point p,line l){
 point t=p;
 t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
 if (xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
  return distance(p,l.a)<distance(p,l.b)?distance(p,l.a):distance(p,l.b);
 return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
}
double disptoseg(point p,point l1,point l2){
 point t=p;
 t.x+=l1.y-l2.y,t.y+=l2.x-l1.x;
 if (xmult(l1,t,p)*xmult(l2,t,p)>eps)
  return distance(p,l1)<distance(p,l2)?distance(p,l1):distance(p,l2);
 return fabs(xmult(p,l1,l2))/distance(l1,l2);
}


//矢量V以P为顶点逆时针旋转angle并放大scale倍
point rotate(point v,point p,double angle,double scale){
 point ret=p;
 v.x-=p.x,v.y-=p.y;
 p.x=scale*cos(angle);
 p.y=scale*sin(angle);
 ret.x+=v.x*p.x-v.y*p.y;
 ret.y+=v.x*p.y+v.y*p.x;
 return ret;
}


//p点关于直线L的对称点
ponit symmetricalPointofLine(point p, line L)
{
    point p2;
    double d;
    d = L.a * L.a + L.b * L.b;
    p2.x = (L.b * L.b * p.x - L.a * L.a * p.x - 
            2 * L.a * L.b * p.y - 2 * L.a * L.c) / d;
    p2.y = (L.a * L.a * p.y - L.b * L.b * p.y - 
            2 * L.a * L.b * p.x - 2 * L.b * L.c) / d;
    return p2;
}


//求两点的平分线
line bisector(point& a, point& b) {
 line ab, ans;  ab.set(a, b);
 double midx = (a.x + b.x)/2.0, midy = (a.y + b.y)/2.0;
 ans.a = -ab.b, ans.b = -ab.a, ans.c = -ab.b * midx + ab.a * midy;
 return ans;
}


// 已知入射线、镜面，求反射线。 
// a1,b1,c1为镜面直线方程(a1 x + b1 y + c1 = 0 ,下同)系数;  
a2,b2,c2为入射光直线方程系数;  
a,b,c为反射光直线方程系数. 
// 光是有方向的，使用时注意：入射光向量:<-b2,a2>；反射光向量:<b,-a>. 
// 不要忘记结果中可能会有"negative zeros"


void reflect(double a1,double b1,double c1,
double a2,double b2,double c2,
double &a,double &b,double &c) 
{ 
 double n,m; 
 double tpb,tpa; 
 tpb=b1*b2+a1*a2; 
 tpa=a2*b1-a1*b2; 
 m=(tpb*b1+tpa*a1)/(b1*b1+a1*a1); 
 n=(tpa*b1-tpb*a1)/(b1*b1+a1*a1); 
 if(fabs(a1*b2-a2*b1)<1e-20) 
 { 
  a=a2;b=b2;c=c2; 
  return; 
 } 
 double xx,yy; //(xx,yy)是入射线与镜面的交点。 
 xx=(b1*c2-b2*c1)/(a1*b2-a2*b1); 
 yy=(a2*c1-a1*c2)/(a1*b2-a2*b1); 
 a=n; 
 b=-m; 
 c=m*yy-xx*n; 
}


1.6 面积
#include <math.h>
struct point{double x,y;};


//计算cross product (P1-P0)x(P2-P0)
double xmult(point p1,point p2,point p0){
 return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double xmult(double x1,double y1,double x2,double y2,double x0,double y0){
 return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}


//计算三角形面积,输入三顶点
double area_triangle(point p1,point p2,point p3){
 return fabs(xmult(p1,p2,p3))/2;
}
double area_triangle(double x1,double y1,double x2,double y2,double x3,double y3){
 return fabs(xmult(x1,y1,x2,y2,x3,y3))/2;
}


//计算三角形面积,输入三边长
double area_triangle(double a,double b,double c){
 double s=(a+b+c)/2;
 return sqrt(s*(s-a)*(s-b)*(s-c));
}


//计算多边形面积,顶点按顺时针或逆时针给出
double area_polygon(int n,point* p){
 double s1=0,s2=0;
 int i;
 for (i=0;i<n;i++)
  s1+=p[(i+1)%n].y*p[i].x,s2+=p[(i+1)%n].y*p[(i+2)%n].x;
 return fabs(s1-s2)/2;
}


1.7球面
#include <math.h>
const double pi=acos(-1);


//计算圆心角lat表示纬度,-90<=w<=90,lng表示经度
//返回两点所在大圆劣弧对应圆心角,0<=angle<=pi
double angle(double lng1,double lat1,double lng2,double lat2){
 double dlng=fabs(lng1-lng2)*pi/180;
 while (dlng>=pi+pi)
  dlng-=pi+pi;
 if (dlng>pi)
  dlng=pi+pi-dlng;
 lat1*=pi/180,lat2*=pi/180;
 return acos(cos(lat1)*cos(lat2)*cos(dlng)+sin(lat1)*sin(lat2));
}


//计算距离,r为球半径
double line_dist(double r,double lng1,double lat1,double lng2,double lat2){
 double dlng=fabs(lng1-lng2)*pi/180;
 while (dlng>=pi+pi)
  dlng-=pi+pi;
 if (dlng>pi)
  dlng=pi+pi-dlng;
 lat1*=pi/180,lat2*=pi/180;
 return r*sqrt(2-2*(cos(lat1)*cos(lat2)*cos(dlng)+sin(lat1)*sin(lat2)));
}


//计算球面距离,r为球半径
inline double sphere_dist(double r,double lng1,double lat1,double lng2,double lat2){
 return r*angle(lng1,lat1,lng2,lat2);
}


//球面反射
//SGU110
// http://acm.sgu.ru/problem.php?contest=0&problem=110


#include <cstdio>
#include <cmath>


const int size = 555;
const double eps = 1e-9;


struct point {double x, y, z;} centre = {0, 0, 0};
struct circle {point o; double r;} cir[size];
struct ray {point s, dir;} l;
int n;


int dcmp (double x){return x < -eps ? -1 : x > eps;}
double sqr (double x){return x*x;}
double dot (point a, point b){return a.x * b.x + a.y * b.y + a.z * b.z;}
double dis2 (point a, point b){return sqr(a.x-b.x) + sqr(a.y-b.y) + sqr(a.z-b.z);}
double disToLine2 (point a, ray l){   /**** 点到直线L的距离的平方 **/
 point tmp;
 tmp.x =  l.dir.y * (a.z - l.s.z) - l.dir.z * (a.y - l.s.y);
 tmp.y = -l.dir.x * (a.z - l.s.z) + l.dir.z * (a.x - l.s.x);
 tmp.z =  l.dir.x * (a.y - l.s.y) - l.dir.y * (a.x - l.s.x); 
 return dis2 (tmp, centre) / dis2 (l.dir, centre);
}


/**　用解方程(点到圆心的距离为r)法求交点  (下面有向量法求交点, 两者取其一, 都OK)*/
/* 是向量分量表示发的系数, 必须在射线上,故K必须为正, t是交点***/
/*
bool find (circle p, ray l, double &k, point &t) 
{
 double x = l.s.x - p.o.x, y = l.s.y - p.o.y, z = l.s.z - p.o.z;
 double a = sqr(l.dir.x) + sqr(l.dir.y) + sqr(l.dir.z);
 double b = 2 * (x*l.dir.x + y*l.dir.y + z*l.dir.z);
 double c = x*x + y*y + z*z - p.r*p.r;
 double det = b*b - 4*a*c;
// printf ("a = %lf, b = %lf, c = %lf", a, b, c);
// printf ("det = %lf\n", det);
 if (dcmp(det) == -1) return false;
 k = (-b - sqrt(det)) / a / 2;
 if (dcmp(k) != 1) return false;
 t.x = l.s.x + k * l.dir.x;
 t.y = l.s.y + k * l.dir.y;
 t.z = l.s.z + k * l.dir.z;
 return true;
}
*/


/**** 用向量法求交点  ***/
bool find (circle p, ray l, double &k, point &t)
{
 double h2 = disToLine2 (p.o, l);
// printf ("h2 = %lf\n", h2);
 if (dcmp(p.r*p.r - h2) < 0) return false;
 point tmp;
 tmp.x = p.o.x - l.s.x;
 tmp.y = p.o.y - l.s.y;
 tmp.z = p.o.z - l.s.z;
 if (dcmp(dot(tmp, l.dir)) <= 0) return false;
 k = sqrt(dis2(p.o, l.s) - h2) - sqrt(p.r*p.r - h2);
 double k1 = k / sqrt(dis2(l.dir, centre));
 t.x = l.s.x + k1 * l.dir.x;
 t.y = l.s.y + k1 * l.dir.y;
 t.z = l.s.z + k1 * l.dir.z;
 return true; 
}
/*计算新射线的起点和方向 */
void newRay (ray &l, ray l1, point inter)
{
 double k = - 2 * dot(l.dir, l1.dir);
 l.dir.x += l1.dir.x * k;
 l.dir.y += l1.dir.y * k;
 l.dir.z += l1.dir.z * k;
 l.s = inter;
}
/* 返回的是最先相交的球的编号,均不相交,返回-1 */
int update ()
{
 int sign = -1, i;
 double k = 1e100, tmp;
 point inter, t;
 for (i = 1; i <= n; i++){ //找到最先相交的球
  if (!find (cir[i], l, tmp, t)) continue;
  if (dcmp (tmp - k) < 0) k = tmp, inter = t, sign = i;
 }
 //ray 变向
 if (sign == -1) return sign;
 ray l1;
 l1.s = cir[sign].o;
 l1.dir.x = (inter.x - l1.s.x) / cir[sign].r;
 l1.dir.y = (inter.y - l1.s.y) / cir[sign].r;
 l1.dir.z = (inter.z - l1.s.z) / cir[sign].r;
 newRay (l, l1, inter);
 return sign;
}
int main ()
{
//  freopen ("in", "r", stdin);
 int i;
 scanf ("%d", &n);
 for (i = 1; i <= n; i++) //输入空间的球位置
  scanf ("%lf%lf%lf%lf", &cir[i].o.x, &cir[i].o.y, &cir[i].o.z, &cir[i].r);
 scanf ("%lf%lf%lf%lf%lf%lf", &l.s.x, &l.s.y, &l.s.z, &l.dir.x, &l.dir.y, &l.dir.z);
 for (i = 0; i <= 10; i++){ //最多输出十次相交的球的编号
  int sign = update ();
  if (sign == -1) break;
  if (i == 0) printf ("%d", sign);
  else if (i < 10) printf (" %d", sign);
  else printf (" etc.");
 }
 puts ("");
}

 


1.8三角形
#include <math.h>
struct point{double x,y;};
struct line{point a,b;};


double distance(point p1,point p2){
 return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}


point intersection(line u,line v){
 point ret=u.a;
 double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
   /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
 ret.x+=(u.b.x-u.a.x)*t;
 ret.y+=(u.b.y-u.a.y)*t;
 return ret;
}


//外心
point circumcenter(point a,point b,point c){
 line u,v;
 u.a.x=(a.x+b.x)/2;
 u.a.y=(a.y+b.y)/2;
 u.b.x=u.a.x-a.y+b.y;
 u.b.y=u.a.y+a.x-b.x;
 v.a.x=(a.x+c.x)/2;
 v.a.y=(a.y+c.y)/2;
 v.b.x=v.a.x-a.y+c.y;
 v.b.y=v.a.y+a.x-c.x;
 return intersection(u,v);
}


//内心
point incenter(point a,point b,point c){
 line u,v;
 double m,n;
 u.a=a;
 m=atan2(b.y-a.y,b.x-a.x);
 n=atan2(c.y-a.y,c.x-a.x);
 u.b.x=u.a.x+cos((m+n)/2);
 u.b.y=u.a.y+sin((m+n)/2);
 v.a=b;
 m=atan2(a.y-b.y,a.x-b.x);
 n=atan2(c.y-b.y,c.x-b.x);
 v.b.x=v.a.x+cos((m+n)/2);
 v.b.y=v.a.y+sin((m+n)/2);
 return intersection(u,v);
}


//垂心
point perpencenter(point a,point b,point c){
 line u,v;
 u.a=c;
 u.b.x=u.a.x-a.y+b.y;
 u.b.y=u.a.y+a.x-b.x;
 v.a=b;
 v.b.x=v.a.x-a.y+c.y;
 v.b.y=v.a.y+a.x-c.x;
 return intersection(u,v);
}


//重心
//到三角形三顶点距离的平方和最小的点
//三角形内到三边距离之积最大的点
point barycenter(point a,point b,point c){
 line u,v;
 u.a.x=(a.x+b.x)/2;
 u.a.y=(a.y+b.y)/2;
 u.b=c;
 v.a.x=(a.x+c.x)/2;
 v.a.y=(a.y+c.y)/2;
 v.b=b;
 return intersection(u,v);
}


//费马点
//到三角形三顶点距离之和最小的点
point fermentpoint(point a,point b,point c){
 point u,v;
 double step=fabs(a.x)+fabs(a.y)+fabs(b.x)+fabs(b.y)+fabs(c.x)+fabs(c.y);
 int i,j,k;
 u.x=(a.x+b.x+c.x)/3;
 u.y=(a.y+b.y+c.y)/3;
 while (step>1e-10)
  for (k=0;k<10;step/=2,k++)
   for (i=-1;i<=1;i++)
    for (j=-1;j<=1;j++){
     v.x=u.x+step*i;
     v.y=u.y+step*j;
     if (distance(u,a)+distance(u,b)+distance(u,c)>distance(v,a)+distance(v,b)+distance(v,c))
      u=v;
    }
 return u;
}


//求曲率半径 三角形内最大可围成面积
#include<iostream>
 #include<cmath>
 using namespace std;
 const double pi=3.14159265358979;
 int main()
 {
    double a,b,c,d,p,s,r,ans,R,x,l; int T=0;
 while(cin>>a>>b>>c>>d&&a+b+c+d)
  {
  T++;
  l=a+b+c;
  p=l/2;
  s=sqrt(p*(p-a)*(p-b)*(p-c));
  R= s /p;
  if (d >= l)  ans = s;
  else if(2*pi*R>=d) ans=d*d/(4*pi);
  else
  {
   r = (l-d)/((l/R)-(2*pi));
   x = r*r*s/(R*R);
   ans = s - x + pi * r * r;  
  }
  printf("Case %d: %.2lf\n",T,ans);
  }
  return 0;
 }


1.9三维几何
//三维几何函数库
#include <math.h>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point3{double x,y,z;};
struct line3{point3 a,b;};
struct plane3{point3 a,b,c;};


//计算cross product U x V
point3 xmult(point3 u,point3 v){
 point3 ret;
 ret.x=u.y*v.z-v.y*u.z;
 ret.y=u.z*v.x-u.x*v.z;
 ret.z=u.x*v.y-u.y*v.x;
 return ret;
}


//计算dot product U . V
double dmult(point3 u,point3 v){
 return u.x*v.x+u.y*v.y+u.z*v.z;
}


//矢量差 U - V
point3 subt(point3 u,point3 v){
 point3 ret;
 ret.x=u.x-v.x;
 ret.y=u.y-v.y;
 ret.z=u.z-v.z;
 return ret;
}


//取平面法向量
point3 pvec(plane3 s){
 return xmult(subt(s.a,s.b),subt(s.b,s.c));
}
point3 pvec(point3 s1,point3 s2,point3 s3){
 return xmult(subt(s1,s2),subt(s2,s3));
}


//两点距离,单参数取向量大小
double distance(point3 p1,point3 p2){
 return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
}


//向量大小
double vlen(point3 p){
 return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}


//判三点共线
int dots_inline(point3 p1,point3 p2,point3 p3){
 return vlen(xmult(subt(p1,p2),subt(p2,p3)))<eps;
}


//判四点共面
int dots_onplane(point3 a,point3 b,point3 c,point3 d){
 return zero(dmult(pvec(a,b,c),subt(d,a)));
}


//判点是否在线段上,包括端点和共线
int dot_online_in(point3 p,line3 l){
 return zero(vlen(xmult(subt(p,l.a),subt(p,l.b))))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&
  (l.a.y-p.y)*(l.b.y-p.y)<eps&&(l.a.z-p.z)*(l.b.z-p.z)<eps;
}
int dot_online_in(point3 p,point3 l1,point3 l2){
 return zero(vlen(xmult(subt(p,l1),subt(p,l2))))&&(l1.x-p.x)*(l2.x-p.x)<eps&&
  (l1.y-p.y)*(l2.y-p.y)<eps&&(l1.z-p.z)*(l2.z-p.z)<eps;
}


//判点是否在线段上,不包括端点
int dot_online_ex(point3 p,line3 l){
 return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y)||!zero(p.z-l.a.z))&&
  (!zero(p.x-l.b.x)||!zero(p.y-l.b.y)||!zero(p.z-l.b.z));
}
int dot_online_ex(point3 p,point3 l1,point3 l2){
 return dot_online_in(p,l1,l2)&&(!zero(p.x-l1.x)||!zero(p.y-l1.y)||!zero(p.z-l1.z))&&
  (!zero(p.x-l2.x)||!zero(p.y-l2.y)||!zero(p.z-l2.z));
}


//判点是否在空间三角形上,包括边界,三点共线无意义
int dot_inplane_in(point3 p,plane3 s){
 return zero(vlen(xmult(subt(s.a,s.b),subt(s.a,s.c)))-vlen(xmult(subt(p,s.a),subt(p,s.b)))-
  vlen(xmult(subt(p,s.b),subt(p,s.c)))-vlen(xmult(subt(p,s.c),subt(p,s.a))));
}
int dot_inplane_in(point3 p,point3 s1,point3 s2,point3 s3){
 return zero(vlen(xmult(subt(s1,s2),subt(s1,s3)))-vlen(xmult(subt(p,s1),subt(p,s2)))-
  vlen(xmult(subt(p,s2),subt(p,s3)))-vlen(xmult(subt(p,s3),subt(p,s1))));
}


//判点是否在空间三角形上,不包括边界,三点共线无意义
int dot_inplane_ex(point3 p,plane3 s){
 return dot_inplane_in(p,s)&&vlen(xmult(subt(p,s.a),subt(p,s.b)))>eps&&
  vlen(xmult(subt(p,s.b),subt(p,s.c)))>eps&&vlen(xmult(subt(p,s.c),subt(p,s.a)))>eps;
}
int dot_inplane_ex(point3 p,point3 s1,point3 s2,point3 s3){
 return dot_inplane_in(p,s1,s2,s3)&&vlen(xmult(subt(p,s1),subt(p,s2)))>eps&&
  vlen(xmult(subt(p,s2),subt(p,s3)))>eps&&vlen(xmult(subt(p,s3),subt(p,s1)))>eps;
}


//判两点在线段同侧,点在线段上返回0,不共面无意义
int same_side(point3 p1,point3 p2,line3 l){
 return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))>eps;
}
int same_side(point3 p1,point3 p2,point3 l1,point3 l2){
 return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))>eps;
}


//判两点在线段异侧,点在线段上返回0,不共面无意义
int opposite_side(point3 p1,point3 p2,line3 l){
 return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))<-eps;
}
int opposite_side(point3 p1,point3 p2,point3 l1,point3 l2){
 return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))<-eps;
}


//判两点在平面同侧,点在平面上返回0
int same_side(point3 p1,point3 p2,plane3 s){
 return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))>eps;
}
int same_side(point3 p1,point3 p2,point3 s1,point3 s2,point3 s3){
 return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))>eps;
}


//判两点在平面异侧,点在平面上返回0
int opposite_side(point3 p1,point3 p2,plane3 s){
 return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))<-eps;
}
int opposite_side(point3 p1,point3 p2,point3 s1,point3 s2,point3 s3){
 return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))<-eps;
}


//判两直线平行
int parallel(line3 u,line3 v){
 return vlen(xmult(subt(u.a,u.b),subt(v.a,v.b)))<eps;
}
int parallel(point3 u1,point3 u2,point3 v1,point3 v2){
 return vlen(xmult(subt(u1,u2),subt(v1,v2)))<eps;
}


//判两平面平行
int parallel(plane3 u,plane3 v){
 return vlen(xmult(pvec(u),pvec(v)))<eps;
}
int parallel(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3){
 return vlen(xmult(pvec(u1,u2,u3),pvec(v1,v2,v3)))<eps;
}


//判直线与平面平行
int parallel(line3 l,plane3 s){
 return zero(dmult(subt(l.a,l.b),pvec(s)));
}
int parallel(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){
 return zero(dmult(subt(l1,l2),pvec(s1,s2,s3)));
}


//判两直线垂直
int perpendicular(line3 u,line3 v){
 return zero(dmult(subt(u.a,u.b),subt(v.a,v.b)));
}
int perpendicular(point3 u1,point3 u2,point3 v1,point3 v2){
 return zero(dmult(subt(u1,u2),subt(v1,v2)));
}


//判两平面垂直
int perpendicular(plane3 u,plane3 v){
 return zero(dmult(pvec(u),pvec(v)));
}
int perpendicular(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3){
 return zero(dmult(pvec(u1,u2,u3),pvec(v1,v2,v3)));
}


//判直线与平面平行
int perpendicular(line3 l,plane3 s){
 return vlen(xmult(subt(l.a,l.b),pvec(s)))<eps;
}
int perpendicular(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){
 return vlen(xmult(subt(l1,l2),pvec(s1,s2,s3)))<eps;
}


//判两线段相交,包括端点和部分重合
int intersect_in(line3 u,line3 v){
 if (!dots_onplane(u.a,u.b,v.a,v.b))
  return 0;
 if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
  return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
 return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
int intersect_in(point3 u1,point3 u2,point3 v1,point3 v2){
 if (!dots_onplane(u1,u2,v1,v2))
  return 0;
 if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))
  return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);
 return dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u2);
}


//判两线段相交,不包括端点和部分重合
int intersect_ex(line3 u,line3 v){
 return dots_onplane(u.a,u.b,v.a,v.b)&&opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
int intersect_ex(point3 u1,point3 u2,point3 v1,point3 v2){
 return dots_onplane(u1,u2,v1,v2)&&opposite_side(u1,u2,v1,v2)&&opposite_side(v1,v2,u1,u2);
}


//判线段与空间三角形相交,包括交于边界和(部分)包含
int intersect_in(line3 l,plane3 s){
 return !same_side(l.a,l.b,s)&&!same_side(s.a,s.b,l.a,l.b,s.c)&&
  !same_side(s.b,s.c,l.a,l.b,s.a)&&!same_side(s.c,s.a,l.a,l.b,s.b);
}
int intersect_in(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){
 return !same_side(l1,l2,s1,s2,s3)&&!same_side(s1,s2,l1,l2,s3)&&
  !same_side(s2,s3,l1,l2,s1)&&!same_side(s3,s1,l1,l2,s2);
}


//判线段与空间三角形相交,不包括交于边界和(部分)包含
int intersect_ex(line3 l,plane3 s){
 return opposite_side(l.a,l.b,s)&&opposite_side(s.a,s.b,l.a,l.b,s.c)&&
  opposite_side(s.b,s.c,l.a,l.b,s.a)&&opposite_side(s.c,s.a,l.a,l.b,s.b);
}
int intersect_ex(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){
 return opposite_side(l1,l2,s1,s2,s3)&&opposite_side(s1,s2,l1,l2,s3)&&
  opposite_side(s2,s3,l1,l2,s1)&&opposite_side(s3,s1,l1,l2,s2);
}


//计算两直线交点,注意事先判断直线是否共面和平行!
//线段交点请另外判线段相交(同时还是要判断是否平行!)
point3 intersection(line3 u,line3 v){
 point3 ret=u.a;
 double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
   /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
 ret.x+=(u.b.x-u.a.x)*t;
 ret.y+=(u.b.y-u.a.y)*t;
 ret.z+=(u.b.z-u.a.z)*t;
 return ret;
}
point3 intersection(point3 u1,point3 u2,point3 v1,point3 v2){
 point3 ret=u1;
 double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
   /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
 ret.x+=(u2.x-u1.x)*t;
 ret.y+=(u2.y-u1.y)*t;
 ret.z+=(u2.z-u1.z)*t;
 return ret;
}


//计算直线与平面交点,注意事先判断是否平行,并保证三点不共线!
//线段和空间三角形交点请另外判断
point3 intersection(line3 l,plane3 s){
 point3 ret=pvec(s);
 double t=(ret.x*(s.a.x-l.a.x)+ret.y*(s.a.y-l.a.y)+ret.z*(s.a.z-l.a.z))/
  (ret.x*(l.b.x-l.a.x)+ret.y*(l.b.y-l.a.y)+ret.z*(l.b.z-l.a.z));
 ret.x=l.a.x+(l.b.x-l.a.x)*t;
 ret.y=l.a.y+(l.b.y-l.a.y)*t;
 ret.z=l.a.z+(l.b.z-l.a.z)*t;
 return ret;
}
point3 intersection(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){
 point3 ret=pvec(s1,s2,s3);
 double t=(ret.x*(s1.x-l1.x)+ret.y*(s1.y-l1.y)+ret.z*(s1.z-l1.z))/
  (ret.x*(l2.x-l1.x)+ret.y*(l2.y-l1.y)+ret.z*(l2.z-l1.z));
 ret.x=l1.x+(l2.x-l1.x)*t;
 ret.y=l1.y+(l2.y-l1.y)*t;
 ret.z=l1.z+(l2.z-l1.z)*t;
 return ret;
}


//计算两平面交线,注意事先判断是否平行,并保证三点不共线!
line3 intersection(plane3 u,plane3 v){
 line3 ret;
 ret.a=parallel(v.a,v.b,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.a,v.b,u.a,u.b,u.c);
 ret.b=parallel(v.c,v.a,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.c,v.a,u.a,u.b,u.c);
 return ret;
}
line3 intersection(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3){
 line3 ret;
 ret.a=parallel(v1,v2,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v1,v2,u1,u2,u3);
 ret.b=parallel(v3,v1,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v3,v1,u1,u2,u3);
 return ret;
}


//点到直线距离
double ptoline(point3 p,line3 l){
 return vlen(xmult(subt(p,l.a),subt(l.b,l.a)))/distance(l.a,l.b);
}
double ptoline(point3 p,point3 l1,point3 l2){
 return vlen(xmult(subt(p,l1),subt(l2,l1)))/distance(l1,l2);
}


//点到平面距离
double ptoplane(point3 p,plane3 s){
 return fabs(dmult(pvec(s),subt(p,s.a)))/vlen(pvec(s));
}
double ptoplane(point3 p,point3 s1,point3 s2,point3 s3){
 return fabs(dmult(pvec(s1,s2,s3),subt(p,s1)))/vlen(pvec(s1,s2,s3));
}


//直线到直线距离
double linetoline(line3 u,line3 v){
 point3 n=xmult(subt(u.a,u.b),subt(v.a,v.b));
 return fabs(dmult(subt(u.a,v.a),n))/vlen(n);
}
double linetoline(point3 u1,point3 u2,point3 v1,point3 v2){
 point3 n=xmult(subt(u1,u2),subt(v1,v2));
 return fabs(dmult(subt(u1,v1),n))/vlen(n);
}


//两直线夹角cos值
double angle_cos(line3 u,line3 v){
 return dmult(subt(u.a,u.b),subt(v.a,v.b))/vlen(subt(u.a,u.b))/vlen(subt(v.a,v.b));
}
double angle_cos(point3 u1,point3 u2,point3 v1,point3 v2){
 return dmult(subt(u1,u2),subt(v1,v2))/vlen(subt(u1,u2))/vlen(subt(v1,v2));
}


//两平面夹角cos值
double angle_cos(plane3 u,plane3 v){
 return dmult(pvec(u),pvec(v))/vlen(pvec(u))/vlen(pvec(v));
}
double angle_cos(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3){
 return dmult(pvec(u1,u2,u3),pvec(v1,v2,v3))/vlen(pvec(u1,u2,u3))/vlen(pvec(v1,v2,v3));
}


//直线平面夹角sin值
double angle_sin(line3 l,plane3 s){
 return dmult(subt(l.a,l.b),pvec(s))/vlen(subt(l.a,l.b))/vlen(pvec(s));
}
double angle_sin(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3){
 return dmult(subt(l1,l2),pvec(s1,s2,s3))/vlen(subt(l1,l2))/vlen(pvec(s1,s2,s3));
}


1.10 凸包
//水平序
#define maxn 100005


struct point
{double x,y;}p[maxn],s[maxn];
bool operator < (point a,point b)
{return a.x<b.x || a.x==b.x&&a.y<b.y;}


int n,f;


double cp(point a,point b,point c)
{return (c.y-a.y)*(b.x-a.x)-(b.y-a.y)*(c.x-a.x);}


void Convex(point *p,int &n)
{
 sort(p,p+n);
 int i,j,r,top,m;
 s[0] = p[0];s[1] = p[1];top = 1;
 for(i=2;i<n;i++)
 {
  while( top>0 && cp(p[i],s[top],s[top-1])>=0 ) top--;
  top++;s[top] = p[i];
 }
 m = top;
 top++;s[top] = p[n-2];
 for(i=n-3;i>=0;i--)
 {
  while( top>m && cp(p[i],s[top],s[top-1])>=0 ) top--;
  top++;s[top] = p[i];
 }
 top--;
 n = top+1;
}


极角序
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define maxn 100005
int N;
struct A
{
 int x,y;
 int v,l;
}P[maxn];
int xmult(int x1,int y1,int x2,int y2,int x3,int y3)
{
 return (y2-y1)*(x3-x1)-(y3-y1)*(x2-x1);
}
void swap(A &a,A &b)
{
 A t = a;a = b,b = t;
}
bool operator < (A a,A b)
{
 int k = xmult(P[0].x,P[0].y,a.x,a.y,b.x,b.y);
 if( k<0 )
  return 1;
 else if( k==0 )
 {
  if( abs(P[0].x-a.x)<abs(P[0].x-b.x) )
   return 1;
  if( abs(P[0].y-a.y)<abs(P[0].y-b.y) )
   return 1;
 }
 return 0;
}
void Grem_scan(int n)
{
 int i,j,k,l;
 k = 0x7fffffff;
 for(i=0;i<n;i++)
  if( P[i].x<k || P[i].x==k && P[i].y<P[l].y )
  k = P[i].x,l = i;
 swap(P[l],P[0]);
 sort(P+1,P+n);
 
 l = 3;
 for(i=3;i<n;i++)
 {
  while( xmult(P[l-2].x,P[l-2].y,P[l-1].x,P[l-1].y,P[i].x,P[i].y)>0 )
   l--;
  P[l++] = P[i];
 }
}
main()
{
 int i,j,k,l;
 N = 0;
 while( scanf("%d%d",&P[N].x,&P[N].y)!=EOF )
  N++;
 Grem_scan(N);
 for(i=0;i<N;i++)
  if( P[i].x==0 && P[i].y==0 )
  break;
 k = i++;
 printf("(0,0)\n");
 while( i!=k )
  printf("(%d,%d)\n",P[i].x,P[i].y),i = (i+1)%N;
}


//卷包裹法
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define maxn 55
struct A
{
 int x,y;
}P[maxn];
int T,N;
bool B[maxn];
int as[maxn],L;
int xmult(A a,A b,A c)
{
 return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
main()
{
 int i,j,k,l;
 scanf("%d",&T);
 while( T-- )
 {
  scanf("%d",&N);
  k = 0x7ffffff;
  for(i=0;i<N;i++)
  {
   scanf("%d%d%d",&j,&P[i].x,&P[i].y);
   if( P[i].y<k )
    k = P[i].y,l = i;
  }
  memset(B,0,sizeof(B));
  B[l] = 1;
  as[0] = l;
  L = 1;
  while( 1 )
  {
   A a,b;
   if( L==1 )
    a.x = 0,a.y = P[as[0]].y;
   else
    a = P[as[L-2]];
   b = P[as[L-1]];


   k = -1;
   for(i=0;i<N;i++)
   {
    if( B[i] )
     continue;
    if( xmult(a,b,P[i])<0 )
     continue;
    if( k==-1 || xmult(P[as[L-1]],P[k],P[i])<0 || xmult(P[as[L-1]],P[k],P[i])==0 && P[i].y<P[k].y )
     k = i;
   }
   if( k==-1 )
    break;
   B[k] = 1;
   as[L++] = k;
  }
  printf("%d ",L);
  for(i=0;i<L;i++)
   printf("%d ",as[i]+1);
  printf("\n");
 }
}
}


1.11 网格
#define abs(x) ((x)>0?(x):-(x))
struct point{int x,y;};


int gcd(int a,int b){return b?gcd(b,a%b):a;}


//多边形上的网格点个数
int grid_onedge(int n,point* p){
 int i,ret=0;
 for (i=0;i<n;i++)
  ret+=gcd(abs(p[i].x-p[(i+1)%n].x),abs(p[i].y-p[(i+1)%n].y));
 return ret;
}


//多边形内的网格点个数
int grid_inside(int n,point* p){
 int i,ret=0;
 for (i=0;i<n;i++)
  ret+=p[(i+1)%n].y*(p[i].x-p[(i+2)%n].x);
 return (abs(ret)-grid_onedge(n,p))/2+1;
}


1.12 圆
#include <math.h>
#define eps 1e-8
struct point{double x,y;};


double xmult(point p1,point p2,point p0){
 return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}


double distance(point p1,point p2){
 return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}


double disptoline(point p,point l1,point l2){
 return fabs(xmult(p,l1,l2))/distance(l1,l2);
}


point intersection(point u1,point u2,point v1,point v2){
 point ret=u1;
 double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
   /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
 ret.x+=(u2.x-u1.x)*t;
 ret.y+=(u2.y-u1.y)*t;
 return ret;
}


//判直线和圆相交,包括相切
int intersect_line_circle(point c,double r,point l1,point l2){
 return disptoline(c,l1,l2)<r+eps;
}


//判线段和圆相交,包括端点和相切
int intersect_seg_circle(point c,double r,point l1,point l2){
 double t1=distance(c,l1)-r,t2=distance(c,l2)-r;
 point t=c;
 if (t1<eps||t2<eps)
  return t1>-eps||t2>-eps;
 t.x+=l1.y-l2.y;
 t.y+=l2.x-l1.x;
 return xmult(l1,c,t)*xmult(l2,c,t)<eps&&disptoline(c,l1,l2)-r<eps;
}


//判圆和圆相交,包括相切
int intersect_circle_circle(point c1,double r1,point c2,double r2){
 return distance(c1,c2)<r1+r2+eps&&distance(c1,c2)>fabs(r1-r2)-eps;
}


//计算圆上到点p最近点,如p与圆心重合,返回p本身
point dot_to_circle(point c,double r,point p){
 point u,v;
 if (distance(p,c)<eps)
  return p;
 u.x=c.x+r*fabs(c.x-p.x)/distance(c,p);
 u.y=c.y+r*fabs(c.y-p.y)/distance(c,p)*((c.x-p.x)*(c.y-p.y)<0?-1:1);
 v.x=c.x-r*fabs(c.x-p.x)/distance(c,p);
 v.y=c.y-r*fabs(c.y-p.y)/distance(c,p)*((c.x-p.x)*(c.y-p.y)<0?-1:1);
 return distance(u,p)<distance(v,p)?u:v;
}


//计算直线与圆的交点,保证直线与圆有交点
//计算线段与圆的交点可用这个函数后判点是否在线段上
void intersection_line_circle(point c,double r,point l1,point l2,point& p1,point& p2){
 point p=c;
 double t;
 p.x+=l1.y-l2.y;
 p.y+=l2.x-l1.x;
 p=intersection(p,c,l1,l2);
 t=sqrt(r*r-distance(p,c)*distance(p,c))/distance(l1,l2);
 p1.x=p.x+(l2.x-l1.x)*t;
 p1.y=p.y+(l2.y-l1.y)*t;
 p2.x=p.x-(l2.x-l1.x)*t;
 p2.y=p.y-(l2.y-l1.y)*t;
}


//计算圆与圆的交点,保证圆与圆有交点,圆心不重合
void intersection_circle_circle(point c1,double r1,point c2,double r2,point& p1,point& p2){
 point u,v;
 double t;
 t=(1+(r1*r1-r2*r2)/distance(c1,c2)/distance(c1,c2))/2;
 u.x=c1.x+(c2.x-c1.x)*t;
 u.y=c1.y+(c2.y-c1.y)*t;
 v.x=u.x+c1.y-c2.y;
 v.y=u.y-c1.x+c2.x;
 intersection_line_circle(c1,r1,u,v,p1,p2);
}


//将向量p逆时针旋转angle角度
Point Rotate(Point p,double angle) {
    Point res;
    res.x=p.x*cos(angle)-p.y*sin(angle);
    res.y=p.x*sin(angle)+p.y*cos(angle);
    return res;
}
//求圆外一点对圆(o,r)的两个切点result1和result2
void TangentPoint_PC(Point poi,Point o,double r,Point &result1,Point &result2) {
    double line=sqrt((poi.x-o.x)*(poi.x-o.x)+(poi.y-o.y)*(poi.y-o.y));
    double angle=acos(r/line);
    Point unitvector,lin;
    lin.x=poi.x-o.x;
    lin.y=poi.y-o.y;
    unitvector.x=lin.x/sqrt(lin.x*lin.x+lin.y*lin.y)*r;
    unitvector.y=lin.y/sqrt(lin.x*lin.x+lin.y*lin.y)*r;
    result1=Rotate(unitvector,-angle);
    result2=Rotate(unitvector,angle);
    result1.x+=o.x;
    result1.y+=o.y;
    result2.x+=o.x;
    result2.y+=o.y;
    return;
}


1.13 矢量运算求几何模板
#include <iostream>
#include <cmath> 
#include <vector> 
#include <algorithm> 
#define MAX_N 100
using namespace std;


///////////////////////////////////////////////////////////////////
//常量区
const double INF        = 1e10;     // 无穷大 
const double EPS        = 1e-15;    // 计算精度 
const int LEFT          = 0;        // 点在直线左边 
const int RIGHT         = 1;        // 点在直线右边 
const int ONLINE        = 2;        // 点在直线上 
const int CROSS         = 0;        // 两直线相交 
const int COLINE        = 1;        // 两直线共线 
const int PARALLEL      = 2;        // 两直线平行 
const int NOTCOPLANAR   = 3;        // 两直线不共面 
const int INSIDE        = 1;        // 点在图形内部 
const int OUTSIDE       = 2;        // 点在图形外部 
const int BORDER        = 3;        // 点在图形边界 
const int BAOHAN        = 1;        // 大圆包含小圆
const int NEIQIE        = 2;        // 内切
const int XIANJIAO      = 3;        // 相交
const int WAIQIE        = 4;        // 外切
const int XIANLI        = 5;        // 相离
const double pi     = acos(-1.0)  //圆周率
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//类型定义区
struct Point {              // 二维点或矢量 
    double x, y; 
    double angle, dis; 
    Point() {} 
    Point(double x0, double y0): x(x0), y(y0) {} 
}; 
struct Point3D {            //三维点或矢量 
    double x, y, z; 
    Point3D() {} 
    Point3D(double x0, double y0, double z0): x(x0), y(y0), z(z0) {} 
}; 
struct Line {               // 二维的直线或线段 
    Point p1, p2; 
    Line() {} 
    Line(Point p10, Point p20): p1(p10), p2(p20) {} 
}; 
struct Line3D {             // 三维的直线或线段 
    Point3D p1, p2; 
    Line3D() {} 
    Line3D(Point3D p10, Point3D p20): p1(p10), p2(p20) {} 
}; 
struct Rect {              // 用长宽表示矩形的方法 w, h分别表示宽度和高度 
    double w, h; 
 Rect() {}
 Rect(double _w,double _h) : w(_w),h(_h) {}
}; 
struct Rect_2 {             // 表示矩形，左下角坐标是(xl, yl)，右上角坐标是(xh, yh) 
    double xl, yl, xh, yh; 
 Rect_2() {}
 Rect_2(double _xl,double _yl,double _xh,double _yh) : xl(_xl),yl(_yl),xh(_xh),yh(_yh) {}
}; 
struct Circle {            //圆
 Point c;
 double r;
 Circle() {}
 Circle(Point _c,double _r) :c(_c),r(_r) {}
};
typedef vector<Point> Polygon;      // 二维多边形     
typedef vector<Point> Points;       // 二维点集 
typedef vector<Point3D> Points3D;   // 三维点集 
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//基本函数区
inline double max(double x,double y) 
{ 
    return x > y ? x : y; 
} 
inline double min(double x, double y) 
{ 
    return x > y ? y : x; 
} 
inline bool ZERO(double x)              // x == 0 
{ 
    return (fabs(x) < EPS); 
} 
inline bool ZERO(Point p)               // p == 0 
{ 
    return (ZERO(p.x) && ZERO(p.y)); 
} 
inline bool ZERO(Point3D p)              // p == 0 
{ 
    return (ZERO(p.x) && ZERO(p.y) && ZERO(p.z)); 
} 
inline bool EQ(double x, double y)      // eqaul, x == y 
{ 
    return (fabs(x - y) < EPS); 
} 
inline bool NEQ(double x, double y)     // not equal, x != y 
{ 
    return (fabs(x - y) >= EPS); 
} 
inline bool LT(double x, double y)     // less than, x < y 
{ 
    return ( NEQ(x, y) && (x < y) ); 
} 
inline bool GT(double x, double y)     // greater than, x > y 
{ 
    return ( NEQ(x, y) && (x > y) ); 
} 
inline bool LEQ(double x, double y)     // less equal, x <= y 
{ 
    return ( EQ(x, y) || (x < y) ); 
} 
inline bool GEQ(double x, double y)     // greater equal, x >= y 
{ 
    return ( EQ(x, y) || (x > y) ); 
} 
// 注意！！！ 
// 如果是一个很小的负的浮点数 
// 保留有效位数输出的时候会出现-0.000这样的形式， 
// 前面多了一个负号 
// 这就会导致错误！！！！！！ 
// 因此在输出浮点数之前，一定要调用次函数进行修正！ 
inline double FIX(double x) 
{ 
    return (fabs(x) < EPS) ? 0 : x; 
} 
//////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//二维矢量运算 
bool operator==(Point p1, Point p2)  
{ 
    return ( EQ(p1.x, p2.x) &&  EQ(p1.y, p2.y) ); 
} 
bool operator!=(Point p1, Point p2)  
{ 
    return ( NEQ(p1.x, p2.x) ||  NEQ(p1.y, p2.y) ); 
} 
bool operator<(Point p1, Point p2) 
{ 
    if (NEQ(p1.x, p2.x)) { 
        return (p1.x < p2.x); 
    } else { 
        return (p1.y < p2.y); 
    } 
} 
Point operator+(Point p1, Point p2)  
{ 
    return Point(p1.x + p2.x, p1.y + p2.y); 
} 
Point operator-(Point p1, Point p2)  
{ 
    return Point(p1.x - p2.x, p1.y - p2.y); 
} 
double operator*(Point p1, Point p2) // 计算叉乘 p1 × p2 
{ 
    return (p1.x * p2.y - p2.x * p1.y); 
} 
double operator&(Point p1, Point p2) { // 计算点积 p1·p2 
    return (p1.x * p2.x + p1.y * p2.y); 
} 
double Norm(Point p) // 计算矢量p的模 
{ 
    return sqrt(p.x * p.x + p.y * p.y); 
} 
// 把矢量p旋转角度angle (弧度表示) 
// angle > 0表示逆时针旋转 
// angle < 0表示顺时针旋转 
Point Rotate(Point p, double angle) 
{ 
    Point result; 
    result.x = p.x * cos(angle) - p.y * sin(angle); 
    result.y = p.x * sin(angle) + p.y * cos(angle); 
    return result; 
} 
//////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////// 
//三维矢量运算 
bool operator==(Point3D p1, Point3D p2)  
{ 
    return ( EQ(p1.x, p2.x) && EQ(p1.y, p2.y) && EQ(p1.z, p2.z) ); 
} 
bool operator<(Point3D p1, Point3D p2) 
{ 
    if (NEQ(p1.x, p2.x)) { 
        return (p1.x < p2.x); 
    } else if (NEQ(p1.y, p2.y)) { 
        return (p1.y < p2.y); 
    } else { 
        return (p1.z < p2.z); 
    } 
} 
Point3D operator+(Point3D p1, Point3D p2)  
{ 
    return Point3D(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z); 
} 
Point3D operator-(Point3D p1, Point3D p2)  
{ 
    return Point3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z); 
} 
Point3D operator*(Point3D p1, Point3D p2) // 计算叉乘 p1 x p2 
{ 
    return Point3D(p1.y * p2.z - p1.z * p2.y, 
        p1.z * p2.x - p1.x * p2.z, 
        p1.x * p2.y - p1.y * p2.x );         
} 
double operator&(Point3D p1, Point3D p2) { // 计算点积 p1·p2 
    return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z); 
} 
double Norm(Point3D p) // 计算矢量p的模 
{ 
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z); 
}


//////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//点.线段.直线问题
//
double Distance(Point p1, Point p2) //2点间的距离
{
 return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double Distance(Point3D p1, Point3D p2) //2点间的距离,三维
{
 return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
}
double Distance(Point p, Line L) // 求二维平面上点到直线的距离 
{ 
    return ( fabs((p - L.p1) * (L.p2 - L.p1)) / Norm(L.p2 - L.p1) ); 
} 
double Distance(Point3D p, Line3D L)// 求三维空间中点到直线的距离 
{ 
    return ( Norm((p - L.p1) * (L.p2 - L.p1)) / Norm(L.p2 - L.p1) ); 
} 
bool OnLine(Point p, Line L) // 判断二维平面上点p是否在直线L上 
{ 
    return ZERO( (p - L.p1) * (L.p2 - L.p1) ); 
} 
bool OnLine(Point3D p, Line3D L) // 判断三维空间中点p是否在直线L上 
{ 
    return ZERO( (p - L.p1) * (L.p2 - L.p1) ); 
} 
int Relation(Point p, Line L) // 计算点p与直线L的相对关系 ,返回ONLINE,LEFT,RIGHT
{ 
    double res = (L.p2 - L.p1) * (p - L.p1); 
    if (EQ(res, 0)) { 
        return ONLINE; 
    } else if (res > 0) { 
        return LEFT; 
    } else { 
        return RIGHT; 
    } 
} 
bool SameSide(Point p1, Point p2, Line L) // 判断点p1, p2是否在直线L的同侧 
{ 
    double m1 = (p1 - L.p1) * (L.p2 - L.p1); 
    double m2 = (p2 - L.p1) * (L.p2 - L.p1); 
    return GT(m1 * m2, 0); 
} 
bool OnLineSeg(Point p, Line L) // 判断二维平面上点p是否在线段l上 
{ 
    return ( ZERO( (L.p1 - p) * (L.p2 - p) ) && 
        LEQ((p.x - L.p1.x)*(p.x - L.p2.x), 0) && 
        LEQ((p.y - L.p1.y)*(p.y - L.p2.y), 0) ); 
} 
bool OnLineSeg(Point3D p, Line3D L) // 判断三维空间中点p是否在线段l上 
{ 
    return ( ZERO((L.p1 - p) * (L.p2 - p)) && 
        EQ( Norm(p - L.p1) + Norm(p - L.p2), Norm(L.p2 - L.p1)) ); 
} 
Point SymPoint(Point p, Line L) // 求二维平面上点p关于直线L的对称点 
{ 
    Point result; 
    double a = L.p2.x - L.p1.x; 
    double b = L.p2.y - L.p1.y; 
    double t = ( (p.x - L.p1.x) * a + (p.y - L.p1.y) * b ) / (a*a + b*b); 
    result.x = 2 * L.p1.x + 2 * a * t - p.x; 
    result.y = 2 * L.p1.y + 2 * b * t - p.y; 
    return result; 
} 
bool Coplanar(Points3D points) // 判断一个点集中的点是否全部共面 
{ 
    int i; 
    Point3D p;


    if (points.size() < 4) return true; 
    p = (points[2] - points[0]) * (points[1] - points[0]); 
    for (i = 3; i < points.size(); i++) { 
        if (! ZERO(p & points[i]) ) return false; 
    } 
    return true; 
} 
bool LineIntersect(Line L1, Line L2) // 判断二维的两直线是否相交 
{ 
    return (! ZERO((L1.p1 - L1.p2)*(L2.p1 - L2.p2)) );  // 是否平行 
} 
bool LineIntersect(Line3D L1, Line3D L2) // 判断三维的两直线是否相交 
{ 
    Point3D p1 = L1.p1 - L1.p2; 
    Point3D p2 = L2.p1 - L2.p2; 
    Point3D p  = p1 * p2; 
    if (ZERO(p)) return false;      // 是否平行 
    p = (L2.p1 - L1.p2) * (L1.p1 - L1.p2); 
    return ZERO(p & L2.p2);         // 是否共面 
} 
bool LineSegIntersect(Line L1, Line L2) // 判断二维的两条线段是否相交 
{ 
    return ( GEQ( max(L1.p1.x, L1.p2.x), min(L2.p1.x, L2.p2.x) ) && 
        GEQ( max(L2.p1.x, L2.p2.x), min(L1.p1.x, L1.p2.x) ) && 
        GEQ( max(L1.p1.y, L1.p2.y), min(L2.p1.y, L2.p2.y) ) && 
        GEQ( max(L2.p1.y, L2.p2.y), min(L1.p1.y, L1.p2.y) ) && 
        LEQ( ((L2.p1 - L1.p1) * (L1.p2 - L1.p1)) * ((L2.p2 -  L1.p1) * (L1.p2 - L1.p1)), 0 ) && 
        LEQ( ((L1.p1 - L2.p1) * (L2.p2 - L2.p1)) * ((L1.p2 -  L2.p1) * (L2.p2 - L2.p1)), 0 ) );              
} 
bool LineSegIntersect(Line3D L1, Line3D L2) // 判断三维的两条线段是否相交 
{ 
    // todo 
    return true; 
} 
// 计算两条二维直线的交点，结果在参数P中返回 
// 返回值说明了两条直线的位置关系:  COLINE   -- 共线  PARALLEL -- 平行  CROSS    -- 相交 
int CalCrossPoint(Line L1, Line L2, Point& P) 
{ 
    double A1, B1, C1, A2, B2, C2;


    A1 = L1.p2.y - L1.p1.y; 
    B1 = L1.p1.x - L1.p2.x; 
    C1 = L1.p2.x * L1.p1.y - L1.p1.x * L1.p2.y;


    A2 = L2.p2.y - L2.p1.y; 
    B2 = L2.p1.x - L2.p2.x; 
    C2 = L2.p2.x * L2.p1.y - L2.p1.x * L2.p2.y;


    if (EQ(A1 * B2, B1 * A2))    { 
        if (EQ( (A1 + B1) * C2, (A2 + B2) * C1 )) { 
            return COLINE; 
        } else { 
            return PARALLEL; 
        } 
    } else { 
        P.x = (B2 * C1 - B1 * C2) / (A2 * B1 - A1 * B2); 
        P.y = (A1 * C2 - A2 * C1) / (A2 * B1 - A1 * B2); 
        return CROSS; 
    } 
} 
// 计算两条三维直线的交点，结果在参数P中返回 
// 返回值说明了两条直线的位置关系 COLINE   -- 共线  PARALLEL -- 平行  CROSS    -- 相交  NONCOPLANAR -- 不公面 
int CalCrossPoint(Line3D L1, Line3D L2, Point3D& P) 
{ 
    // todo 
    return 0; 
} 
// 计算点P到直线L的最近点 
Point NearestPointToLine(Point P, Line L)  
{ 
    Point result; 
    double a, b, t;


    a = L.p2.x - L.p1.x; 
    b = L.p2.y - L.p1.y; 
    t = ( (P.x - L.p1.x) * a + (P.y - L.p1.y) * b ) / (a * a + b * b);


    result.x = L.p1.x + a * t; 
    result.y = L.p1.y + b * t; 
    return result; 
} 
// 计算点P到线段L的最近点 
Point NearestPointToLineSeg(Point P, Line L)  
{ 
    Point result; 
    double a, b, t;


    a = L.p2.x - L.p1.x; 
    b = L.p2.y - L.p1.y; 
    t = ( (P.x - L.p1.x) * a + (P.y - L.p1.y) * b ) / (a * a + b * b);


    if ( GEQ(t, 0) && LEQ(t, 1) ) { 
        result.x = L.p1.x + a * t; 
        result.y = L.p1.y + b * t; 
    } else { 
        if ( Norm(P - L.p1) < Norm(P - L.p2) ) { 
            result = L.p1; 
        } else { 
            result = L.p2; 
        } 
    } 
    return result; 
} 
// 计算险段L1到线段L2的最短距离 
double MinDistance(Line L1, Line L2)  
{ 
    double d1, d2, d3, d4;


    if (LineSegIntersect(L1, L2)) { 
        return 0; 
    } else { 
        d1 = Norm( NearestPointToLineSeg(L1.p1, L2) - L1.p1 ); 
        d2 = Norm( NearestPointToLineSeg(L1.p2, L2) - L1.p2 ); 
        d3 = Norm( NearestPointToLineSeg(L2.p1, L1) - L2.p1 ); 
        d4 = Norm( NearestPointToLineSeg(L2.p2, L1) - L2.p2 ); 
         
        return min( min(d1, d2), min(d3, d4) ); 
    } 
} 
// 求二维两直线的夹角， 
// 返回值是0~Pi之间的弧度 
double Inclination(Line L1, Line L2) 
{ 
    Point u = L1.p2 - L1.p1; 
    Point v = L2.p2 - L2.p1; 
    return acos( (u & v) / (Norm(u)*Norm(v)) ); 
} 
// 求三维两直线的夹角， 
// 返回值是0~Pi之间的弧度 
double Inclination(Line3D L1, Line3D L2) 
{ 
    Point3D u = L1.p2 - L1.p1; 
    Point3D v = L2.p2 - L2.p1; 
    return acos( (u & v) / (Norm(u)*Norm(v)) ); 
} 
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// 判断两个矩形是否相交 
// 如果相邻不算相交 
bool Intersect(Rect_2 r1, Rect_2 r2) 
{ 
    return ( max(r1.xl, r2.xl) < min(r1.xh, r2.xh) && 
             max(r1.yl, r2.yl) < min(r1.yh, r2.yh) ); 
} 
// 判断矩形r2是否可以放置在矩形r1内 
// r2可以任意地旋转 
//发现原来的给出的方法过不了OJ上的无归之室这题，
//所以用了自己的代码
bool IsContain(Rect r1, Rect r2)      //矩形的w>h
 { 
     if(r1.w >r2.w && r1.h > r2.h) return true;
     else
     {
        double r = sqrt(r2.w*r2.w + r2.h*r2.h) / 2.0;
        double alpha = atan2(r2.h,r2.w);
        double sita = asin((r1.h/2.0)/r);
        double x = r * cos(sita - 2*alpha);
        double y = r * sin(sita - 2*alpha);
        if(x < r1.w/2.0 && y < r1.h/2.0 && x > 0 && y > -r1.h/2.0) return true;
        else return false;
     }
} 
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//圆
Point Center(const Circle & C) //圆心
{      
    return C.c;      
}   


double Area(const Circle &C)
{
 return pi*C.r*C.r; 
}


double CommonArea(const Circle & A, const Circle & B) //两个圆的公共面积       
{      
    double area = 0.0;      
    const Circle & M = (A.r > B.r) ? A : B;      
    const Circle & N = (A.r > B.r) ? B : A;      
    double D = Distance(Center(M), Center(N));      
    if ((D < M.r + N.r) && (D > M.r - N.r))      
    {      
        double cosM = (M.r * M.r + D * D - N.r * N.r) / (2.0 * M.r * D);      
        double cosN = (N.r * N.r + D * D - M.r * M.r) / (2.0 * N.r * D);      
        double alpha = 2.0 * acos(cosM);      
        double beta  = 2.0 * acos(cosN);      
        double TM = 0.5 * M.r * M.r * sin(alpha);      
        double TN = 0.5 * N.r * N.r * sin(beta);      
        double FM = (alpha / (2*pi)) * Area(M);      
        double FN = (beta / (2*pi)) * Area(N);      
        area = FM + FN - TM - TN;      
    }      
    else if (D <= M.r - N.r)      
    {      
        area = Area(N);      
    }      
    return area;      
} 
     
bool IsInCircle(const Circle & C, const Rect_2 & rect)//判断圆是否在矩形内(不允许相切)
{      
    return (GT(C.c.x - C.r, rect.xl)
  &&  LT(C.c.x + C.r, rect.xh)
  &&  GT(C.c.y - C.r, rect.yl)
  &&  LT(C.c.y + C.r, rect.yh));      
} 


//判断2圆的位置关系
//返回: 
//BAOHAN   = 1;        // 大圆包含小圆
//NEIQIE   = 2;        // 内切
//XIANJIAO = 3;        // 相交
//WAIQIE   = 4;        // 外切
//XIANLI   = 5;        // 相离
int CirCir(const Circle &c1, const Circle &c2)//判断2圆的位置关系
{
 double dis = Distance(c1.c,c2.c);
 if(LT(dis,fabs(c1.r-c2.r))) return BAOHAN;
 if(EQ(dis,fabs(c1.r-c2.r))) return NEIQIE;
 if(LT(dis,c1.r+c2.r) && GT(dis,fabs(c1.r-c2.r))) return XIANJIAO;
 if(EQ(dis,c1.r+c2.r)) return WAIQIE;
 return XIANLI;
}
////////////////////////////////////////////////////////////////////////


int main()
{
 return 0;
}

 


1.14结构体表示几何图形
//计算几何(二维)   
#include <cmath>   
#include <cstdio>   
#include <algorithm>   
using namespace std;  


typedef double TYPE;   
#define Abs(x) (((x)>0)?(x):(-(x)))   
#define Sgn(x) (((x)<0)?(-1):(1))   
#define Max(a,b) (((a)>(b))?(a):(b))   
#define Min(a,b) (((a)<(b))?(a):(b))   
#define Epsilon 1e-8   
#define Infinity 1e+10   
#define PI acos(-1.0)//3.14159265358979323846   
TYPE Deg2Rad(TYPE deg){return (deg * PI / 180.0);}   
TYPE Rad2Deg(TYPE rad){return (rad * 180.0 / PI);}   
TYPE Sin(TYPE deg){return sin(Deg2Rad(deg));}   
TYPE Cos(TYPE deg){return cos(Deg2Rad(deg));}   
TYPE ArcSin(TYPE val){return Rad2Deg(asin(val));}   
TYPE ArcCos(TYPE val){return Rad2Deg(acos(val));}   
TYPE Sqrt(TYPE val){return sqrt(val);} 


//点   
struct POINT   
{   
  TYPE x;   
  TYPE y;   
  POINT() : x(0), y(0) {};   
  POINT(TYPE _x_, TYPE _y_) : x(_x_), y(_y_) {};   
};   
// 两个点的距离   
TYPE Distance(const POINT & a, const POINT & b)   
{   
  return Sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));   
}   
//线段   
struct SEG   
{     
  POINT a; //起点   
  POINT b; //终点   
  SEG() {};   
  SEG(POINT _a_, POINT _b_):a(_a_),b(_b_) {};   
};     
//直线(两点式)   
struct LINE   
{   
  POINT a;   
  POINT b;   
  LINE() {};   
  LINE(POINT _a_, POINT _b_) : a(_a_), b(_b_) {};   
};   
//直线(一般式)   
struct LINE2   
{   
  TYPE A,B,C;   
  LINE2() {};   
  LINE2(TYPE _A_, TYPE _B_, TYPE _C_) : A(_A_), B(_B_), C(_C_) {};   
};  


//两点式化一般式   
LINE2 Line2line(const LINE & L) // y=kx+c k=y/x
{   
  LINE2 L2;   
  L2.A = L.b.y - L.a.y;   
  L2.B = L.a.x - L.b.x;   
  L2.C = L.b.x * L.a.y - L.a.x * L.b.y;   
  return L2;   
}  


// 引用返回直线 Ax + By + C =0 的系数   
void Coefficient(const LINE & L, TYPE & A, TYPE & B, TYPE & C)   
{   
  A = L.b.y - L.a.y;   
  B = L.a.x - L.b.x;   
  C = L.b.x * L.a.y - L.a.x * L.b.y;   
}   
void Coefficient(const POINT & p,const TYPE a,TYPE & A,TYPE & B,TYPE & C)   
{   
  A = Cos(a);   
  B = Sin(a);   
  C = - (p.y * B + p.x * A);   
}   
/判等(值，点，直线)   
bool IsEqual(TYPE a, TYPE b)   
{   
  return (Abs(a - b) <Epsilon);   
}   
bool IsEqual(const POINT & a, const POINT & b)   
{   
  return (IsEqual(a.x, b.x) && IsEqual(a.y, b.y));   
}   
bool IsEqual(const LINE & A, const LINE & B)   
{   
  TYPE A1, B1, C1;   
  TYPE A2, B2, C2;   
  Coefficient(A, A1, B1, C1);   
  Coefficient(B, A2, B2, C2);   
  return IsEqual(A1 * B2, A2 * B1) && IsEqual(A1 * C2, A2 * C1) && IsEqual(B1 * C2, B2 * C1);   
}   
// 矩形   
struct RECT   
{   
  POINT a; // 左下点     
  POINT b; // 右上点     
  RECT() {};   
  RECT(const POINT & _a_, const POINT & _b_) { a = _a_; b = _b_; }   
};  


//矩形化标准   
RECT Stdrect(const RECT & q)
{   
  TYPE t;   
  RECT p=q;   
  if(p.a.x > p.b.x) swap(p.a.x , p.b.x);    
  if(p.a.y > p.b.y) swap(p.a.y , p.b.y);    
  return p;   
}  


//根据下标返回矩形的边     
SEG Edge(const RECT & rect, int idx)   
{   
  SEG edge;   
  while (idx < 0) idx += 4;   
  switch (idx % 4)   
  {   
  case 0: //下边
    edge.a = rect.a;   
    edge.b = POINT(rect.b.x, rect.a.y);   
    break;   
  case 1: //右边
    edge.a = POINT(rect.b.x, rect.a.y);   
    edge.b = rect.b;   
    break;   
  case 2: //上边  
    edge.a = rect.b;   
    edge.b = POINT(rect.a.x, rect.b.y);   
    break;   
  case 3: //左边  
    edge.a = POINT(rect.a.x, rect.b.y);   
    edge.b = rect.a;   
    break;   
  default:   
    break;   
  }   
  return edge;   
}  


//矩形的面积   
TYPE Area(const RECT & rect)   
{   
  return (rect.b.x - rect.a.x) * (rect.b.y - rect.a.y);   
}  


//两个矩形的公共面积     
TYPE CommonArea(const RECT & A, const RECT & B)   
{   
  TYPE area = 0.0;   
  POINT LL(Max(A.a.x, B.a.x), Max(A.a.y, B.a.y));   
  POINT UR(Min(A.b.x, B.b.x), Min(A.b.y, B.b.y));   
  if( (LL.x <= UR.x) && (LL.y <= UR.y) )   
  {   
    area = Area(RECT(LL, UR));   
  }   
  return area;   
}  
//判断圆是否在矩形内(不允许相切)   
bool IsInCircle(const CIRCLE & circle, const RECT & rect)   
{   
  return (circle.x - circle.r > rect.a.x) &&   
    (circle.x + circle.r < rect.b.x) &&   
    (circle.y - circle.r > rect.a.y) &&   
    (circle.y + circle.r < rect.b.y);   
}  


//判断矩形是否在圆内(不允许相切)   
bool IsInRect(const CIRCLE & circle, const RECT & rect)   
{   
  POINT c,d;   
  c.x=rect.a.x; c.y=rect.b.y;   
  d.x=rect.b.x; d.y=rect.a.y;   
  return (Distance( Center(circle) , rect.a ) < circle.r) &&   
    (Distance( Center(circle) , rect.b ) < circle.r) &&   
    (Distance( Center(circle) , c ) < circle.r) &&   
    (Distance( Center(circle) , d ) < circle.r);   
}  


//判断矩形是否与圆相离(不允许相切)   
bool Isoutside(const CIRCLE & circle, const RECT & rect)   
{   
  POINT c,d;   
  c.x=rect.a.x; c.y=rect.b.y;   
  d.x=rect.b.x; d.y=rect.a.y;   
  return (Distance( Center(circle) , rect.a ) > circle.r) &&   
    (Distance( Center(circle) , rect.b ) > circle.r) &&   
    (Distance( Center(circle) , c ) > circle.r) &&   
    (Distance( Center(circle) , d ) > circle.r) &&   
    (rect.a.x > circle.x || circle.x > rect.b.x || rect.a.y > circle.y || circle.y > rect.b.y) ||   
    ((circle.x - circle.r > rect.b.x) ||   
    (circle.x + circle.r < rect.a.x) ||   
    (circle.y - circle.r > rect.b.y) ||   
    (circle.y + circle.r < rect.a.y));   
}  


1.15四城部分几何模板
/*
1.注意实际运用的时候可以用sqrd代替dist提高精度，节省时间
*/
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;


const double INF = 10e300;
const double EPS = 1e-8;
const double PI = acos(-1.0);


inline int dblcmp(double a, double b) {if(fabs(a-b) < EPS) return 0;if(a < b) return -1;return 1;}
inline double Max(double a, double b) { if(dblcmp(a, b) == 1) return a; return b; }
inline double Min(double a, double b) { if(dblcmp(a, b) == 1) return b; return a; }
inline double Agl(double deg) { return deg * PI / 180.0; }


struct Point { double x, y; void set(double a, double b) { x = a; y = b; } };
struct Vec { double x, y; void set(Point& a, Point& b) { x = b.x-a.x; y = b.y-a.y; } };
struct Line { double a, b, c; Point st, end;
void set(Point& u, Point& v) {a = v.y - u.y; b = u.x - v.x; c = a*u.x + b*u.y; st = u; end = v; } };


inline double dist(Point& a, Point& b) { return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
inline double sqrd(Point& a, Point& b) { return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y); }
inline double dot(Vec& a, Vec& b) { return a.x * b.x + a.y * b.y; }
inline double cross(Vec& a, Vec& b) { return a.x * b.y - a.y * b.x; }
inline double cross(Point& a, Point& b, Point& c) {Vec x, y; x.set(a, b); y.set(a, c); return cross(x, y); }
//返回1代表a在bc之间 0代表在端点 -1代表在外面
inline int between(Point& a, Point& b, Point& c) { Vec x, y; x.set(a,b); y.set(a,c); return dblcmp(dot(x, y),0); }


//3维坐标转换 输入是度数
void trans(double lat, double log, double& x, double& y, double& z, double radius) {
 x = radius * cos(lat) * cos(log);
 y = radius * cos(lat) * sin(log);
 z = radius * sin(lat);
}


//求两点的平分线
Line bisector(Point& a, Point& b) {
 Line ab, ans; ab.set(a, b);
 double midx = (a.x + b.x)/2.0, midy = (a.y + b.y)/2.0;
 ans.a = -ab.b, ans.b = -ab.a, ans.c = -ab.b * midx + ab.a * midy;
 return ans;
}

 


//线线相交 如果平行 返回-1, 重合返回-2
int line_line_intersect(Line& l1, Line& l2, Point& s) {
 double det = l1.a*l2.b - l2.a*l1.b;
    if(dblcmp(det, 0.0) == 0) { //平行或者重合
  if(dblcmp(point_line_dist(l1.st, l2.st, l2.end, 0), 0) == 0) 
   return -2;
  return -1;
 }
    s.x = (l2.b*l1.c - l1.b*l2.c)/det;
    s.y = (l1.a*l2.c - l2.a*l1.c)/det;
 return 1;
}


//2线段相交 ab, cd 交点是s 平行返回-1, 重合返回-2, 不在线段上面返回0 在线段中间返回1 在线段两端返回2
int seg_seg_intersect(Point& a, Point& b, Point& c, Point& d, Point& s) {
    Line l1, l2; l1.set(a, b); l2.set(c, d);
 int ans = line_line_intersect(l1, l2, s);
 if(ans == 1) {
  if(between(s, a, b) == 1 && between(s, c, d) == 1) 
   return 1;
  if(between(s, a, b) == -1 && between(s, c, d) == -1)
   return 0;
  return 2;
 }
 return ans;
}


//求三点共圆 中心放在center中 返回半径
double center_3point(Point& a, Point& b, Point& c, Point& center) {
 Line x = bisector(a, b), y = bisector(b, c);
 line_line_intersect(x, y, center);
 return dist(center, a);
}


1.16  一些代码
1.16.1 最小圆覆盖_zju1450
/*
包含点集所有点的最小圆的算法
最小圆覆盖


 http://acm.zju.edu.cn/show_problem.php?pid=1450
 
 相关题目最小球包含  http://acm.pku.edu.cn/JudgeOnline/problem?id=2069


平面上有n个点，给定n个点的坐标，试找一个半径最小的圆，将n
个点全部包围，点可以在圆上。


1. 在点集中任取3点A,B,C。
2. 作一个包含A,B,C三点的最小圆,圆周可能通过这3点，也可能只通过
其中两点,但包含第3点.后一种情况圆周上的两点一定是位于圆的一条直
径的两端。
3. 在点集中找出距离第2步所建圆圆心最远的D点，若D点已在圆内或圆周上，
则该圆即为所求的圆，算法结束.则，执行第4步。
4. 在A,B,C,D中选3个点,使由它们生成的一个包含这4个点的圆为最小，这3
点成为新的A,B,C，返回执行第2步。若在第4步生成的圆的圆周只通过A,B,C,D
中的两点，则圆周上的两点取成新的A和B,从另两点中任取一点作为新的C。


程序设计题解上的解题报告：
对于一个给定的点集A，记MinCircle(A)为点集A的最小外接圆，显然，对于所
有的点集情况A,MinCircle(A)都是存在且惟一的。需要特别说明的是，当A为空
集时，MinCircle(A)为空集，当A={a}时，MinCircle(A)圆心坐标为a，半径为0；
   显然，MinCircle(A)可以有A边界上最多三个点确定(当点集A中点的个数大于
1时，有可能两个点确定了MinCircle(A))，也就是说存在着一个点集B，|B|<=3
且B包含与A，有MinCircle(B)=MinCircle(A).所以，如果a不属于B，则
MinCircle(A-{a})=MinCircle(A);如果MinCircle(A-{a})不等于MinCircle(A),则
a属于B。
    所以我们可以从一个空集R开始，不断的把题目中给定的点集中的点加入R，同
时维护R的外接圆最小，这样就可以得到解决该题的算法。

 


pku2069

 

*/
#include <stdio.h>
#include <math.h>


const int maxn = 1005;
//const double eps = 1e-6;


struct TPoint
{
 double x, y;
 TPoint operator-(TPoint &a)
 {
  TPoint p1;
  p1.x = x - a.x;
  p1.y = y - a.y;
  return p1;
 }
};


struct TCircle
{
 double r;
 TPoint centre;
};


struct TTriangle
{
 TPoint t[3];
};


TCircle c;
TPoint a[maxn];


double distance(TPoint p1, TPoint p2)
{
 TPoint p3;
 p3.x = p2.x - p1.x;
 p3.y = p2.y - p1.y;
 return sqrt(p3.x * p3.x + p3.y * p3.y);
}


double triangleArea(TTriangle t)
{
 TPoint p1, p2;
 p1 = t.t[1] - t.t[0];
 p2 = t.t[2] - t.t[0];
 return fabs(p1.x * p2.y - p1.y * p2.x) / 2;
}


TCircle circumcircleOfTriangle(TTriangle t)
{
    //三角形的外接圆
    TCircle tmp;
    double a, b, c, c1, c2;
    double xA, yA, xB, yB, xC, yC;
    a = distance(t.t[0], t.t[1]);
    b = distance(t.t[1], t.t[2]);
    c = distance(t.t[2], t.t[0]);
    //根据S = a * b * c / R / 4;求半径R 
    tmp.r = a * b * c / triangleArea(t) / 4;
    
    xA = t.t[0].x; yA = t.t[0].y;
    xB = t.t[1].x; yB = t.t[1].y;
    xC = t.t[2].x; yC = t.t[2].y;
    c1 = (xA * xA + yA * yA - xB * xB - yB * yB) / 2;
    c2 = (xA * xA + yA * yA - xC * xC - yC * yC) / 2;
    
    tmp.centre.x = (c1 * (yA - yC) - c2 * (yA - yB)) / 
         ((xA - xB) * (yA - yC) - (xA - xC) * (yA - yB)); 
    tmp.centre.y = (c1 * (xA - xC) - c2 * (xA - xB)) / 
         ((yA - yB) * (xA - xC) - (yA - yC) * (xA - xB)); 
         
    return tmp;     
}


TCircle MinCircle2(int tce, TTriangle ce)
{
 TCircle tmp;
 if(tce == 0) tmp.r = -2;
 else if(tce == 1) 
 {
  tmp.centre = ce.t[0];
  tmp.r = 0;
 }
 else if(tce == 2)
 {
  tmp.r = distance(ce.t[0], ce.t[1]) / 2;
  tmp.centre.x = (ce.t[0].x + ce.t[1].x) / 2;
  tmp.centre.y = (ce.t[0].y + ce.t[1].y) / 2;  
 }
 else if(tce == 3) tmp = circumcircleOfTriangle(ce);
 return tmp;
}


void MinCircle(int t, int tce, TTriangle ce)
{
 int i, j;
 TPoint tmp;
 c = MinCircle2(tce, ce);
 if(tce == 3) return;
 for(i = 1;i <= t;i++)
 {
  if(distance(a[i], c.centre) > c.r)
  {
   ce.t[tce] = a[i];
   MinCircle(i - 1, tce + 1, ce);
   tmp = a[i];
   for(j = i;j >= 2;j--)
   {
    a[j] = a[j - 1];
   }
   a[1] = tmp;
  }
 }
}


void run(int n)
{
 TTriangle ce;
 int i;
 MinCircle(n, 0, ce);
 printf("%.2lf %.2lf %.2lf\n", c.centre.x, c.centre.y, c.r);
}


int main()
{
    freopen("circle.in", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n;
 while(scanf("%d", &n) != EOF && n)
 {
  for(int i = 1;i <= n;i++)
   scanf("%lf%lf", &a[i].x, &a[i].y);
  run(n);
 }
 return 0;
}

 


1.16.2 直线旋转_两凸包的最短距离(poj3608)
#include <stdio.h>
#include <math.h>


#define pi acos(-1.0)
#define eps 1e-6
#define inf 1e250
#define Maxn 10005


typedef struct TPoint
{
 double x, y;
}TPoint;


typedef struct TPolygon
{
 TPoint p[Maxn];
 int n;
}TPolygon;


typedef struct TLine
{
 double a, b, c;
}TLine;


double max(double a, double b)
{
 if(a > b) return a;
 return b;
}


double min(double a, double b)
{
 if(a < b) return a;
 return b;
}


double distance(TPoint p1, TPoint p2)
{
 return sqrt((p1.x - p2.x) * (p1.x - p2.x) 
  + (p1.y - p2.y) * (p1.y - p2.y));
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


double polygonArea(TPolygon p)
{
    int i, n;
    double area;
    n = p.n;
    area = 0;
    for(i = 1;i <= n;i++)
  area += (p.p[i - 1].x * p.p[i % n].y - p.p[i % n].x * p.p[i - 1].y);


 return area / 2;  
}


void ChangeClockwise(TPolygon &polygon)
{
 TPoint tmp;
 int i;
 for(i = 0;i <= (polygon.n - 1) / 2;i++)
 {
  tmp = polygon.p[i];
  polygon.p[i] = polygon.p[polygon.n - 1 - i];
  polygon.p[polygon.n - 1 - i] = tmp;   
 }
}


double disPointToSeg(TPoint p1, TPoint p2, TPoint p3)
{
    double a = distance(p1, p2);
    double b = distance(p1, p3);
    double c = distance(p2, p3);
    if(fabs(a + b - c) < eps) return 0;
    if(fabs(a + c - b) < eps || fabs(b + c - a) < eps) return min(a, b);
    double t1 = -a * a + b * b + c * c;
    double t2 = a * a - b * b + c * c;
    if(t1 <= 0 || t2 <= 0) return min(a, b);
    
    TLine l1 = lineFromSegment(p2, p3);
    return fabs(l1.a * p1.x + l1.b * p1.y + l1.c) / sqrt(l1.a * l1.a + l1.b * l1.b);      
}


double disPallSeg(TPoint p1, TPoint p2, TPoint p3, TPoint p4)
{
 return min(min(disPointToSeg(p1, p3, p4), disPointToSeg(p2, p3, p4)),
  min(disPointToSeg(p3, p1, p2), disPointToSeg(p4, p1, p2)));
}


double angle(TPoint p1, TPoint p2, double SlewRate)
{
 double ang, tmp;
 TPoint p;
 p.x = p2.x - p1.x;
 p.y = p2.y - p1.y;
 if(fabs(p.x) < eps)
 {
  if(p.y > 0) ang = pi / 2;
  else ang = 3 * pi / 2;
 }
 else 
 {
        ang = atan(p.y / p.x);
  if(p.x < 0) ang += pi;
 }
 while(ang < 0) ang += 2 * pi;
 if(ang >= pi) SlewRate += pi;
 if(ang > SlewRate) tmp = ang - SlewRate;
 else tmp = pi - (SlewRate - ang);
 while(tmp >= pi) tmp -= pi;
 if(fabs(tmp - pi) < eps) tmp = 0;
 return tmp;
}


int main()
{
 int n, m, i;
 TPolygon polygon1, polygon2;
 double ymin1, ymax2, ans, d;
 int k1, k2;
 while(scanf("%d%d", &n, &m) && n)
 {
  polygon1.n = n;
  polygon2.n = m;
  for(i = 0;i < n;i++)
   scanf("%lf%lf", &polygon1.p[i].x, &polygon1.p[i].y);
  for(i = 0;i < m;i++)
   scanf("%lf%lf", &polygon2.p[i].x, &polygon2.p[i].y); 
  if(polygonArea(polygon1) < 0) ChangeClockwise(polygon1);
  if(polygonArea(polygon2) < 0) ChangeClockwise(polygon2);
  ymin1 = inf, ymax2 = -inf;
  for(i = 0;i < n;i++)
   if(polygon1.p[i].y < ymin1) ymin1 = polygon1.p[i].y , k1 = i;
  for(i = 0;i < m;i++)
   if(polygon2.p[i].y > ymax2) ymax2 = polygon2.p[i].y , k2 = i; 
  double SlewRate = 0;
  double angle1, angle2;
  ans = inf;
  double Slope = 0;
  while(Slope <= 360) 
  { 
   while(SlewRate >= pi) SlewRate -= pi;
   if(fabs(pi - SlewRate) < eps) SlewRate = 0;
   angle1 = angle(polygon1.p[k1], polygon1.p[(k1 + 1) % n], SlewRate);
   angle2 = angle(polygon2.p[k2], polygon2.p[(k2 + 1) % m], SlewRate); 
   if(fabs(angle1 - angle2) < eps)
   {
    d = disPallSeg(polygon1.p[k1], polygon1.p[(k1 + 1) % n], polygon2.p[k2], polygon2.p[(k2 + 1) % m]); 
    if(d < ans) ans = d;
                k1++;
    k1 %= n;
    k2++;
    k2 %= m; 
    SlewRate += angle1;
    Slope += angle1;
   }
   else if(angle1 < angle2)
   {
    d = disPointToSeg(polygon2.p[k2], polygon1.p[k1], polygon1.p[(k1 + 1) % n]);
    if(d < ans) ans = d;
    k1++;
    k1 %= n;
    SlewRate += angle1;
    Slope += angle1;
   }
   else 
   {
    d = disPointToSeg(polygon1.p[k1], polygon2.p[k2], polygon2.p[(k2 + 1) % m]);
    if(d < ans) ans = d;
    k2++;
    k2 %= m;
    SlewRate += angle2;
    Slope += angle2;
   }
  }
  printf("%.5lf\n", ans);
 }
 return 0;
}


1.16.3 扇形的重心

 

//Xc = 2*R*sinA/3/A 
//A为圆心角的一半
#include <stdio.h>
#include <math.h>
int main()
{
 double r, angle;
 while(scanf("%lf%lf", &r, &angle) != EOF){
  angle /= 2;
  printf("%.6lf\n", 2 * r * sin(angle) / 3 / angle);
 }
 return 0;
}

 


1.16.4 根据经度纬度求球面距离

 

/*
假设地球是球体， 
设地球上某点的经度为lambda,纬度为phi， 
则这点的空间坐标是 
x=cos(phi)*cos(lambda) 
y=cos(phi)*sin(lambda) 
z=sin(phi) 
设地球上两点的空间坐标分别为(x1,y1,z1),(x2,y2,z2) 
直线距离即为R*sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1)),
则它们的夹角为 
A = acos(x1 * x2 + y1 * y2 + z1 * z2)，
则两地距离为 A * R，其中R为地球平均半径6371 
*/


/*
这里坐标都要乘以半径R，但由于是求角度，所以统一都没有乘 
注意这里还要判断坐标的正负和经度纬度的规定有关


pku_3407
*/
#include <stdio.h>
#include <math.h>


const double pi = acos(-1.0);


struct TPoint
{
   double x, y, z;
};
 
int main()
{
    double w1, wm1, j1, jm1, wd1, wd2;
    double w2, wm2, j2, jm2, jd1, jd2;
    TPoint p1, p2;
    char chr1, chr2;
    while(scanf("%lf%lf ", &w1, &wm1) != EOF){
        scanf("%c ", &chr1);
        scanf("%lf %lf %c", &j1, &jm1, &chr2);
        wd1 = (w1 + wm1 / 60) * pi / 180;
        jd1 = (j1 + jm1 / 60) * pi / 180;
        if(chr1 == 'S') wd1 *= -1.0;
        if(chr2 == 'W') jd1 *= -1.0;
        p1.x = cos(wd1) * cos(jd1);
        p1.y = cos(wd1) * sin(jd1);
        p1.z = sin(wd1);
        scanf("%lf %lf %c %lf %lf %c", &w2, &wm2, &chr1, &j2, &jm2, &chr2);
        wd2 = (w2 + wm2 / 60) * pi / 180;
        jd2 = (j2 + jm2 / 60) * pi / 180;
        if(chr1 == 'S') wd2 *= -1.0;
        if(chr2 == 'W') jd2 *= -1.0;
        p2.x = cos(wd2) * cos(jd2);
        p2.y = cos(wd2) * sin(jd2);
        p2.z = sin(wd2);
        double a = acos(p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
        printf("%.3lf\n", a * 6370.0);   
    }
    return 0;
}

 


1.16.5 多边形的重心
/*
题目描述：
有一个密度均匀的平面N多边形(3 <= N <= 1000000)，可能凹也可能凸，但没有边相交叉，
另外已知N个有序(顺时针或逆时针)顶点的坐标值，第j个顶点坐标为（Xi ， Yi ），且满
足 (|Xi|, |Yi| <= 20000)，求这个平面多边形的重心。


  解题过程：
  从第1个顶点出发，分别连接第i, i+1个顶点组成三角形Ti,1 < i < n, 
  一共n-2个三角形正好是多连形的一个划分，分别求出每个三角形的面积Si，
  总面积为各个面积相加
  根据物理学知识得：n个点(xi,yi)每个重量是mi,则重心是   
  X = (x1*M1+x2*M2+...+xn*Mn) / (M1+M2+....+Mn)   
  Y = (y1*M1+y2*M2+...+yn*Mn) / (M1+M2+....+Mn)   
  另个需要用的知识有：
  已知3点求三角形的面积，设三点分别为p[0].x, p[0].y p[1].x, p[1].y p[1].x, p[1].y
  面积s =[ p[0].x*p[1].y-p[1].x*p[0].y + p[1].x*p[2].y-p[2].x*p[1].y + p[2].x*p[0].y-p[0].x*p[2].y ] / 2 , 
  这是这3个点是逆时针的值，顺时针取负。
  已知3点求重心，x = (p[0].x+p[1].x+p[2].x)/3.0 , y = (p[0].y+p[1].y+p[2].y)/3.0 
  另外在求解的过程中，不需要考虑点的输入顺序是顺时针还是逆时针，相除后就抵消了，
  还要注意 一点是不必在求每个小三角形的重心时都除以3，可以在最后除一下
   
*/
/*fzu_1132*/
#include <stdio.h>
#include <math.h>


typedef struct TPoint
{
    double x;
    double y;
}TPoint;


double triangleArea(TPoint p0, TPoint p1, TPoint p2)
{
    //已知三角形三个顶点的坐标，求三角形的面积 
    double k = p0.x * p1.y + p1.x * p2.y
  + p2.x * p0.y - p1.x * p0.y 
  - p2.x * p1.y - p0.x * p2.y;
 //if(k >= 0) return k / 2;
// else return -k / 2;    
       return k / 2;
}


int main()
{
    int i, n, test;
 TPoint p0, p1, p2, center;
    double area, sumarea, sumx, sumy;    
    scanf("%d", &test);  
    while(test--){
  scanf("%d", &n);
  scanf("%lf%lf", &p0.x, &p0.y);
  scanf("%lf%lf", &p1.x, &p1.y);
        sumx = 0;
        sumy = 0;
        sumarea = 0;
        for(i = 2;i < n;i++){
   scanf("%lf%lf", &p2.x, &p2.y);
            center.x = p0.x + p1.x + p2.x;
            center.y = p0.y + p1.y + p2.y;  
            area =  triangleArea(p0, p1, p2);
            sumarea += area;
   sumx += center.x * area;
   sumy += center.y * area; 
   p1 = p2;           
        }
        printf("%.2lf %.2lf\n", sumx / sumarea / 3, sumy / sumarea / 3);
    }
    return 0;
}


1.16.6 存不存在一个平面把两堆点分开(poj3643)
#include <stdio.h>
struct point
{
 double x, y, z;
}pa[201], pb[201];
int main() 
{ 
 int n, m, i; 
 while (scanf("%d", &n), n != -1) 
 { 
  for (i = 0; i < n; i++) 
   scanf("%lf%lf%lf", &pa[i].x, &pa[i].y, &pa[i].z); 
  scanf("%d", &m); 
  for (i = 0; i < m; i++) 
   scanf("%lf%lf%lf", &pb[i].x, &pb[i].y, &pb[i].z);
  int cnt = 0, finish = 0; 
  double a = 0, b = 0, c = 0, d = 0; 
  while (cnt < 100000 && !finish)
  { 
   finish = 1; 
   for (i = 0; i < n; i++) 
    if (a * pa[i].x + b * pa[i].y + c * pa[i].z + d > 0) 
    { 
     a -= pa[i].x; 
     b -= pa[i].y; 
     c -= pa[i].z; 
     d -= 3; 
     finish = 0; 
    }
   for (i = 0; i < m; i++) 
    if (a * pb[i].x + b * pb[i].y + c * pb[i].z + d <= 0) 
    { 
     a += pb[i].x; 
     b += pb[i].y; 
     c += pb[i].z; 
     d += 3; 
     finish = 0; 
    }
   cnt++; 
  }
  printf("%lf %lf %lf %lf\n", a, b, c, d); 
 }
 return 0;
}

 

1.16.7 pku_3335_判断多边形的核是否存在
/*多边形的核*/
#include <stdio.h>
#include <math.h>


#define Maxn 3005
const double eps = 1e-10;


typedef struct TPodouble 
{
 double x;
 double y;
}TPoint;


typedef struct TPolygon
{
 TPoint p[Maxn];
 int n;
};


typedef struct TLine
{
 double a, b, c;
}TLine;


bool same(TPoint p1, TPoint p2)
{
 if(p1.x != p2.x) return false;
 if(p1.y != p2.y) return false;
 return true;
}
 
double multi(TPoint p1, TPoint p2, TPoint p0)
{
    //求矢量[p0, p1], [p0, p2]的叉积
    //p0是顶点 
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
    //若结果等于0，则这三点共线
    //若结果大于0，则p0p2在p0p1的逆时针方向
    //若结果小于0，则p0p2在p0p1的顺时针方向 
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    //线段所在直线,返回直线方程的三个系统 
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


TPoint LineInter(TLine l1, TLine l2)
{
    //求两直线得交点坐标
    TPoint tmp; 
    double a1 = l1.a;
    double b1 = l1.b;
    double c1 = l1.c;
    double a2 = l2.a;
    double b2 = l2.b;
    double c2 = l2.c;
    //注意这里b1 = 0 
    if(fabs(b1) < eps){
        tmp.x = -c1 / a1;  
        tmp.y = (-c2 - a2 * tmp.x) / b2;
    }       
    else{
        tmp.x = (c1 * b2 - b1 * c2) / (b1 * a2 - b2 * a1);
        tmp.y = (-c1 - a1 * tmp.x) / b1;
    }
 return tmp;
}


TPolygon Cut_polygon(TPoint p1, TPoint p2, TPolygon polygon)
{
 TPolygon new_polygon;
 TPoint interp;
 TLine l1, l2;
 int i, j;
 double t1, t2;
 new_polygon.n = 0;
 for(i = 0;i <= polygon.n - 1;i++){
  t1 = multi(p2, polygon.p[i], p1);
  t2 = multi(p2, polygon.p[i + 1], p1);
  if(fabs(t1) < eps || fabs(t2) < eps){
   if(fabs(t1) < eps) new_polygon.p[new_polygon.n++] = polygon.p[i]; 
   if(fabs(t2) < eps) new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
  }
  else if(t1 < 0 && t2 < 0){
   new_polygon.p[new_polygon.n++] = polygon.p[i]; 
   new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
  }
  else if(t1 * t2  < 0){
   l1 = lineFromSegment(p1, p2);
   l2 = lineFromSegment(polygon.p[i], polygon.p[i + 1]);
   interp = LineInter(l1, l2); 
   if(t1 < 0) {
    new_polygon.p[new_polygon.n++] = polygon.p[i];
    new_polygon.p[new_polygon.n++] = interp;
   }
   else {
    new_polygon.p[new_polygon.n++] = interp;
    new_polygon.p[new_polygon.n++] = polygon.p[i + 1];  
   }
  }
 }
 polygon.n = 0;
 if(new_polygon.n == 0) return polygon;
 polygon.p[polygon.n++] = new_polygon.p[0];
 for(i = 1;i < new_polygon.n;i++){
  if(!same(new_polygon.p[i], new_polygon.p[i - 1])){
   polygon.p[polygon.n++] = new_polygon.p[i];
  } 
 }
 if(polygon.n != 1 && same(polygon.p[polygon.n - 1], polygon.p[0])) polygon.n--;
 polygon.p[polygon.n] = polygon.p[0];
 return polygon;
}


double polygonArea(TPolygon p)
{
    //已知多边形各顶点的坐标，求其面积
    int i, n;
    double area;
    n = p.n;
    area = 0;
    for(i = 1;i <= n;i++){
        area += (p.p[i - 1].x * p.p[i % n].y - p.p[i % n].x * p.p[i - 1].y);
    }  
 return area / 2;  
}


void ChangeClockwise(TPolygon &polygon)
{
 TPoint tmp;
 int i;
 for(i = 0;i <= (polygon.n - 1) / 2;i++){
  tmp = polygon.p[i];
  polygon.p[i] = polygon.p[polygon.n - 1 - i];
  polygon.p[polygon.n - 1 - i] = tmp;   
 }
}


int main()
{
 int test, i, j;
 double area;
 TPolygon polygon, new_polygon;
 scanf("%d", &test);
 while(test--){
  scanf("%d", &polygon.n);
  for(i = 0;i <= polygon.n - 1;i++){
   scanf("%lf%lf", &polygon.p[i].x, &polygon.p[i].y);
  }
  /*若是逆时针转化为顺时针*/
  if(polygonArea(polygon) > 0) ChangeClockwise(polygon);
  polygon.p[polygon.n] = polygon.p[0];
  new_polygon = polygon;
  for(i = 0;i <= polygon.n - 1;i++){
   new_polygon = Cut_polygon(polygon.p[i], polygon.p[i + 1], new_polygon);
  } 
  area = polygonArea(new_polygon);
  if(area < 0) printf("%.2lf\n", -area);
  else printf("%.2lf\n", area);
 }
 return 0; 
}


//是否存在


#include <stdio.h>
#include <math.h>


#define Maxn 3005
const double eps = 1e-10;


typedef struct TPodouble 
{
 double x;
 double y;
}TPoint;


typedef struct TPolygon
{
 TPoint p[Maxn];
 int n;
};


typedef struct TLine
{
 double a, b, c;
}TLine;


bool same(TPoint p1, TPoint p2)
{
 if(p1.x != p2.x) return false;
 if(p1.y != p2.y) return false;
 return true;
}
 
double multi(TPoint p1, TPoint p2, TPoint p0)
{
    //求矢量[p0, p1], [p0, p2]的叉积
    //p0是顶点 
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
    //若结果等于0，则这三点共线
    //若结果大于0，则p0p2在p0p1的逆时针方向
    //若结果小于0，则p0p2在p0p1的顺时针方向 
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    //线段所在直线,返回直线方程的三个系统 
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


TPoint LineInter(TLine l1, TLine l2)
{
    //求两直线得交点坐标
    TPoint tmp; 
    double a1 = l1.a;
    double b1 = l1.b;
    double c1 = l1.c;
    double a2 = l2.a;
    double b2 = l2.b;
    double c2 = l2.c;
    //注意这里b1 = 0 
    if(fabs(b1) < eps){
        tmp.x = -c1 / a1;  
        tmp.y = (-c2 - a2 * tmp.x) / b2;
    }       
    else{
        tmp.x = (c1 * b2 - b1 * c2) / (b1 * a2 - b2 * a1);
        tmp.y = (-c1 - a1 * tmp.x) / b1;
    }
 return tmp;
}


TPolygon Cut_polygon(TPoint p1, TPoint p2, TPolygon polygon)
{
 TPolygon new_polygon;
 TPoint interp;
 TLine l1, l2;
 int i, j;
 double t1, t2;
 new_polygon.n = 0;
 for(i = 0;i <= polygon.n - 1;i++){
  t1 = multi(p2, polygon.p[i], p1);
  t2 = multi(p2, polygon.p[i + 1], p1);
  if(fabs(t1) < eps || fabs(t2) < eps){
   if(fabs(t1) < eps) new_polygon.p[new_polygon.n++] = polygon.p[i]; 
   if(fabs(t2) < eps) new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
  }
  else if(t1 < 0 && t2 < 0){
   new_polygon.p[new_polygon.n++] = polygon.p[i]; 
   new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
  }
  else if(t1 * t2  < 0){
   l1 = lineFromSegment(p1, p2);
   l2 = lineFromSegment(polygon.p[i], polygon.p[i + 1]);
   interp = LineInter(l1, l2); 
   if(t1 < 0) {
    new_polygon.p[new_polygon.n++] = polygon.p[i];
    new_polygon.p[new_polygon.n++] = interp;
   }
   else {
    new_polygon.p[new_polygon.n++] = interp;
    new_polygon.p[new_polygon.n++] = polygon.p[i + 1];  
   }
  }
 }
 polygon.n = 0;
 if(new_polygon.n == 0) return polygon;
 polygon.p[polygon.n++] = new_polygon.p[0];
 for(i = 1;i < new_polygon.n;i++){
  if(!same(new_polygon.p[i], new_polygon.p[i - 1])){
   polygon.p[polygon.n++] = new_polygon.p[i];
  } 
 }
 if(polygon.n != 1 && same(polygon.p[polygon.n - 1], polygon.p[0])) polygon.n--;
 polygon.p[polygon.n] = polygon.p[0];
 return polygon;
}


void ChangeClockwise(TPolygon &polygon)
{
 TPoint tmp;
 int i;
 for(i = 0;i <= (polygon.n - 1) / 2;i++){
  tmp = polygon.p[i];
  polygon.p[i] = polygon.p[polygon.n - 1 - i];
  polygon.p[polygon.n - 1 - i] = tmp;   
 }
}


double polygonArea(TPolygon p)
{
    //已知多边形各顶点的坐标，求其面积
    double area;
    int i, n;
    n = p.n;
    area = 0;
    for(i = 1;i <= n;i++){
        area += (p.p[i - 1].x * p.p[i % n].y - p.p[i % n].x * p.p[i - 1].y);
    }  
    return area / 2;   
}


int main()
{
 int i, j;
 TPolygon polygon, new_polygon;
 while(scanf("%d", &polygon.n) && polygon.n){
  for(i = 0;i <= polygon.n - 1;i++){
   scanf("%lf%lf", &polygon.p[i].x, &polygon.p[i].y);
  }
  /*若是逆时针转化为顺时针*/
  if(polygonArea(polygon) > 0) ChangeClockwise(polygon);  
  polygon.p[polygon.n] = polygon.p[0];
  new_polygon = polygon;
  for(i = 0;i <= polygon.n - 1;i++){
   new_polygon = Cut_polygon(polygon.p[i], polygon.p[i + 1], new_polygon);
  }
  if(new_polygon.n > 0) printf("1\n");
  else printf("0\n"); 
 }
 return 0; 
}

 


1.16.8 pku_2600_二分+圆的参数方程
#include <stdio.h>
#include <math.h>


const double eps = 1e-4;
const double pi = acos(-1.0);


struct TPoint 
{
 double x, y;
}p[60], a[60];
double angle[60];


double multi(TPoint p1, TPoint p2, TPoint p0)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}


TPoint fine_a2(TPoint a1, TPoint m, double angle1)
{
 TPoint a2;
 double r, angle2, angle3;
 r = sqrt((a1.x - m.x) * (a1.x - m.x) + (a1.y - m.y) * (a1.y - m.y));
 angle2 = acos((a1.x - m.x) / r);
 if(a1.y < m.y) {
  if(angle2 <= pi / 2) angle2 = -angle2;
  if(angle2 > pi / 2) angle2 = 3 * pi / 2 - (angle2 - pi / 2);
 }
 angle3 = angle2 - angle1;
 a2.x = m.x + r * cos(angle3);
 a2.y = m.y + r * sin(angle3);
 if(multi(m, a2, a1) < 0) return a2;
    angle3 = angle2 + angle1;
 a2.x = m.x + r * cos(angle3);
 a2.y = m.y + r * sin(angle3);
 if(multi(m, a2, a1) < 0) return a2; 
}


int main()
{
 int n, i, j;
 while(scanf("%d", &n) != EOF){
  for(i = 0;i < n;i++){
   scanf("%lf%lf", &p[i].x, &p[i].y);
  }
  for(i = 0;i < n;i++){
   scanf("%lf", &angle[i]);
   angle[i] = angle[i] * pi / 180;
  }
  a[0].x = 0;
  a[0].y = 0;
  while(1){
   for(i = 1;i <= n;i++){
    a[i] = fine_a2(a[i - 1], p[i - 1], angle[i - 1]);
   }
   if(fabs(a[n].x - a[0].x) <= eps  
     && fabs(a[n].y - a[0].y) <= eps) break;
   else {
    a[0].x = (a[0].x + a[n].x) / 2;
    a[0].y = (a[0].y + a[n].y) / 2;
   }
  }
  for(i = 0;i < n;i++){
   printf("%.0lf %.0lf\n", a[i].x, a[i].y);
  }  
 }
 return 0;
}
1.16.9 pku_1151_矩形相交的面积
/*
大牛的思想 
题目给出 n 个矩形，要求它们的面积并。具体做法是离散化。
先把 2n 个 x 坐标排序去重，然后再把所有水平线段（
要记录是矩形上边还是下边）按 y 坐标排序。
最后对于每一小段区间 (x[i], x[i + 1]) 扫描所有的水平线段，
求出这些水平线段在小区间内覆盖的面积。总的时间复杂度是 O(n^2)。
利用线段树，可以优化到 O(nlogn)。
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define up  1
#define down -1

 


typedef struct TSeg
{
 double l, r;
 double y;
 int UpOrDown;
}TSeg;
TSeg seg[210];
int segn;
double x[210];
int xn;


int cmp1(const void *a, const void *b)
{
 if(*(double *)a < *(double *)b) return -1;
 else return 1;
}


int cmp2(const void *a, const void *b)
{
 TSeg *c = (TSeg *)a;
 TSeg *d = (TSeg *)b;
 if(c->y < d->y) return -1;
 else return 1;
}


void movex(int t, int &xn)
{
 int i;
 for(i = t;i <= xn - 1;i++){
  x[i] = x[i + 1];
 }
 xn--;
}


int main()
{
 //freopen("in.in", "r", stdin);
 //freopen("out.out", "w", stdout);
 int n, i, j, cnt, test = 1;
 double x1, y1, x2, y2, ylow, area;
 while(scanf("%d", &n) != EOF && n){
  xn = 0;
  segn = 0;  
  for(i = 0;i < n;i++){
   scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
   x[xn++] = x1;
   x[xn++] = x2;
   seg[segn].l = x1;
   seg[segn].r = x2;  
   seg[segn].y = y1;
   seg[segn++].UpOrDown = up;
   seg[segn].l = x1;
   seg[segn].r = x2;
   seg[segn].y = y2;
   seg[segn++].UpOrDown = down;   
  }
  qsort(x, xn, sizeof(x[0]), cmp1);
  /*除掉重复的x*/
  for(i = 1;i < xn;){
   if(x[i] == x[i - 1]) movex(i, xn);
   else i++;
  }
  qsort(seg, segn, sizeof(seg[0]), cmp2); 
  area = 0.0;
  for(i = 0;i < xn - 1;i++){
   cnt = 0;  
   for(j = 0;j < segn;j++){
    if(seg[j].l <= x[i] && seg[j].r >= x[i + 1]){
     if(cnt == 0) ylow = seg[j].y;
     if(seg[j].UpOrDown == down) cnt++;
     else cnt--;
     if(cnt == 0) area += (x[i + 1] - x[i]) * (seg[j].y - ylow);     
    }
   }
  }
  printf("Test case #%d\n", test++);
        printf("Total explored area: %.2lf\n", area);   
 }
 return 0;
}


1.16.10 pku_1118_共线最多的点的个数
/*
2617120 chenhaifeng 1118 Accepted 512K 1890MS C++ 977B 2007-09-04 18:43:26 
直接O(n^3)超时，用一个标记数组，标记i,j所做直线已经查找过，可以跳过


大牛的思想
朴素做法是 O(n3) 的，超时。我的做法是枚举每个点，
然后求其它点和它连线的斜率，再排序。这样就得到经过
该点的直线最多能经过几个点。求个最大值就行了。复
杂度是 O(n2logn) 的。把排序换成 hash，
可以优化到 O(n2)。 
2617134 chenhaifeng 1118 Accepted 276K 312MS G++ 1394B 2007-09-04 18:49:08 
*/
#include <stdio.h>
#include <math.h>


bool f[705][705];
int a[705];


int main()
{
 int n, i, j, s, num, maxn;
 int x[705], y[705];
 int t, m;


 
 while(scanf("%d", &n) != EOF && n){
  for(i = 0;i <= n - 1;i++){
   scanf("%d%d", &x[i], &y[i]);
  }
  maxn = -1;
  for(i = 0;i <= n - 1;i++){
   for(j = i;j <= n - 1;j++){
    f[i][j] = false;
   }
  }
  for(i = 0;i <= n - 1;i++){
   for(j = i + 1;j <= n - 1;j++){
    if(f[i][j] == true) continue;
    if(n - j < maxn) break;
    num = 2;
    t = 2;
    a[0] = i;
    a[1] = j;
    f[i][j] = true; 
    for(s = j + 1;s <= n - 1;s++){
     if(f[i][s] == true || f[j][s] == true) continue;
     if((y[i] - y[s]) * (x[j] - x[s]) == (x[i] - x[s]) * (y[j] - y[s])){
       num++; 
       a[t] = s;
       for(m = 0;m <= t - 1;m++){
        f[m][s] = true;
      }
      t++; 
     }     
    }
    if(num > maxn) maxn = num; 
   }   
  }
  printf("%d\n", maxn);   
 }
 return 0;
}

 


1.16.11 pku2826_线段围成的区域可储水量
/*
两条线不相交，
左边或右边的口被遮住，
交点是某条线的那个纵坐标较高的那点
某条线段水平放置
*/
#include <stdio.h>
#include <math.h>


#define eps 1e-8


struct TPoint
{
 double x, y;
};
struct TLine
{
    double a, b, c;
};


int same(TPoint p1, TPoint p2)
{
 if(fabs(p1.x - p2.x) > eps) return 0;
 if(fabs(p1.y - p2.y) > eps) return 0;
 return 1;
}


double min(double x, double y)
{
    if(x < y) return x;
    else return y; 
}


double max(double x, double y)
{
    if(x > y) return x;
    else return y; 
}


double multi(TPoint p1, TPoint p2, TPoint p0)
{ 
    return (p1.x - p0.x) * (p2.y - p0.y) 
      - (p2.x - p0.x) * (p1.y - p0.y);
}


bool isIntersected(TPoint s1, TPoint e1, TPoint s2, TPoint e2)
{
    if(
    (max(s1.x, e1.x) >= min(s2.x, e2.x)) &&
    (max(s2.x, e2.x) >= min(s1.x, e1.x)) &&
    (max(s1.y, e1.y) >= min(s2.y, e2.y)) &&
    (max(s2.y, e2.y) >= min(s1.y, e1.y)) &&
    (multi(s2, e1, s1) * multi(e1, e2, s1) >= 0) &&
    (multi(s1, e2, s2) * multi(e2, e1, s2) >= 0)
    )  return true;
    
    return false;    
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


TPoint LineInter(TLine l1, TLine l2)
{
    TPoint tmp; 
    double a1 = l1.a;
    double b1 = l1.b;
    double c1 = l1.c;
    double a2 = l2.a;
    double b2 = l2.b;
    double c2 = l2.c;
    if(fabs(b1) < eps){
        tmp.x = -c1 / a1;  
        tmp.y = (-c2 - a2 * tmp.x) / b2;
    }       
    else{
        tmp.x = (c1 * b2 - b1 * c2) / (b1 * a2 - b2 * a1);
        tmp.y = (-c1 - a1 * tmp.x) / b1;
    }
 return tmp;
}


double triangleArea(TPoint p1, TPoint p2, TPoint p3)
{
 TPoint p4, p5;
 p4.x = p2.x - p1.x;
 p4.y = p2.y - p1.y;
 p5.x = p3.x - p1.x;
 p5.y = p3.y - p1.y;
 return fabs(p5.x * p4.y - p5.y * p4.x) / 2; 
}


double find_x(double y, TLine line)
{
 return (-line.c - line.b * y) / line.a;
}


double find_y(double x, TLine line)
{
 if(fabs(line.b) < eps)
 {
  return -1e250;
 }
 else 
 {
  return (-line.c - line.a  * x) / line.b;
 }
}


int main()
{
 //freopen("in.in", "r", stdin);
 //freopen("out.out", "w", stdout);
 int test;
 double miny, y;
 TLine l1, l2;
 TPoint p1, p2, p3, p4, inter;
 TPoint tp1, tp2;
 scanf("%d", &test);
 while(test--)
 {
  scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, 
  &p2.x, &p2.y, &p3.x, &p3.y, &p4.x, &p4.y);
  if(same(p1, p2) || same(p3, p4) 
     || !isIntersected(p1, p2, p3, p4)
     || fabs(p1.y - p2.y) < eps //平行与x轴 
     || fabs(p3.y - p4.y) < eps
    )
  {
   printf("0.00\n");
   continue;
  }
  l1 = lineFromSegment(p1, p2);
  l2 = lineFromSegment(p3, p4);
  inter = LineInter(l1, l2);
  if(p1.y > p2.y) tp1 = p1;
  else tp1 = p2;
  if(p3.y > p4.y) tp2 = p3;
  else tp2 = p4;
  if(tp1.y < tp2.y)
  {
   if(tp1.x >= min(p4.x, p3.x) && tp1.x <= max(p4.x, p3.x))
   {
    y = find_y(tp1.x, l2);
    if(y >= tp1.y)
    {
     printf("0.00\n");
     continue;
    } 
   }
   miny = tp1.y;
  }
  else
  {
   if(tp2.x >= min(p1.x, p2.x) && tp2.x <= max(p1.x, p2.x))
   {
    y = find_y(tp2.x, l1);
    if(y >= tp2.y)
    {
     printf("0.00\n");
     continue;
    } 
   }
   miny = tp2.y;
  }
  if(fabs(miny - inter.y) < eps)
  {
   printf("0.00\n");
   continue;   
  }
  tp1.x = find_x(miny, l1);
  tp2.x = find_x(miny, l2);
  tp1.y = tp2.y = miny;
  printf("%.2lf\n", triangleArea(tp1, tp2, inter)); 
 } 
 return 0;
}


1.16.12 Pick公式
//A = b / 2 + i -1  其中 b 与 i 分別表示在边界上及內部的格子点之个數
//http://www.hwp.idv.tw/bbs1/htm/%A6V%B6q%B7L%BFn%A4%C0/%A6V%B6q%B7L%BFn%A4%C0.htm
// http://acm.pku.edu.cn/JudgeOnline/problem?id=2954


#include <stdio.h>
#include <stdlib.h>


typedef struct TPoint
{
 int x;
 int y;
}TPoint;


typedef struct TLine
{
 int a, b, c;
}TLine;


int triangleArea(TPoint p1, TPoint p2, TPoint p3)
{
    //已知三角形三个顶点的坐标，求三角形的面积 
    int k = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y
      - p2.x * p1.y - p3.x * p2.y - p1.x * p3.y;  
    if(k < 0) return -k;
    else return k;
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    //线段所在直线,返回直线方程的三个系统 
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


void swap(int &a, int &b)
{
 int t;
 t = a;
 a = b;
 b = t;
}


int Count(TPoint p1, TPoint p2)
{
 int i, sum = 0, y;
 TLine l1 =  lineFromSegment(p1, p2);
 if(l1.b == 0) return abs(p2.y - p1.y) + 1;
 if(p1.x > p2.x) swap(p1.x, p2.x); //这里没有交换WA两次 
 for(i = p1.x;i <= p2.x;i++){
  y = -l1.c - l1.a * i;
  if(y % l1.b == 0) sum++;
 }
 return sum; 
}


int main()
{
  //freopen("in.in", "r", stdin);
 //freopen("OUT.out", "w", stdout);
 TPoint p1, p2, p3;
 while(scanf("%d%d%d%d%d%d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y) != EOF){
  if(p1.x == 0 && p1.y == 0 && p2.x == 0 && p2.y == 0 && p3.x == 0 && p3.y == 0) break;
  int  A = triangleArea(p1, p2, p3);//A为面积的两倍 
  int b = 0;
  int i;
  b = Count(p1, p2) + Count(p1, p3) + Count(p3, p2) - 3;//3个顶点多各多加了一次 
  //i = A / 2- b / 2 + 1;
  i = (A - b) / 2 + 1;
  printf("%d\n", i); 
 } 
 return 0; 
}


1.16.13 N点中三个点组成三角形面积最大
//Rotating Calipers algorithm

 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MaxNode 50005


int stack[MaxNode];
int top;
double max;


typedef struct TPoint
{
    int x;
    int y;
}TPoint;
TPoint point[MaxNode];


void swap(TPoint point[], int i, int j)
{
    TPoint tmp;
    tmp = point[i];
    point[i] = point[j];
    point[j] = tmp;
}


double multi(TPoint p1, TPoint p2, TPoint p0)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}


double distance(TPoint p1, TPoint p2)
{
 return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}


int cmp(const void *a, const void *b)
{
    TPoint *c = (TPoint *)a;
    TPoint *d = (TPoint *)b;
    double k = multi(*c, *d, point[0]);
    if(k< 0) return 1;
    else if(k == 0 && distance(*c, point[0]) >= distance(*d, point[0]))  
         return 1;
    else return -1;   
}


void grahamScan(int n)
{ 
    //Graham扫描求凸包
    int i, u; 
    
    //将最左下的点调整到p[0]的位置
    u = 0;
    for(i = 1;i <= n - 1;i++){
        if((point[i].y < point[u].y) || 
       (point[i].y == point[u].y && point[i].x  < point[u].x))
   u = i;      
    } 
    swap(point, 0, u);
    
    //将平p[1]到p[n - 1]按按极角排序，可采用快速排序
    qsort(point + 1, n - 1, sizeof(point[0]), cmp);
    
    for(i = 0;i <= 2;i++) stack[i] = i;
    top = 2;
    for(i = 3;i <= n - 1;i++){
        while(multi(point[i], point[stack[top]], point[stack[top - 1]]) >= 0){
   top--;
   if(top == 0) break;
        }
        top++;
        stack[top] = i;
    }
}


int main()
{    
    double triangleArea(int i, int j, int k);
    void PloygonTriangle();
    int i, n;
    while(scanf("%d", &n) && n != -1){
        for(i = 0;i < n;i++)
   scanf("%d%d", &point[i].x, &point[i].y);
        if(n <= 2){
   printf("0.00\n");
            continue;      
        }
        if(n == 3){
            printf("%.2lf\n", triangleArea(0, 1, 2));
            continue; 
        }
        grahamScan(n);
        PloygonTriangle(); 
        printf("%.2lf\n", max);    
    }
    return 0;
}


void PloygonTriangle()
{
    double triangleArea(int i, int j, int k);
    int i, j , k;
    double area, area1;
    max = -1;
 for(i = 0;i <= top - 2;i++){ 
  k = -1;
  for(j = i + 1; j <= top - 1;j++){ 
   if(k <= j) k= j + 1;
   area = triangleArea(stack[i], stack[j], stack[k]);
   if(area > max) max = area;
   while(k + 1 <= top){
    area1= triangleArea(stack[i], stack[j], stack[k + 1]);
    if(area1 < area) break;
    if(area1 > max) max = area1;
    area = area1;
    k++;
   }
  }
 }
}


double triangleArea(int i, int j, int k)
{
    //已知三角形三个顶点的坐标，求三角形的面积 
    double l = fabs(point[i].x * point[j].y + point[j].x * point[k].y 
  + point[k].x * point[i].y - point[j].x * point[i].y 
  - point[k].x * point[j].y - point[i].x * point[k].y) / 2;  
    return l;
}

 


1.16.14 直线关于圆的反射
/*
fzu_1035
1.直线和圆的交点 
2.点关于线的对称点
3.点到线的距离 
4.直线方程 
*/
#include <iostream>


#include <cmath>


using namespace std;


#define INF 999999999
const double eps = 1e-6;


int up;


typedef struct TPoint
{
    double x;
    double y;
}TPoint;


typedef struct TCircle
{
    TPoint center;
    double r;
}TCircle;


typedef struct TLine
{
    //直线标准式中的系数 
    double a, b, c;
}TLine;


void SloveLine(TLine &line, TPoint start, TPoint dir)
{
    //根据直线上一点和直线的方向求直线的方程 
    if(dir.x == 0){
        line.a = 1;
        line.b = 0;
        line.c = start.x;
    }
    else {
        double k = dir.y / dir.x;
        line.a = k;
        line.b = -1;
        line.c = start.y - k * start.x;        
    }    
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    //线段所在直线,返回直线方程的三个系统 
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


TPoint symmetricalPointofLine(TPoint p, TLine L)
{
    //p点关于直线L的对称点 
    TPoint p2;
    double d;
    d = L.a * L.a + L.b * L.b;
    p2.x = (L.b * L.b * p.x - L.a * L.a * p.x - 
            2 * L.a * L.b * p.y - 2 * L.a * L.c) / d;
    p2.y = (L.a * L.a * p.y - L.b * L.b * p.y - 
            2 * L.a * L.b * p.x - 2 * L.b * L.c) / d;
    return p2;
}


double distanc(TPoint p1, TPoint p2)
{
    //计算平面上两个点之间的距离
   return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));    
}


bool samedir(TPoint dir, TPoint start, TPoint point)
{
    //判断方向 
    TPoint tmp;
    tmp.x = point.x - start.x;
    tmp.y = point.y - start.y;
    if(tmp.x != 0 && dir.x != 0){
        if(tmp.x / dir.x > 0) return true;
        else return false;
    }
    else if(tmp.y != 0 && dir.y != 0){
        if(tmp.y / dir.y > 0) return true;
        else return false; 
    }
    return true; 
}


bool Intersected(TPoint &point, TLine line, const TCircle circle[], 
     TPoint start, TPoint dir, int which)
{
    //如果圆与直线有(有效交点)交点就存放在变量point中 
 double a = line.a, b = line.b, c = line.c;
 double x0 = circle[which].center.x, y0 = circle[which].center.y;
 double r =  circle[which].r;
 //有交点，求交点 
 double x2front = b * b + a * a;
 double x1front = -2 * x0 * b * b + 2 * a * b * y0 + 2 * a * c;
 double front = x0 * x0 * b * b + y0 * y0 * b * b 
  + c * c + 2 * c * y0 * b - b * b * r * r;
 double d = x1front * x1front - 4 * x2front * front;
 TPoint p1, p2;
 bool k1, k2;
    if(fabs(d) < eps){
        //x2front不可能等于零 
       point.x = -x1front / x2front / 2;
       point.y = (-c - a * point.x) / b;
       //判断方向
       if(samedir(dir, start, point)) return true;
       else return false;
    }
    else if(d < 0) return false;
    else {
        p1.x = (-x1front + sqrt(d)) / 2 / x2front;
        p1.y = (-c - a * p1.x) / b;
        p2.x = (-x1front - sqrt(d)) / 2 / x2front;
        p2.y = (-c - a * p2.x) / b;
        k1 = samedir(dir, start, p1);
        k2 = samedir(dir, start, p2);
        if(k1 == false && k2 == false) return false;
        if(k1 == true && k2 == true){
            double dis1 = distanc(p1, start);
            double dis2 = distanc(p2, start);
            if(dis1 < dis2) point = p1;
            else point = p2;
            return true;
        }
        else if(k1 == true) point = p1;
        else point = p2;
        return true;
    } 
}


void Reflect(int &num, TCircle circle[], TPoint start, TPoint dir, int n)
{
    //反复反射 
    int i;
    TLine line;
    TPoint interpoint, newstart;
    int u;
    SloveLine(line, start, dir);
    int tag = 0;
    double mindis = INF;
    for(i = 1;i <= n;i++){
        if(i != up && Intersected(interpoint, line, circle, start, dir, i)){
            double dis = distanc(start, interpoint);
            if(dis < mindis){
                tag = 1;
                u = i;  
                mindis = dis;
                newstart = interpoint;
            }            
        }
    }
    if(tag == 0){
        cout << "inf" << endl;
        return ;
    }
    else {
        if(num == 10){
            cout << "..." << endl;
           return ;
        }
        cout << u << " "; 
        num++;
        //新的方向 
        TLine line1;
        TPoint p;
        line1 = lineFromSegment(newstart, circle[u].center);
        if(fabs(line1.a * start.x + line1.b * start.y +line1.c) <= eps){
            dir.x = -dir.x;
            dir.y = -dir.y;
        }
        else {
            p = symmetricalPointofLine(start, line1);//start的对称点 
            dir.x = p.x - newstart.x;
            dir.y = p.y - newstart.y; 
        }
        
        start = newstart;     
        up = u;
        Reflect(num, circle, start, dir, n);     
    } 
}


int main()
{
    //freopen("fzu_1035.in", "r", stdin);
    //freopen("fzu_1035.out", "w", stdout);
    int n, i, j, num, test = 1;
    TCircle circle[30];
    TPoint start, dir;
    while(cin >> n && n){
        for(i = 1;i <= n;i++){
            cin >> circle[i].center.x >> circle[i].center.y >> circle[i].r;
        }
        cin >> start.x >> start.y >> dir.x >> dir.y;
        
        cout << "Scene " << test++ << endl;


        num = 0;
        up = -1;
        Reflect(num, circle, start, dir, n);
        cout << endl;
    } 
    return 0;
}

 


1.16.15 pku2002_3432_N个点最多组成多少个正方形(hao)
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#define eps 1e-6
#define pi acos(-1.0)


#define PRIME 9991


struct point
{ 
    int x, y; 
}p[2201]; 
int n;


struct HASH
{
    int cnt;
    int next;
}hash[50000];
int hashl;


int Hash(int n)
{
    int i = n % PRIME;
    while(hash[i].next != -1){
        if(hash[hash[i].next].cnt == n) return 1;
        else if(hash[hash[i].next].cnt > n) break;
        i = hash[i].next;
    }
    hash[hashl].cnt = n;
    hash[hashl].next = hash[i].next;
    hash[i].next = hashl;
    hashl++; 
    return 0;
}


int Hash2(int n)
{
    int i = n % PRIME;
    while(hash[i].next != -1){
        if(hash[hash[i].next].cnt == n) return 1;
        else if(hash[hash[i].next].cnt > n) return 0;
        i = hash[i].next;
    }
    return 0;
}


int check(double ax, double ay, int &x, int &y)
{
    int a0 = (int)ax;
    int b0 = (int)ay;
    int tag1 = 0, tag2 = 0;   
    if(fabs(a0 - ax) < eps){
        tag1 = 1;
        x = a0;
    }
    else if(fabs(a0 + 1 - ax) < eps){
        tag1 = 1;
        x = a0 + 1;
    }
    if(fabs(b0 - ay) < eps){
        tag2 = 1;
        y = b0;
    }
    else if(fabs(b0 + 1 - ay) < eps){
        y = b0 + 1;
        tag2 = 1;
    }
    if(tag1 == 1 && tag2 == 1) return 1;
    else return 0;
}


int squares(point p1, point p2, point &p3, point &p4)
{
    double a = (double)p2.x - p1.x;
    double b = (double)p2.y - p1.y;
    double midx = ((double)p1.x + p2.x) / 2;
    double midy = ((double)p1.y + p2.y) / 2;
    double tmp = a * a + b * b;
    double x1 = sqrt(b * b) / 2;
    double y1;
    if(fabs(b) < eps) y1 = sqrt(a * a + b * b) / 2;
    else y1 = -a * x1 / b;
    x1 += midx;
    y1 += midy;
    if(check(x1, y1, p3.x, p3.y) == 0) return 0;    
    x1 = 2 * midx - x1;
    y1 = 2 * midy - y1; 
    if(check(x1, y1, p4.x, p4.y) == 0) return 0; 
    return 1;
}


int main() 
{ 
    int i, j, cnt; 
    while(scanf("%d", &n) != EOF && n)
    {
  for(i = 0;i < PRIME;i++) hash[i].next = -1;
  hashl = PRIME;
  int x1, y1, x2, y2;
  for (i = 0; i < n; i++){
   scanf("%d%d", &p[i].x, &p[i].y); 
   Hash((p[i].x + 100000) * 100000 + p[i].y + 100000);
  }   
  cnt = 0; 
  for (i = 0; i < n; i++){ 
   for (j = i + 1; j < n; j++) 
   { 
    point a, b; 
    if(squares(p[i], p[j], a, b) == 0) continue; 
    if(Hash2((a.x + 100000) * 100000 + a.y + 100000) == 0) continue;
    if(Hash2((b.x + 100000) * 100000 + b.y + 100000) == 0) continue;
    cnt++; 
   } 
  }
  printf("%d\n", cnt / 2); 
 }
    return 0; 
}

 

 


1.16.16 pku1981_单位圆覆盖最多点(poj1981)CircleandPoints
/*
平面上N个点，用一个半径R的圆去覆盖，最多能覆盖多少个点？


比较经典的题目。


对每个点以R为半径画圆，对N个圆两两求交。这一步O(N^2)。问题转化为求被覆盖次数最多的弧。


对每一个圆，求其上的每段弧重叠次数。假如A圆与B圆相交。A上[PI/3, PI/2]的区间被B覆盖(PI为圆周率)。那么对于A圆，我们在PI/3处做一个+1标记，在PI/2处做一个-1标记。


对于[PI*5/3, PI*7/3]这样横跨0点的区间只要在0点处拆成两段即可。


将一个圆上的所有标记排序，从头开始扫描。初始ans = 0，碰到+1标记给ans++，碰到-1标记ans--。扫描过程中ans的最大值就是圆上被覆盖最多的弧。求所有圆的ans的最大值就是答案。


总复杂度O(N^2 * logN)


*/#include <stdio.h>
#include <math.h>


#define eps 1e-6


struct point 
{
 double x, y;
};


double dis(point p1, point p2)
{
 point p3;
 p3.x = p2.x - p1.x;
 p3.y = p2.y - p1.y;
 return p3.x * p3.x + p3.y * p3.y;
}


point find_centre(point p1, point p2)
{
 point p3, mid, centre;
 double b, c, ang;
 p3.x = p2.x - p1.x;
 p3.y = p2.y - p1.y;
 mid.x = (p1.x + p2.x) / 2;
 mid.y = (p1.y + p2.y) / 2;  
 b = dis(p1, mid);
 c = sqrt(1 - b);
 if(fabs(p3.y) < eps)//垂线的斜角90度
 {
  centre.x = mid.x;
  centre.y = mid.y + c;
 }
 else 
 {
  ang = atan(-p3.x / p3.y);
  centre.x = mid.x + c * cos(ang);
  centre.y = mid.y + c * sin(ang);
 }
 return centre; 
}


int main()
{
    int n, ans, tmpans, i, j, k;
    point p[305], centre;
    double tmp;
    while(scanf("%d", &n) && n)
    {
  for(i = 0;i < n;i++)
   scanf("%lf%lf", &p[i].x, &p[i].y);
  ans = 1;
  for(i = 0;i < n;i++)
   for(j = i + 1;j < n;j++)
   {
    if(dis(p[i], p[j]) > 4) continue;
    tmpans = 0;
    centre = find_centre(p[i], p[j]);
    for(k = 0;k < n;k++)
    {
     //if(tmpans + n - k <= ans) break;
     tmp = dis(centre, p[k]);
     //if(tmp < 1.0 || fabs(tmp - 1.0) < eps) tmpans++;
     if(tmp <= 1.000001) tmpans++;
    }
    if(ans < tmpans) ans = tmpans;
   }
  printf("%d\n", ans);  
    }
    return 0;
}

 


1.16.17 pku3668_GameofLine_N个点最多确定多少互不平行的直线(poj3668)
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define eps 1e-6
#define pi acos(-1)


struct point 
{
 double x, y;
};


double FindSlewRate(point p1, point p2)
{
 point p;
 p.x = p2.x - p1.x;
 p.y = p2.y - p1.y;
 if(fabs(p.x) < eps) return pi / 2;
 double tmp = atan(p.y / p.x);
 if(tmp < 0) return pi + tmp;
 return tmp;
}


int cmp(const void *a, const void *b)
{
 double *c = (double *)a;
 double *d = (double *)b;
 if(*c < *d) return -1;
 return 1;
}


int main()
{
 int n, rt;
 point p[205];
 double rate[40005];
 while(scanf("%d", &n) != EOF)
 {
  for(int i = 0;i < n;i++)
   scanf("%lf%lf", &p[i].x ,&p[i].y);
  rt = 0;
  for(int i = 0;i < n;i++)
   for(int j = i + 1;j < n;j++)
    rate[rt++] = FindSlewRate(p[i], p[j]);
  qsort(rate, rt, sizeof(rate[0]), cmp); 
  int ans = 1;
  for(int i = 1;i < rt;i++)
   if(rate[i] > rate[i - 1]) ans++;
  //注意这里写fabs(rate[i] - rate[i - 1]) > eps Wrong Answer 
  printf("%d\n", ans);
 } 
 return 0;
}


1.16.18 求凸多边形直径
#include<stdio.h> 
#include<math.h>


#define eps 1e-6 
#define MaX 6000


/*-----------多边形结构------------*/ 
struct POLYGON{ 
   int n;                                  //多边形顶点数 
   double x[MaX],y[MaX];        //顶点坐标 
}poly;


int zd[100000][2],znum;      //跖对的集合和跖对的数量

 


/*------------辅助函数-----------*/ 
double dist(int a,int b,int c) 
{ 
   double vx1,vx2,vy1,vy2; 
   vx1=poly.x[b]-poly.x[a]; vy1=poly.y[b]-poly.y[a]; 
   vx2=poly.x[c]-poly.x[a]; vy2=poly.y[c]-poly.y[a]; 
   return fabs(vx1*vy2 - vy1*vx2); 
}

 


/*-------------求凸多边形直径的函数-------------*/ 
double DIAMETER() 
{ 
   znum=0; 
   int i,j,k=1; 
   double m,tmp; 
   while(dist(poly.n-1,0,k+1) > dist(poly.n-1,0,k)+eps) 
      k++; 
   i=0; j=k; 
   while(i<=k && j<poly.n) 
   { 
      zd[znum][0]=i; zd[znum++][1]=j; 
      while(dist(i,i+1,j+1)>dist(i,i+1,j)-eps && j<poly.n-1) 
      { 
         zd[znum][0]=i; zd[znum++][1]=j; 
         j++; 
      } 
      i++; 
   } 
   m=-1; 
   for(i=0;i<znum;i++) 
   { 
      tmp =(poly.x[zd[i][0]]-poly.x[zd[i][1]]) * (poly.x[zd[i][0]]-poly.x[zd[i][1]]); 
      tmp+=(poly.y[zd[i][0]]-poly.y[zd[i][1]]) * (poly.y[zd[i][0]]-poly.y[zd[i][1]]); 
      if(m<tmp) m=tmp; 
   } 
   return sqrt(m); 
}


/*----------主函数----------*/ 
int main() 
{ 
   int i; 
   while(scanf("%d",&poly.n)==1) 
   { 
      for(i=0;i<poly.n;i++) 
         scanf("%lf %lf",&poly.x[i],&poly.y[i]); 
      printf("%.3lf\n",DIAMETER()); 
   } 
   return 0; 
}
1.16.19 矩形面积并，周长并
见附录一5.11,5.12
1.16.20 pku2069 最小球覆盖 
见附录一5.13,5.14
//最小闭合球
#include<stdio.h>
#include<math.h>
#include<memory>
#include<stdlib.h>
using namespace std;
const double eps = 1e-10;
struct point_type { double x, y, z; };
int npoint, nouter ;
point_type point [1000], outer[4], res;
double radius, tmp ;


inline double dist(point_type p1 , point_type p2)
{
double dx=p1.x-p2.x, dy=p1.y-p2.y,dz=p1.z-p2.z ;
return ( dx*dx + dy*dy + dz*dz ) ;
}


inline double dot( point_type p1 , point_type p2 )
{
return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}


void ball()
{
 point_type q[3]; 
 double m[3][3],sol[3],L[3],det; int i,j;
 res.x=res.y=res.z=-1000;
 radius=0;
    switch ( nouter ) 
  {
  case 1 : res=outer[0]; break;
  case 2 :
     res.x=(outer[0].x+outer[1].x)/2;
     res.y=(outer[0].y+outer[1].y)/2;
     res.z=(outer[0].z+outer[1].z)/2;
     radius=dist(res,outer[0]);
     break;
  case 3 :
     for ( i=0; i<2; ++i ) {
     q[i].x=outer[i+1].x-outer[0].x;
     q[i].y=outer[i+1].y-outer[0].y;
     q[i].z=outer[i+1].z-outer[0].z;
     }
     for ( i=0; i<2; ++i )
      for ( j=0; j<2; ++j )
      m[i][j]=dot(q[i],q[j])*2 ;
     for ( i=0; i<2; ++i ) sol[i]=dot(q[i],q[i]);
     if (fabs(det=m[0][0]*m[1][1]-m[0][1]*m[1][0]) < eps ) return ;
     
     L[0]=(sol[0]*m[1][1]-sol[1]*m[0][1])/det;
     L[1]=(sol[1]*m[0][0]-sol[0]*m[1][0])/det;
     res.x=outer[0].x+q[0].x*L[0]+q[1].x*L[1];
     res.y=outer[0].y+q[0].y*L[0]+q[1].y*L[1];
     res.z=outer[0].z+q[0].z*L[0]+q[1].z*L[1];
     radius=dist(res,outer[0]);
     break;
  case 4 :
     for ( i=0; i<3; ++i ){
     q[i].x=outer[i+1].x-outer[0].x;
     q[i].y=outer[i+1].y-outer[0].y;
     q[i].z=outer[i+1].z-outer[0].z;
     sol[i]=dot(q[i],q[i]);
     }
     for ( i=0; i<3; ++i) 
      for ( j=0; j<3; ++j) m[i][j]=dot(q[i],q[j])*2;
     det= m[0][0]*m[1][1]*m[2][2] + m[0][1]*m[1][2]*m[2][0]
      +m[0][2]*m[2][1]*m[1][0] - m[0][2]*m[1][1]*m[2][0]
      -m[0][1]*m[1][0]*m[2][2] - m[0][0]*m[1][2]*m[2][1];


     if ( fabs( det )<eps ) return;


     for ( j=0; j<3; ++j ){
     for ( i=0; i<3; ++i ) m[i][j]=sol[i];
      L[j]=( m[0][0]*m[1][1]*m[2][2] + m[0][1]*m[1][2]*m[2][0]
        + m[0][2]*m[2][1]*m[1][0] - m[0][2]*m[1][1]*m[2][0]
        - m[0][1]*m[1][0]*m[2][2] - m[0][0]*m[1][2]*m[2][1]
        ) / det;
     for( i=0; i<3; ++i ) m[i][j]=dot(q[i],q[j])*2;
     }
     res=outer[0];
     for ( i=0; i<3; ++i ) {
     res.x+=q[i].x*L[i];
        res.y+=q[i].y*L[i];
     res.z+=q[i].z*L[i];
     }
     radius=dist(res,outer[0]);
  }
}


void minball(int n)
{
  ball();
  if ( nouter <4 )
       for ( int i=0; i<n; ++i )
           if( dist(res,point[i])-radius>eps)
      {
    outer[nouter]=point[i];
                ++nouter;
    minball(i);
    --nouter;
    if(i>0)
    {
      point_type Tt = point[i] ;
      memmove(&point[1], &point[0] , sizeof ( point_type )*i );
      point[0]=Tt;
    }
   }
}

 

 


int main()
{
 int i;
 while(scanf("%d",&npoint)!=EOF,npoint)
 {
  for(i=0;i<npoint;i++)
       scanf("%lf%lf%lf",&point[i].x,&point[i].y,&point[i].z);
  nouter=0; 
  minball(npoint);
  printf("%.8lf\n",sqrt(radius)+eps);
 }
 return 0;
}


1.16.21 最大空凸包、最大空矩形
见附录一5.7, 6.15

1.16.22 求圆和多边形的交
/*圆和简单多边形*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#define M 30
#define eps 1e-7
const double PI = acos(-1.0);


class pnt_type
{
public:
 double x,y;
};
class state_type
{
public:
 double angle;
 double CoverArea;
};


pnt_type pnt[M];
pnt_type center;


int n;
double R;


bool read_data()
{
 n = 3;
 int i;
 if (cin >> pnt[1].x >> pnt[1].y)
 {
  for (i=2;i<=n;i++) cin >> pnt[i].x >> pnt[i].y;
  cin >> center.x >> center.y >> R;
  return true;
 }
 return false;
}
inline double Area2(pnt_type &a,pnt_type &b,pnt_type &c)
{
 return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
inline double dot(pnt_type &a,pnt_type &b,pnt_type &c)
{
 return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}
inline double dist(pnt_type &a,pnt_type &b)
{
 return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}


void init()
{
 int i;
 double temp,sum;
 for (i=2;i<n;i++)
 {
  temp = Area2(pnt[1],pnt[i],pnt[i + 1]);
  sum += temp;
 }
 if (sum < 0) reverse(pnt + 1,pnt + n + 1);
 pnt[n + 1] = pnt[1];
}


inline bool inCircle(pnt_type &s)
{
 return dist(center,s) <= R;
}


bool SameSide(pnt_type a,pnt_type b)
{
 if (dist(a,center) > dist(b,center)) swap(a,b);
 return dot(a,b,center) < eps;
}


double ShadomOnCircle(pnt_type a,pnt_type b)
{
 double flag = Area2(center,a,b),res = 0;
 if (fabs(flag) < eps) return 0;


 bool ina = inCircle(a),inb = inCircle(b);
 if (ina && inb)
 {
  res = fabs(Area2(center,a,b)) / 2;
 }
 else if (!ina && !inb)
 {
  if (SameSide(a,b))
  {
   double theta = acos(dot(center,a,b) / dist(center,a) / dist(center,b));
   res = R * R * theta / 2;
  }
  else
  {
   double height = fabs(Area2(center,a,b)) / dist(a,b);
   double theta = acos(dot(center,a,b) / dist(center,a) / dist(center,b));
   if (height >= R)
   {
    res = R * R * theta / 2;
   }
   else
   {
    double _theta = 2 * acos(height / R);
    res = R * R * (theta - _theta) / 2 + R * R * sin(_theta) / 2;
   }
  }
 }
 else
 {
  if (!ina && inb) swap(a,b);
  double height = fabs(Area2(center,a,b)) / dist(a,b);
  double temp = dot(a,center,b);
  double theta = acos(dot(center,a,b) / dist(center,a) / dist(center,b)),theta1,theta2;
  if (fabs(temp) < eps)
  {
   double _theta = acos(height / R);
   res += R * height / 2 * sin(_theta);
   res += R * R / 2 * (theta - _theta);
  }
  else
  {
   theta1 = asin(height / R); theta2 = asin(height / dist(a,center));
   if (temp > 0)
   {
    res += dist(center,a) * R / 2 * sin(PI - theta1 - theta2);
    res += R * R / 2 * (theta + theta1 + theta2 - PI);
   }
   else
   {
    res += dist(center,a) * R / 2 * sin(theta2 - theta1);
    res += R * R / 2 * (theta - theta2 + theta1);
   }
  }
 }
 if (flag < 0) return -res; else return res;
}


double Cover()
{
 int i;
 double res = 0;
 for (i=1;i<=n;i++) 
  res += ShadomOnCircle(pnt[i],pnt[i + 1]);
 return res;
}


int main()
{
 double ans;
 while (read_data())
 {
  init();
  ans = Cover();
  printf("%.2lf\n",ans);
 }
 return 0;
}


半平面交
//Nlgn
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define maxn 20005
#define eps 1e-10


struct point
{double x,y;};
struct line
{point s,e;double k;};


line L[maxn];
point S[maxn];


int N,Q[maxn];


double cross(point a,point b,point c) // c在直线ab右边返回<0
{return (c.y-a.y)*(b.x-a.x)-(b.y-a.y)*(c.x-a.x);}


bool operator < (line a,line b) // 直线se右边为可行域
{
 if( fabs(a.k-b.k)<eps )
  return cross(b.s,b.e,a.s)<0;
 return a.k<b.k;
}


point intersection(point u1,point u2,point v1,point v2){
 point ret=u1;
 double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
  /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
 ret.x+=(u2.x-u1.x)*t;
 ret.y+=(u2.y-u1.y)*t;
 return ret;
}


double HalfInSec()
{
 int i,j,k,l;
 sort(L,L+N);  // 极角[-pi,pi]排序
 
 for(i=1,j=0;i<N;i++)  // 去掉相同极角直线
  if( fabs(L[i].k-L[j].k)>eps ) 
  L[++j] = L[i];
 N = j+1;


 k = 0,l = 1;
 Q[0] = 0,Q[1] = 1;
 S[1] = intersection(L[0].s,L[0].e,L[1].s,L[1].e);
 for(i=2;i<N;i++)
 {
  while( k<l && cross(L[i].s,L[i].e,S[l])>eps ) 
   l--;
  while( k<l && cross(L[i].s,L[i].e,S[k+1])>eps ) 
   k++;
  Q[++l] = i;
  S[l] = intersection(L[Q[l-1]].s,L[Q[l-1]].e,L[i].s,L[i].e);
 }


 while( k<l && cross(L[Q[k]].s,L[Q[k]].e,S[l])>eps )
  l--;
 while( k<l && cross(L[Q[l]].s,L[Q[l]].e,S[k+1])>eps )
  k++;
 S[k] = intersection(L[Q[l]].s,L[Q[l]].e,L[Q[k]].s,L[Q[k]].e);
 S[++l] = S[k];


 double s = 0;
 for(i=k;i<l;i++)
  s += S[i].y*S[i+1].x-S[i+1].y*S[i].x;
 return fabs(s/2);
}
int main()
{
 int i,j,k,l;
 scanf("%d",&N);
 for(i=0;i<N;i++)
  scanf("%lf%lf%lf%lf",&L[i].e.x,&L[i].e.y,&L[i].s.x,&L[i].s.y);
 L[N].s.x = 0,L[N].s.y = 0;
 L[N+1].s.x = 10000,L[N+1].s.y = 0;
 L[N+2].s.x = 10000,L[N+2].s.y = 10000;
 L[N+3].s.x = 0,L[N+3].s.y = 10000;
 L[N].e = L[N+3].s;
 L[N+1].e = L[N].s;
 L[N+2].e = L[N+1].s;
 L[N+3].e = L[N+2].s;
 N += 4;
 for(i=0;i<N;i++)
  L[i].k = atan2(L[i].s.y-L[i].e.y,L[i].s.x-L[i].e.x);
 printf("%.1lf\n",HalfInSec());
}

 


//N^2
#include <iostream>
#include <math.h>
#include <string>
using namespace std;
#define maxn 2005
int N;
struct point
{
 double x, y;
}P[maxn];


double xmul(point a,point b,point c)
{return (c.y-a.y)*(b.x-a.x)-(b.y-a.y)*(c.x-a.x);}


point intersection(point u1,point u2,point v1,point v2){
 point ret=u1;
 double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
  /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
 ret.x+=(u2.x-u1.x)*t;
 ret.y+=(u2.y-u1.y)*t;
 return ret;
}


int HalfInteSec(double move)
{
 int i,j;
 point tt[maxn],tp[maxn],ns,ne;
 int len,tlen;
 len = N;
 memcpy(tp,P,sizeof(P));
 for(i=0;i<N;i++)
 {
  point s,e;
  double dx,dy;
  
  
  dx = P[i].y-P[i+1].y;dy = P[i+1].x-P[i].x;
  dx = P[i].y-P[i+1].y;dy = P[i+1].x-P[i].x;


  s.x = P[i+1].x+dx*(move/sqrt(dx*dx+dy*dy));
  s.y = P[i+1].y+dy*(move/sqrt(dx*dx+dy*dy));
  
  e.x = P[i].x+dx*(move/sqrt(dx*dx+dy*dy));
  e.y = P[i].y+dy*(move/sqrt(dx*dx+dy*dy));

 


  tlen = 0;
  for(j=0;j<len;j++)
  {
   ns = tp[j];    ne = tp[j+1];
   
   if( xmul(s,e,ns)<=0 )
    tt[tlen++] = ns;
   
   if( xmul(s,e,ns)*xmul(s,e,ne)<0 )
    tt[tlen++] = intersection(s,e,ns,ne);
  }
  tt[tlen] = tt[0];
  memcpy(tp,tt,sizeof(tt));
  len = tlen;
 }
 return len; 
}


int main()
{
 int i,j,k,l;
 while( scanf("%d",&N),N )
 {
  for(i=0;i<N;i++)
   scanf("%lf%lf",&P[i].x,&P[i].y);
  P[N] = P[0];
  double min = 0,max = 10000,mid;
  while( max-min>0.0000001 )
  {
   mid = (min+max)/2;
   l = HalfInteSec(mid);
   if( l==0 )
    max = mid;
   else
    min = mid;
  }
  printf("%.6lf\n",min);
 }
}

 