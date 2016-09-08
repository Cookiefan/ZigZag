//分治求逆序对
void solve(int l, int r)
{
	if (l==r) return ;
	int mid=(l+r)>>1;
	solve(l, mid);
	solve(mid+1, r);
	int i=l, j=mid+1, k=0;
	while (i<=mid || j<=r)
	{
		if (j>r || i<=mid && q[i]<=q[j]) nq[k++]=q[i++], sum+=(j-mid-1);
		else
		if (i>mid || j<=r && q[i]>q[j]) nq[k++]=q[j++];
	}
	for (int i=0;i<k;i++) q[l+i]=nq[i];
}