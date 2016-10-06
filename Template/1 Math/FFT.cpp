//FFT
#define PI acos(-1.0)//acosl(-1.0)

typedef double LD;//long double
typedef long long LL;
//typedef complex<LD> cpx;
struct cpx
{
    LD x, y;
    cpx(LD _x=0, LD _y=0):x(_x), y(_y){}
    cpx operator +(const cpx &b)const{
    return cpx(x+b.x, y+b.y);
    }
    cpx operator -(const cpx &b)const{
        return cpx(x-b.x, y-b.y);
    }
    cpx operator *(const cpx &b)const{
        return cpx(x*b.x-y*b.y, x*b.y+y*b.x);
    }
};

int rev(int x, int n)
{
    int tmp=0;
    for (int i=n>>1;i;i>>=1,x>>=1)
        tmp=tmp<<1|x&1;
    return tmp;
}

void fft(cpx *a, int n, int flag)
{
	for (int i=0,j=i;i<n;i++,j=rev(i, n))
		if (i<j) swap(a[i], a[j]);
	for (int k=1;k<n;k<<=1)
	{
		cpx wn(cos(PI/k), flag*sin(PI/k));
		//cpx wn(cosl(PI/i), flag*sinl(PI/i));
		cpx w(1, 0);
		for (int i=0;i<k;i++,w=w*wn)
			for (int j=i;j<n;j+=(k<<1))
			{
				cpx x=a[j], y=w*a[j|k];
				a[j]=x+y;
				a[j|k]=x-y;
			}
	}
	if (flag==-1) 
		for (int i=0;i<n;i++)
			a[i].x/=n, a[i].y/=n;
}

cpx A[maxn], B[maxn];
int a[maxn], b[maxn], c[maxn];
int n;
void roll(int *a, int *b, int *c, int n, int m)
{
	int num=1;
	while (num<n+m) num<<=1;//move out if slow
	for (int i=0;i<num;i++) A[i]=(i<n?a[i]:0);
	for (int i=0;i<num;i++) B[i]=(i<m?b[i]:0);	
	fft(A, num, 1);
	fft(B, num, 1);
	for (int i=0;i<num;i++) A[i]=A[i]*B[i];
	fft(A, num, -1);
	for (int i=0;i<num;i++) c[i]=(LL)(A[i].x+0.5)%mod;
}
//黑科技卷积(精度10^12)
cpx A1[maxn<<1], B1[maxn<<1], A2[maxn<<1], B2[maxn<<1], A3[maxn<<1];
void roll(LL *a, LL *b, LL *c, int n, int m)
{
    int num=1;;
    int O=sqrt(oo);
    while (num<n+m) num<<=1;
    for (int i=0;i<num;i++)
    {
        A1[i]=(i<m?a[i]/O:0);
        A2[i]=(i<m?a[i]%O:0);
        A3[i]=0;
        B1[i]=(i<m?b[i]/O:0);
        B2[i]=(i<m?b[i]%O:0);
    }
    fft(A1,num,1);fft(A2,num,1);
    fft(B1,num,1);fft(B2,num,1);
    for (int i=0;i<num;i++)
    {
        A3[i]=A1[i]*B2[i]+A2[i]*B1[i];
        A1[i]=A1[i]*B1[i];
        A2[i]=A2[i]*B2[i];
    }
    fft(A1,num,-1);fft(A2,num,-1);fft(A3,num,-1);
    for (int i=0;i<num;i++)
    {
        LL x=(A1[i].x+0.5), y=(A2[i].x+0.5), z=(A3[i].x+0.5);
        c[i]=(x*O*O+y+z*O)%oo;
        if (i>=m)
        {
            c[i%m]=c[i%m]+c[i];
            while (c[i%m]>=oo) c[i%m]-=oo;
        }
    }
}