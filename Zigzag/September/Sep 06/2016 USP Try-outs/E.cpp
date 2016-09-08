#include <bits/stdc++.h>
#define maxn 320
#define inf 9999999
using namespace std;

string a;
int n,m;

int ch[maxn][12];
int fail[maxn], good[maxn], bad[maxn];
int rot, num, now;

typedef pair<int, int> pii;
int vis[maxn][1<<15];
char e[maxn][1<<15];
pii pre[maxn][1<<15];

void ins(int w)
{
    if (ch[now][w]==-1) ch[now][w]=++num;
    now=ch[now][w];
}

void build()
{
	queue<int> q;
	memset(fail,0,sizeof(fail));
	for (int w=0;w<10;w++)
		if (ch[rot][w]==-1)
    		ch[0][w]=rot;
    	else
    		q.push(ch[0][w]);
    while (!q.empty())
    {
        int x=q.front(); q.pop();
        good[x]|=good[fail[x]];
        bad[x]|=bad[fail[x]];
        for (int w=0;w<10;w++)
            if (ch[x][w]==-1)
            	ch[x][w]=ch[fail[x]][w];
            else
            {
            	int y=ch[x][w];
            	fail[y]=ch[fail[x]][w];
                q.push(y);
            }
    }
}

string travel()
{
	memset(vis,0,sizeof(vis));
	queue<pii> q;
	q.push(pii(rot, 0));
	vis[rot][0]=1;
	string ss="";
	while (!q.empty())
	{
		int x=q.front().first;
		int xst=q.front().second;
		if (xst==(1<<n)-1)
		{
			pii tmp=q.front();
			while (tmp.first!=rot || tmp.second!=0)
			{
				ss.push_back(e[tmp.first][tmp.second]);
				tmp=pre[tmp.first][tmp.second];
			}
			reverse(ss.begin(), ss.end());
			return ss;
		}
		q.pop();

		for (int w=0;w<10;w++)
		{
			int y=ch[x][w];
			int yst=xst|good[y];
			if (bad[y] || vis[y][yst]) continue;
			q.push(pii(y, yst));
			vis[y][yst]=1;
			e[y][yst]='a'+w;
			pre[y][yst]=pii(x, xst);
		}
	}
	return "-";
}

int main()
{
	scanf("%d%d",&n,&m);
	memset(ch,-1,sizeof(ch));
	memset(good,0,sizeof(good));
	memset(bad,0,sizeof(bad));
	rot=num=0;
	for (int i=0;i<n+m;i++)
	{
		cin>>a;
		int len=a.length();
		now=rot;
		for (int j=0;j<len;j++) ins(a[j]-'a');
		if (i<n) good[now]=1<<i;
		else bad[now]=1;
	}
	build();
	cout<<travel()<<endl;
	return 0;
}