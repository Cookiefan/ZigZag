//高斯消元

void gauss(int n)
{
    int k=1;
    for (int i=1;i<=n;i++)
    {
        int p=0;
        for (int j=k;j<=n;j++)
            if (fab(a[j][i])>eps) {    p=j; break;    }
        if (!p) continue;
        for (int l=1;l<=n+1;l++) swap(a[p][l],a[k][l]);
        for (int j=k+1;j<=n;j++)
        {
            lb rate=a[j][i]/a[k][i];
            for (int l=1;l<=n+1;l++) 
                a[j][l]-=a[k][l]*rate;
        }
        k++;
    }
    for (int i=n;i;i--)
    {
        v[i]=a[i][n+1];
        for (int j=i+1;j<=n;j++)
            v[i]-=v[j]*a[i][j];
        v[i]/=a[i][i];
    }
}
