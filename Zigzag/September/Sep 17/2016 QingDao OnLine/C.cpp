#include <bits/stdc++.h>
#define maxn 402000
using namespace std;
int ch[maxn][26], v[maxn];
int fail[maxn];
int rot, num, now, n;
char s[1000200];

void ins(int w)
{
    if (ch[now][w]==-1) ch[now][w]=++num;
    v[num]=0;
    for (int i=0;i<26;i++) ch[num][i]=-1;
    now=ch[now][w];
}

void build()
{
    queue<int> q;
    for (int i=0;i<=num;i++) fail[i]=0;
    for (int w=0;w<26;w++)
        if (ch[rot][w]==-1)
            ch[0][w]=rot;
        else
            q.push(ch[0][w]);
    while (!q.empty())
    {
        int x=q.front(); q.pop();
        for (int w=0;w<26;w++)
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

void init()
{
    num=rot=0;
}

int main()
{
	//cout<<sizeof(ch)/1024/1024<<endl;
    //freopen("C.in","r", stdin);
    int Case;
    scanf("%d",&Case);
    for (int o=1;o<=Case;o++)
    {
        scanf("%d",&n);
        init();
        for (int i=1;i<=n;i++)
        {
            scanf(" %s ",s);
            int len=strlen(s);
            now=rot;
            for (int i=0;i<len;i++)
                ins(s[i]-'a');
            v[now]=len;
        }
        build();
        now=rot;
        char c;
        int i=0;
        while (scanf("%c",&c)&&c!='\n')
        {
        	s[i]=c;
        	if (isupper(c)) c=c+'a'-'A';
            else if (!islower(c)) now=rot;
            else{
	            int w=c-'a';
	            now=ch[now][w];
	            if (v[now]>0)
	                for (int j=0;j<v[now];j++)
	                    s[i-j]='*';
	        }
	        i++;
        }
        s[i]=0;
        printf("%s\n",s);
    }
    return 0;
}