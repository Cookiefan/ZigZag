#include <bits/stdc++.h>
#define maxn 220000
using namespace std;

int fail[maxn];
int ch[maxn][30], freq[maxn], fa[maxn];
int n,m,num,rot;
string s;

void ins(string &s)
{
	int len=s.length(), now=rot;
	for (int i=0;i<len;i++)
	{
		int w=s[i]-'a';
		if (!ch[now][w]) ch[now][w]=++num;
		fa[ch[now][w]]=now;
    	now=ch[now][w];
    	freq[now]++;
    }
}

void build()
{
	queue<int> q;
	while (!q.empty()) q.pop();
	q.push(rot);
    while (!q.empty())
    {
        int p=q.front(); q.pop();
        for (int w=0;w<26;w++)
            if (ch[p][w])
            {
                int tmp=ch[p][w];
                int j=p;
                if (j==rot) fail[tmp]=rot;
                else
                {
                    j=fail[j];
                    while (j&&ch[j][w]==0) j=fail[j];
                    if (ch[j][w]) fail[tmp]=ch[j][w];
                    else fail[tmp]=rot;
                }
                //add_edge(fail[tmp],tmp);
                q.push(tmp);
            }
    }
    for (int i=num;i>=1;i--)
    	freq[fail[i]]+=freq[i];
}

int query(string &s)
{
	int now=rot, len=s.length();
	for (int i=0;i<len;i++)
	{
		int w=s[i]-'a';
		if (ch[now][w]) now=ch[now][w];
		else return 0;
	}
	return freq[now];
}

void init()
{
	memset(freq,0,sizeof(freq));
	memset(ch,0,sizeof(ch));
	rot=num=1;
}

int main()
{
	freopen("J.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		init();
		for (int i=1;i<=n;i++)
		{
			cin>>s;
			ins(s);
		}
		build();
		printf("Case #%d:\n",o);
		for (int i=1;i<=m;i++)
		{
			cin>>s;
			int k=query(s);
			//cout<<"k"<<k<<endl;
			if (!k)
			{
				printf("%d\n",0);
				continue;
			}
			int len=s.length();
			int l=1, r=len,ans=0;
			while (l<=r)
			{
				int mid=(l+r)>>1;
				string t=s.substr(len-mid, mid);
				if (query(t)==k)
				{
					ans=mid;
					r=mid-1;
				}
				else
					l=mid+1;
			}
			cout<<"ans"<<' '<<ans<<endl;
			printf("%d\n",len-ans+1);
		}
	}
	return 0;
}