#include <bits/stdc++.h>
using namespace std;
#define inf 99999999
int c[11];
int id[100], v[100];
int a[100][100], nxt[100];
int n,m,ans,cnt;

void pivot(int x, int y, int n, int m){
	swap(id[m+x], id[y]);
	double tmp=-a[x][y]; a[x][y]=-1;
	for (int i=0;i<=m;i++)
		a[x][i]*=tmp;
	for (int i=0;i<=n;i++){
		if (!a[i][y] || i==x) continue;
		tmp=a[i][y]; a[i][y]=0;
		for (int j=0;j<=m;j++)
			a[i][j]+=tmp*a[x][j];
	}
}

double simplex(int n, int m){
	for (int i=1;i<=m;i++) id[i]=i;
	while (1){
		int x=0, y=0;
		//double mi=0;
		for (int i=1;i<=n;i++)
			if (dcmp(a[i][0])<0)
				x=i;
		if (!x) break;
		for (int j=1;j<=m;j++)
			if (dcmp(a[x][j])>0){
				y=j;
				break;
			}
		if (!y) return -1;
		pivot(x, y, n, m);
	}
	while (1){
		int x=0, y=0;
		double mx=0;
		for (int i=1;i<=m;i++)
			if (dcmp(a[0][i]-mx)>0)
				mx=a[0][y=i];
		if (!y) break;
		double mi=inf,tmp;
		for (int i=1;i<=n;i++)
			if (dcmp(a[i][y])<0&& 
				(tmp=-a[i][0]/a[i][y])<mi)
				mi=tmp,x=i;
		if (!x) return inf;
		pivot(x, y, n, m);
	}
	for (int i=m+1;i<=m+n;i++){
		ans[id[i]]=a[i-m][0];
	}
	return a[0][0];
}

void dfs(int k){
	if (k>4){
		memset(a, 0, sizeof(a));
		m=0;
		for (int i=1;i<=9;i++)
			for (int j=1;j<=9;j++)
				if (i+j<=9 && i!=j){
					++m;
					cout<<m<<": "<<i<<"+"<<j<<"="<<i+j<<endl;
					a[i][m]=-1;
					a[j][m]=-1;
					a[i+j][m]=-1;
				}
		for (int i=1;i<=m;i++){
			a[9+i][i]=-1;
			a[9+i][0]=1;
		}
		n=41;
		for (int i=1;i<=m;i++) a[0][i]=1;
		for (int i=1;i<=9;i++) a[i][0]=c[i];
		
		for (int i=0;i<=n;i++){
			for (int j=0;j<=m;j++)
				cout<<a[i][j]<<' ';
			cout<<endl;
		}
		ans=max(ans, cnt+simplex());
		for (int i=m+1;i<=m+n;i++)
	        v[id[i]]=a[i-m][0];
		for (int i=1;i<=m;i++) cout<<v[i]<<' ';cout<<endl;
		return ;
	}
	dfs(k+1);
	if (c[k]>=2 && c[2*k]>=1){
		c[k]-=2; c[2*k]-=1;
		cnt++;
		dfs(k+1);
		cnt--;
		c[k]+=2; c[2*k]+=1;
	}
}

int main()
{
	
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++){
		for (int i=1;i<=9;i++)
			scanf("%d",&c[i]);
		ans=cnt=0;
		dfs(1);
		printf("%d\n",ans);
	}
	return 0;
}