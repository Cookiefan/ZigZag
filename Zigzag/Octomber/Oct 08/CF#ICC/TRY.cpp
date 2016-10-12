int a[N][N],tag=0,n,m;
void swa(int k1,int k2)
{
	rep(i,0,n)
	swap(a[i][k1],a[i][k2]);
	int wm=1;
	rep(i,0,n)
	{
		int wr=0;
		rep(j,0,m)
		{
			if (a[i][j]!=j+1) wr++;
		}
		if (wr>2) wm=0;
	}
	if (wm) tag=1;
	rep(i,0,n)
	swap(a[i][k1],a[i][k2]);
}
int main()
{
	sf(n);sf(m);
	rep(i,0,n)
	{
		rep(j,0,m)
		sf(a[i][j]);
	}
	swa(2,3);
	rep(i,0,m)
		rep(j,i,m)
		swa(i,j);
	if (tag) puts("YES");
	else puts("NO"); 
	return 0;
}
