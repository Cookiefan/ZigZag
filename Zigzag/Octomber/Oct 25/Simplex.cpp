#include <bits/stdc++.h>
using namespace std;
#define maxn 202
#define eps 1e-7
#define inf 999999999

double a[maxn][maxn], ans[maxn];
int id[maxn], nxt[maxn];
int n,m;

int dcmp(double x){
	if (x<-eps) return -1;
	if (x>eps) return 1;
	return 0;
}

void write(int n, int m){
	for (int i=0;i<=n;i++){
		for (int j=0;j<=m;j++)
			printf("%.1f ",a[i][j]);
		cout<<endl;
	}
	cout<<endl;
}
void pivot(int x, int y, int n, int m){
	swap(id[m+x], id[y]);
	double tmp=-a[x][y]; a[x][y]=-1;
	for (int i=0;i<=m;i++)
		a[x][i]/=tmp;
	for (int i=0;i<=n;i++){
		if (!dcmp(a[i][y]) || i==x) continue;
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

int main()
{
	int n,m,t;
	scanf("%d%d%d",&n,&m,&t);
	for (int i=1;i<=n;i++) scanf("%lf",&a[0][i]);
	for (int i=1;i<=m;i++){
		for (int j=1;j<=n;j++){
			scanf("%lf",&a[i][j]);
			a[i][j]*=-1;
		}
		scanf("%lf",&a[i][0]);
	}
	double tmp=simplex(m, n);
	if (tmp==-1)
		printf("Infeasible\n");
	else if (tmp==inf)
		printf("Unbounded\n");
	else{
		printf("%.8f\n",tmp);
		if (t==1){
			for (int i=1;i<=n;i++)
				printf(i==n?"%.8f\n":"%.8f ",ans[i]);
		}
	}
	return 0;
}