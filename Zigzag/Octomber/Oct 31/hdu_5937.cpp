#include <bits/stdc++.h>
using namespace std;
#define inf 99999999
int c[11];
int id[100], v[100];
int a[100][100], nxt[100];
int n,m,ans,cnt;

void pvt(int x,int y){  
    int i,j;  
    for (i=0; i<=n; i++) if (i!=x && a[i][y]){  
        for (j=0; j<=m; j++) if (a[x][j] && j!=y)  
            a[i][j]-=a[i][y]*a[x][j];  
        a[i][y]=-a[i][y];  
    }  
}  
int solve(){  
    int i,j,k; a[n+1][0]=1000000000;  
    while (1){  
        for (i=1; i<=m; i++) if (a[0][i]>0) break;  
        if (i>m) return -a[0][0];  
        for (j=1,k=n+1; j<=n; j++)  
            if (a[j][i]>0 && a[j][0]<a[k][0]) k=j;  
        pvt(k,i);  
    }  
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
					a[i][m]=1;
					a[j][m]=1;
					a[i+j][m]=1;
				}
		for (int i=1;i<=m;i++){
			a[9+i][i]=1;
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
		ans=max(ans, cnt+solve());
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