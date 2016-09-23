//高斯消元XOR
int gauss(int n, int m)
{
    int k=1;
    for (int i=1;i<=m;i++)
    {
        int p=0;
        for (int j=k;j<=n;j++) if (a[j][i]) {    p=j; break;    }
        if (!p) continue;
        for (int l=1;l<=m;l++) swap(a[p][l],a[k][l]);//有常数的话m+1
        for (int j=k+1;j<=n;j++)
        	if (a[j][i]==1)
	           for (int l=1;l<=m;l++)//有常数的话m+1
    	           	a[j][l]=a[j][l]^a[k][l];
        k++;
    }
    return k-1;//返回线性无关方程个数
}