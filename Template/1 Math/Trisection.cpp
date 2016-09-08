//三分求最小值
double l=mi,r=mx,ans;
while (dcmp(l-r)<=0)
{
	double lmid=l+(r-l)/3.0;
	double rmid=r-(r-l)/3.0;
	if (dcmp(get_ans(lmid)-get_ans(rmid))<=0)
	{
		r=rmid-eps;
		ans=get_ans(lmid);
	}
	else
	{
		l=lmid+eps;
	}	
}