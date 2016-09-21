void fft(cpx *a, int n, int flag)
{
    if (flag==-1) 
    {
    	for (int i=1;i<n/2;i++) swap(a[i], a[n-i]);
        for (int i=0;i<n;i++) a[i].x/=n, a[i].y/=n;
    }
    cpx wn(cos(2*PI/n), sin(2*PI/n));
    for (int s=n>>1;s;s>>=1, wn=wn*wn)
    {
    	cpx w(1,0);
       	for (int k=0; k<s; k++, w=w*wn)
			for (int i=k; i<n; i+=s<<1)
            {
                cpx x=a[i], y=a[i|s];
				a[i]=x+y;
				a[i|s]=(x-y)*w;
            }
    }
    for (int i=1, j=0;i<n;i++,j=0)
	{
		for (int s=i, k=n>>1; k; s>>=1, k>>=1)
			j=j<<1|s&1;
		if (i<j) swap(a[i], a[j]);
	}
}
inline void ntt(LL a[], int n, int flag)
{
	LL wn=exp(G, (mod-1)/n, mod), w=1;
	if (flag==-1)
	{
		for (int i=1;i<n/2;i++) swap(a[i], a[n-i]);
		LL inv=exp(n, mod-2, mod);
		for (int i=0;i<n;i++) a[i]=a[i]*inv%mod;
	}
	for (int s=n>>1; s; s=s>>1, wn=wn*wn%mod, w=1)
		for (int k=0; k<s; k++, w=w*wn%mod)
			for (int i=k; i<n; i+=s<<1)
			{
				LL x=a[i], y=a[i|s]%mod;
				a[i]=(x+y)%mod;
				a[i|s]=(x-y+mod)%mod*w%mod;
			}
	for (int i=1, j=0;i<n;i++,j=0)
	{
		for (int s=i, k=n>>1; k; s>>=1, k>>=1)
			j=j<<1|s&1;
		if (i<j) swap(a[i], a[j]);
	}
}