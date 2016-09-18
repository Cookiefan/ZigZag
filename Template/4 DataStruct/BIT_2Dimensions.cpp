struct bit
{
    int b[maxn][maxn];
    void add(int x,int y,int z)
    {
        for (int i=x;i<=n;i+=(i&-i))
            for (int j=y;j<=m;j+=(j&-j))
                b[i][j]+=z;
    }
    int ask(int x,int y)
    {
        int tmp=0;
        for (int i=x;i>0;i-=(i&-i))
            for (int j=y;j>0;j-=(j&-j))
                tmp+=b[i][j];
        return tmp;
    }
}s,t,l,r;
 
void ins(int x1,int y1,int x2,int y2,int z)
{
    s.add(x1,y1,z); s.add(x2+1,y1,-z); s.add(x1,y2+1,-z); s.add(x2+1,y2+1,z);
    l.add(x1,y1,z*x1); l.add(x2+1,y1,-z*(x2+1)); l.add(x1,y2+1,-z*x1); l.add(x2+1,y2+1,z*(x2+1));
    r.add(x1,y1,z*y1); r.add(x2+1,y1,-z*y1); r.add(x1,y2+1,-z*(y2+1)); r.add(x2+1,y2+1,z*(y2+1));
    t.add(x1,y1,z*x1*y1); t.add(x2+1,y1,-z*(x2+1)*y1); t.add(x1,y2+1,-z*x1*(y2+1)); t.add(x2+1,y2+1,z*(x2+1)*(y2+1));
}
 
int query(int x1,int y1,int x2,int y2)
{
    int a1=s.ask(x2,y2)*(x2+1)*(y2+1)-s.ask(x1-1,y2)*x1*(y2+1)-s.ask(x2,y1-1)*(x2+1)*y1+s.ask(x1-1,y1-1)*x1*y1;
    int a2=l.ask(x2,y2)*(y2+1)-l.ask(x1-1,y2)*(y2+1)-l.ask(x2,y1-1)*y1+l.ask(x1-1,y1-1)*y1;
    int a3=r.ask(x2,y2)*(x2+1)-r.ask(x1-1,y2)*x1-r.ask(x2,y1-1)*(x2+1)+r.ask(x1-1,y1-1)*x1;
    int a4=t.ask(x2,y2)-t.ask(x1-1,y2)-t.ask(x2,y1-1)+t.ask(x1-1,y1-1);
    return a1-a2-a3+a4;
}