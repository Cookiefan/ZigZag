//倍增LCA
void set_father(int n)
{
	for (int k=1;k<=low;k++)
		for (int i=1;i<=n;i++)
			fa[i][k]=fa[fa[i][k-1]][k-1];
}

int get_father(int x,int y)
{
	if (dep[x]>dep[y]) swap(x,y);
	for (int i=low;i>=0;i--)
		if (dep[fa[y][i]]>=dep[x]) y=fa[y][i];
	if (x==y) return x;
	for (int i=low;i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}