#include <bits/stdc++.h>
#define maxn 3300
using namespace std;

typedef long long LL;

struct bit
{
    LL b[maxn][maxn];
    int n,m;
    void add(int x,int y,LL z)
    {
        for (int i=x;i<=n;i+=(i&-i))
            for (int j=y;j<=m;j+=(j&-j))
                b[i][j]^=z;
    }
    LL ask(int x,int y)
    {
        LL tmp=0;
        for (int i=x;i>0;i-=(i&-i))
            for (int j=y;j>0;j-=(j&-j))
                tmp^=b[i][j];
        return tmp;
    }
    void set(int x, int y)
    {
    	n=x; m=y;
    }
    void clear()
    {
    	memset(b,0,sizeof(b));
    }
}s,t,l,r;

LL mul(LL z, int k)
{
	if (k&1) return z;
	else return 0;
}
 
void ins(int x1,int y1,int x2,int y2,LL z)
{
    s.add(x1,y1,z); s.add(x2+1,y1,z); s.add(x1,y2+1,z); s.add(x2+1,y2+1,z);
    l.add(x1,y1,mul(z,x1)); l.add(x2+1,y1,mul(z,x2+1)); l.add(x1,y2+1,mul(z,x1)); l.add(x2+1,y2+1,mul(z,x2+1));
    r.add(x1,y1,mul(z,y1)); r.add(x2+1,y1,mul(z,y1)); r.add(x1,y2+1,mul(z,y2+1)); r.add(x2+1,y2+1,mul(z,y2+1));
    t.add(x1,y1,mul(z,x1*y1)); t.add(x2+1,y1,mul(z, (x2+1)*y1)); t.add(x1,y2+1,mul(z, x1*(y2+1))); t.add(x2+1,y2+1,mul(z, (x2+1)*(y2+1)));
}
 
LL query(int x1,int y1,int x2,int y2)
{
    LL a1=mul(s.ask(x2,y2),(x2+1)*(y2+1))^mul(s.ask(x1-1,y2),x1*(y2+1))^mul(s.ask(x2,y1-1),(x2+1)*y1)^mul(s.ask(x1-1,y1-1),x1*y1);
    LL a2=mul(l.ask(x2,y2),(y2+1))^mul(l.ask(x1-1,y2),(y2+1))^mul(l.ask(x2,y1-1),y1)^mul(l.ask(x1-1,y1-1),y1);
    LL a3=mul(r.ask(x2,y2),(x2+1))^mul(r.ask(x1-1,y2),x1)^mul(r.ask(x2,y1-1),(x2+1))^mul(r.ask(x1-1,y1-1),x1);
    LL a4=t.ask(x2,y2)^t.ask(x1-1,y2)^t.ask(x2,y1-1)^t.ask(x1-1,y1-1);
    //cout<<a1<<' '<<a2<<' '<<a3<<' '<<a4<<endl;
    return a1^a2^a3^a4;
}

void write(bit e)
{
	for (int i=1;i<=2;i++)
	{
		for (int j=1;j<=2;j++)
			cout<<e.b[i][j]<<' ';
		cout<<endl;
	}
}

int n,m, p;

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		char c; int xo, xe, yo , ye, k, z;
		s.set(n+1,n+1); s.clear();
		t.set(n+1,n+1); t.clear();
		l.set(n+1,n+1); l.clear();
		r.set(n+1,n+1); r.clear();
		for (int i=1;i<=m;i++)
		{
			scanf(" %c%d%d%d%d",&c,&xo,&yo,&xe,&ye);
			if (c=='P')
			{
				scanf("%d",&p);
				LL tmp=0;
				for (int j=1;j<=p;j++)
				{
					scanf("%d%d",&k, &z);
					k--;
					if (z&1)
						tmp^=(1LL<<k);
				}
				//cout<<tmp<<endl;
				ins(xo, yo, xe, ye, tmp);
				// write(s);
				// write(t);
				// write(l);
				// write(r);
			}
			else
			{
				LL tmp=query(xo, yo, xe, ye);
				for (int i=0;i<50;i++)
				{
					if ((tmp>>i)&1)
						printf("2");
					else
						printf("1");
					printf(" ");
					if (i==49) printf("\n");
				}
			}
		}
	}

	return 0;
}