#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
#define maxn 200200
using namespace std;

typedef long long LL;
typedef vector<LL> vit;
typedef map<vit, LL>::iterator mit;
map<vit, LL> mp;
vit now;
vector<int> t[maxn];
LL mod[2];


LL sz[maxn];
LL f[maxn][2];

int n;

void dfs(int x)
{
    sz[x]=1;
    f[x][0]=f[x][1]=0;
    for (int j=0;j<t[x].size();j++)
    {
        int y=t[x][j];
        dfs(y);
        sz[x]+=sz[y];
        f[x][0]=(f[x][0]+f[y][0])%mod[0];
        f[x][1]=(f[x][1]+f[y][1])%mod[1];
    }
    f[x][0]=(f[x][0]*n+1)%mod[0];
    f[x][1]=(f[x][1]*n+1)%mod[1];
    now.clear();
    now.push_back(sz[x]);
    now.push_back(f[x][0]);
    now.push_back(f[x][1]);
    //if (!mp.count(now)) mp[now]=0;
    mp[now]++;
}


int main()
{
    //freopen("F.in","r",stdin);
    mod[0]=1000000007;
    mod[1]=1000000009;
    scanf("%d",&n);
    mp.clear();
    for (int i=1;i<=n;i++) t[i].clear();
    int x, y;
    for (int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        t[x].push_back(y);
    }
    dfs(1);
    LL ans=0;
    for (mit x=mp.begin();x!=mp.end();x++)
    {
        LL tmp=x->second;
        ans+=tmp*(tmp-1)/2;
    }
    printf("%lld\n",ans);
    return 0;
}
