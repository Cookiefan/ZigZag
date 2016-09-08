#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int f[maxn][maxn][2];
int p[maxn],q[maxn];
int r[maxn][maxn];
char a[maxn], b[maxn], c[maxn];

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%s %s %s",a+1,b+1,c+1);
		int la=strlen(a+1), lb=strlen(b+1), lc=strlen(c+1);

		memset(r,-1,sizeof(r));
		for (int i=1;i<=la;i++) r[i][1]=(a[i]==c[1])?i:r[i-1][1];
		for (int i=1;i<=la;i++)
			for (int j=2;j<=lc;j++)
				r[i][j]=(a[i]==c[j])?r[i-1][j-1]:r[i-1][j];
		for (int i=1;i<=la;i++) p[i]=r[i][lc];

		memset(r,-1,sizeof(r));
		for (int i=1;i<=lb;i++) r[i][1]=(b[i]==c[1])?i:r[i-1][1];
		for (int i=1;i<=lb;i++)
			for (int j=2;j<=lc;j++)
				r[i][j]=(b[i]==c[j])?r[i-1][j-1]:r[i-1][j];
		for (int i=1;i<=lb;i++) q[i]=r[i][lc];

		// for (int i=1;i<=la;i++) cout<<p[i]<<' '; cout<<endl;
		// for (int i=1;i<=lb;i++) cout<<q[i]<<' '; cout<<endl;

		memset(f,0,sizeof(f));
		for (int i=1;i<=la;i++)
			for (int j=1;j<=lb;j++)
			{
				f[i][j][0]=max(f[i-1][j][0], f[i][j-1][0]);
				if (a[i]==b[j])
					f[i][j][0]=max(f[i][j][0],f[i-1][j-1][0]+1);

				f[i][j][1]=max(f[i-1][j][1], f[i][j-1][1]);
				if (a[i]==b[j] && f[i-1][j-1][1])
					f[i][j][1]=max(f[i][j][1],f[i-1][j-1][1]+1);

				if (p[i]!=-1 && q[j]!=-1 && a[i]==c[lc] && b[j]==c[lc])
					f[i][j][1]=max(f[i][j][1], f[p[i]][q[j]][0]+lc-1);
			}
		// for (int i=1;i<=la;i++)
		// {
		// 	for (int j=1;j<=lb;j++)
		// 		cout<<f[i][j][1]<<' ';
		// 	cout<<endl;
		// }
		printf("Case #%d: %d\n",o,f[la][lb][1]);
	}

	return 0;
}