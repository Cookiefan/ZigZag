#include <bits/stdc++.h>
using namespace std;

struct high
{
    int e[2020];
    void clear()
    {
        memset(e, 0,sizeof(e));
    }
    high(){clear();}
};

high operator -(high a, high b)
{
    high c;
    int add=0;
    c.e[0]=max(a.e[0], b.e[0]);
    for (int i=1;i<=c.e[0];i++)
    {
        c.e[i]=a.e[i]-add-b.e[i];
        if (c.e[i]<0) c.e[i]+=10, add=1;
        else add=0;
    }
    while (c.e[c.e[0]]<=0 && c.e[0]>0) c.e[0]--;
    return c;
}

bool operator <(high a, high b)
{
    if (a.e[0]==b.e[0])
    {
        for (int i=a.e[0];i>=1;i--)
            if (a.e[i]!=b.e[i])
                return a.e[i]<b.e[i];
        return 0;
    }
    else
        return a.e[0]<b.e[0];
}

void read(high &a)
{
    char ch=getchar(); high x; x.clear();
    for (;!isdigit(ch);ch=getchar());
    for (;isdigit(ch);ch=getchar()) x.e[++x.e[0]]=ch-'0';
    for (int i=1;i<=x.e[0];i++)
        a.e[x.e[0]-i+1]=x.e[i];
        a.e[0]=x.e[0];
}

void write(high a)
{
    for (int i=a.e[0];i>=1;i--) printf("%d",a.e[i]);
    printf("\n");
}

vector<high> q;

int main()
{
    //freopen("J.in","r",stdin);
    int Case;
    scanf("%d",&Case);
    for (int o=1;o<=Case;o++)
    {

        high a, b;
        read(a);
        q.clear();
        while (a.e[0]>0)
        {
            b.clear();
            int len=b.e[0]=a.e[0];
            for (int i=len;i>len/2;i--)
            {
                b.e[i]=b.e[len-i+1]=a.e[i];
                if (a<b)
                {
                    b.e[i]--;
                    if (i!=len-i+1) b.e[len-i+1]--;
                }
            }
            if (b.e[len]==0)
            {
                b.e[0]--;
                len--;
                for (int i=1;i<=len;i++)
                    b.e[i]=9;
            }
            q.push_back(b);
            a=a-b;
            if (q.size()>50) printf("%d\n",1/0);
        }
        printf("Case #%d:\n",o);
        printf("%d\n",q.size());
        for (int i=0;i<q.size();i++)
            write(q[i]);
    }
  return 0;
}