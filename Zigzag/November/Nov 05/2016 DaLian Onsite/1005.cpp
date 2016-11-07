#include <bits/stdc++.h>
#define ULL __int128
#define LL long long
using namespace std;
int a[1000];
char s[1000];
LL n;
void write(LL x){
    if (x==0){
        printf("%c\n",'0');
        return ;
    }
    int num=0;
    while (x){
        int c=x%10;
        s[++num]='0'+c;
        x=x/10;
    }
    for (int i=num;i>=1;i--)
        printf("%c",s[i]);
    printf("\n");
}
ULL S1(LL x)
{
//cout<<x<<endl;
    ULL ol=x;
    ULL y;
    ULL ans;
    ULL tmp,l,sum;
    ans=0;
    l=0;tmp=1;
    while (x)
    {
        l++;
        a[l]=x%2;
        x/=2;
    }
    sum=0;y=0;
    for (int i=1;i<=l;i++)
    {
        y+=tmp*a[i];
        x=ol/tmp/2;
        if (y>tmp)
        {
            ans+=tmp*(x+1);
        }
        else 
            ans+=tmp*x;

        tmp*=2;
    }
    return ans;
}

LL S2(LL x)
{
    LL ans=0;
    LL l=0,sum,ol;
    LL tmp=n,y,z;
    ol=x;
    while (tmp)
    {
        l++;
        a[l]=tmp%2;
        tmp/=2;
    }
//    cout<<l<<' '<<x<<endl;
    sum=0;tmp=1;
    for (int i=1;i<=l;i++)
    {
        z=tmp-1;
        x=((x|z)-z)|tmp;
        y=x-tmp+1;
//        cout<<x<<' '<<y<<' '<<tmp<<endl;
        if (x>=ol && x<=n && y<=ol) ans++;
        tmp*=2;
    }
    return ans;
}
LL S22(LL x)
{
    LL ans=0;
    while (x<=n)
    {
        ans++;
        x+=(x&-x);
    }
    return ans;
}
int main()
{
    int t,fl;
    LL x,y;
    ULL ax,ay;
    ULL ans;
    scanf("%lld%d",&n,&t);
    while (t--)
    {
        scanf("%d",&fl);
        if (fl==1)
        {
            scanf("%lld%lld",&x,&y);
            ax=S1(x-1);
            ay=S1(y);
//            cout<<ax<<' '<<ay<<endl;
            //write(ax);
            //write(ay);
            ans=ay-ax;
            //cout<<ans<<endl;
            write(ans);
            //printf("%lld\n",ans);
        }
        else
        {
            scanf("%lld",&x);
            ans=S22(x);
            write(ans);
            //cout<<ans<<endl;
            //printf("%lld\n",ans);
        }
    }


    return 0;
}
