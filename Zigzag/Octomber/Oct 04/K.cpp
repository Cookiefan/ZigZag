#include<bits/stdc++.h>
#define low 63
#define oo 1000000007
using namespace std;
typedef long long LL;
LL n, ans;
LL ss[100];

LL bit(int k)//2^k
{
    LL tmp=1;
    return tmp<<k;
}
LL pre(LL x, int k)//x[low-k..low-1]
{
    return x>>(low-k);
}
LL suf(LL x, int k)//x[0..k-1]
{
    return x & (bit(k)-1);
}
LL cnt(LL x)//num of 0..x
{
    return (x+1)%oo;
}
LL sum(LL x)//sum of 1 (0..x)
{
    x=x+1;
    LL tmp=0;
    for (int i=0;i<low;i++)
    {
        LL t=bit(i);
        tmp=(tmp+x/(t<<1)*t%oo)%oo;
        tmp=(tmp+(x%(t<<1)>=t)*(x%(t<<1)-t)%oo)%oo;
    }
    return tmp;
}

int main()
{
    //freopen("K.in","r",stdin);
    int Case;
    scanf("%d",&Case);
    for (int i=0;i<64;i++) ss[i]=sum(bit(i)-1);
    for (int o=1;o<=Case;o++)
    {
        scanf("%I64d",&n);
        ans=0;
        for (int i=0;i<low;i++)
        {
            LL lf=0, rt=0;
            if ((n>>i)&1)
            {
                lf=1;
                if (i==0) rt=1;
                else{
                    LL L=bit(i)-1, R=suf(n, i);
//                    cout<<L<<' '<<R<<endl;
//                    cout<<sum(L)<<' '<<sum(R)<<endl;
                    rt=(rt+cnt(L)*cnt(R)%oo)%oo;
                    rt=(rt+cnt(L)*sum(R)%oo)%oo;
                    rt=(rt+cnt(R)*ss[i]%oo)%oo;
                }
                ans=(ans+lf*rt%oo)%oo;
                //cout<<lf*rt<<' ';
            }
            lf=cnt((pre(n, low-i-1)))-1;
            if (i==0) rt=1;
            else{
                rt=0;
                LL L=bit(i)-1, R=bit(i)-1;
                //cout<<L<<' '<<R<<endl;
                rt=(rt+cnt(L)*cnt(R)%oo)%oo;
                rt=(rt+cnt(L)*ss[i]%oo)%oo;
                rt=(rt+cnt(R)*ss[i]%oo)%oo;
            }
            //cout<<lf*rt<<' ';
            ans=(ans+lf*rt%oo)%oo;
            //cout<<endl;
        }
        printf("Case #%d: %I64d\n", o, ans);
    }
    return 0;
}