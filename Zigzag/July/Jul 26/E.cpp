#include <bits/stdc++.h>
#define maxn 1200
// #define mod 3
using namespace std;
typedef pair<int,int> pii;
vector<pii> ans;
int a[maxn][maxn],p[maxn][maxn];
int x[maxn];

// int gcd(int a, int b)
// {
//     return b?gcd(b, a%b):a;
// }
// int lcm(int a, int b)
// {
//     return a/gcd(a, b)*b;
// }
// int inv(int a, int m)
// {
//     if(a == 1)
//         return 1;
//     return inv(m%a, m)*(m-m/a)%m;
// }
// int gauss(int equ, int var)
// {
//     int max_r, col, k;
//     for(k = 0, col = 0; k < equ && col < var; k++, col++) {
//         max_r = k;
//         for(int i = k + 1; i < equ; i ++) {
//             if(abs(a[i][col]) > abs(a[max_r][col]))
//                 max_r = i;
//         }
//         if(a[max_r][col] == 0) {
//             k--;
//             continue;
//         }
//         if(max_r != k) {
//             for(int j = col; j < var+1; j++) {
//                 swap(a[k][j], a[max_r][j]);
//             }
//         }
//         for(int i = k + 1; i < equ; i++) {
//             if(a[i][col]) {
//                 int LCM = lcm(abs(a[i][col]), abs(a[k][col]));
//                 int ta = LCM/abs(a[i][col]);
//                 int tb = LCM/abs(a[k][col]);
//                 if(a[i][col] * a[k][col] < 0)
//                     tb = -tb;
//                 for(int j = col; j < var+1; j++) {
//                     a[i][j] = ((a[i][j]*ta - a[k][j]*tb)%mod+mod)%mod;
//                 }
//             }
//         }
//         for(int i = var-1; i >= 0; i--) {
//             int tmp = a[i][var];
//             for(int j = i+1; j < var; j++) {
//                 if(a[i][j]) {
//                     tmp -= a[i][j]*x[j];
//                     tmp = (tmp%mod+mod)%mod;
//                 }
//             }
//             x[i] = a[i][i]*tmp%mod;
//         }
//     }
// }


int gcd(int a, int b)
{
    return b?gcd(b, a%b):a;
}
int lcm(int a, int b)
{
    return a/gcd(a, b)*b;
}
//高斯消元
void gauss(int n)
{
	// for (int i=0;i<n;i++)
	// {
	// 	for (int j=0;j<=n;j++)
	// 		cout<<a[i][j]<<' ';
	// 	cout<<endl;
	// }
	int k=0;
	for (int i=0;i<n;i++)
	{
		int p=0;
		for (int j=k;j<n;j++)
			if (a[j][i]>0) { p=j; break; }
		if (!a[p][i]) continue;
		for (int l=0;l<=n;l++) swap(a[p][l],a[k][l]);
		for (int j=k+1;j<n;j++)
		{
			if (!a[j][i]) continue;
			//int d=lcm(a[j][i], a[k][i]);
			//int s=d/a[j][i], t=d/a[k][i];
			//int r=a[j][i]*a[k][i]%3;
			for (int l=0;l<=n;l++)
				a[j][l]=((a[j][l]*s-a[k][l]*t)%3+3)%3;
				// if (a[j][i]==a[k][i])
				// 	a[j][l]=((a[j][l]-a[k][l])%3+3)%3;
				// else if (a[j][i]==1)
				// 	a[j][l]=((2*a[j][l]-a[k][l])%3+3)%3;
				// else
				// 	a[j][l]=((a[j][l]-2*a[k][l])%3+3)%3;
		}
		k++;
	}
	// for (int i=0;i<n;i++)
	// {
	// 	for (int j=0;j<=n;j++)
	// 		cout<<a[i][j]<<' ';
	// 	cout<<endl;
	// }
	for (int i=n-1;i>=0;i--)
	{
		x[i]=a[i][n];
		for (int j=i+1;j<n;j++)
			x[i]=((x[i]-x[j]*a[i][j])%3+3)%3;
		x[i]=(x[i]*a[i][i])%3;
	}
}

int main()
{
	//cout<<rev(1, 3)<<' '<<rev(2, 3)<<endl;
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		memset(a,0,sizeof(a));
		memset(x,0,sizeof(x));
		int n,m;
		scanf("%d%d",&n,&m);
		// for (int i=0;i<=n*m+1;i++)
		// 	for (int j=0;j<=n*m+1;j++)
		// 		a[i][j]=0;
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
			{
				scanf("%d",&p[i][j]);
				if (i-1>=0) a[i*m+j][(i-1)*m+j]=1;
				if (i+1<n)  a[i*m+j][(i+1)*m+j]=1;
				if (j-1>=0) a[i*m+j][i*m+(j-1)]=1;
				if (j+1<m)  a[i*m+j][i*m+(j+1)]=1;
				a[i*m+j][i*m+j]=2;
				a[i*m+j][n*m]=(3-p[i][j])%3;
			}
		gauss(n*m);
		ans.clear();
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				for (int k=1;k<=x[i*m+j];k++)
					ans.push_back(pii(i+1, j+1));
		int ss=ans.size();
		printf("%d\n",ss);
		for (int i=0;i<ss;i++)
			printf("%d %d\n",ans[i].first,ans[i].second);
	}

	return 0;

}