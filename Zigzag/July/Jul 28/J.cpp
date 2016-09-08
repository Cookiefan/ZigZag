#include <bits/stdc++.h>
#define maxn 120000
#define inf 99999999
using namespace std;
int f[maxn],g[maxn];
int a[maxn];
int n;

int main()
{
	freopen("J.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		int mxf=0;
		for (int i=1;i<=n;i++) g[i]=inf;
		f[0]=0; g[0]=-1;
		for (int i=1;i<=n;i++)
			if (!a[i])
			{
				f[i]=mxf+1;
				mxf=max(f[i], mxf);
				for (int j=mxf;j>=1;j--)
					g[j]=min(g[j], g[j-1]+1);
			}
			else
			{
				int l=0, r=mxf;
				while (l<=r)
				{
					int mid=(l+r)>>1;
					if (g[mid]<a[i])
					{
						f[i]=mid+1;
						l=mid+1;
					}
					else
						r=mid-1;
				}
				g[f[i]]=min(g[f[i]],a[i]);
				mxf=max(f[i], mxf);
			}
		//for (int i=1;i<=n;i++) cout<<f[i]<<' '; cout<<endl;
		//for (int i=1;i<=n;i++) cout<<g[i]<<' '; cout<<endl;
		printf("Case #%d: %d\n",o,mxf);
	}
	return 0;
}

