#include <bits/stdc++.h>
using namespace std;

char s[500];
int vis[120], cut[500], mx[500];
int n, now, flag;

void dfs(int k){
	if (k>=n){
		for (int i=0;i<n;i++)
			printf((cut[i]&&i!=n-1)?"%c ":"%c",s[i]);
		printf("\n");
		flag=1;
		return ;
	}
	int last=now;
	int tmp=now*10+s[k]-'0';
	if (tmp<10 && k<n-1){
		now=tmp;
		dfs(k+1);
		now=0;
		if (flag) return ;
	}
	if (!vis[tmp]){
		cut[k]=1;
		now=0;
		vis[tmp]=1;
		dfs(k+1);
		vis[tmp]=0;
		now=last;
		cut[k]=0;
		if (flag) return ;
	}
}

int main()
{
	freopen("joke.in","r",stdin);
	freopen("joke.out","w",stdout);
	int len=0;
	for (int i=1;i<=50;i++){
		if (i>=10) len+=2;
		else len+=1;
		mx[len]=i;
	}
	scanf(" %s",s);
	n=strlen(s);
	now=0; flag=0;
	memset(vis,0,sizeof(vis));
	vis[0]=1;
	for (int i=mx[n]+1;i<100;i++) vis[i]=1;
	dfs(0);
	return 0;
}