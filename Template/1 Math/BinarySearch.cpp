//整数二分
int l=1,r=n, ans;
while (l<=r)
{
	int mid=(l+r)>>1;
	if (judge(mid)) l=mid+1,ans=mid;
	else r=mid-1;
}
//浮点数二分
hile (l-r<=1e-6)
{
	double mid=(l+r)/2.0;
	if (judge(mid)<=0.0) r=mid-0.000001,ans=mid;//所有>0的解均不合法
	else l=mid+0.000001;    
}