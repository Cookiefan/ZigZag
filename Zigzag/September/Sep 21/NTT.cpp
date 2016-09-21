void ntt(LL A[],int n,int inv) {
    // inv == 1 : ntt, == -1 : intt
    LL w = 1,d = exp(G,(mod - 1) / n,mod),t;
    int i,j,c,s;
    if (inv == -1) {
        for (i = 1,j = n - 1; i < j; ++ i,-- j)
            std::swap(A[i],A[j]);
        for (t = exp(n,mod - 2,mod),i = 0; i < n; ++ i)
            A[i] = A[i] * t % mod;
    }
    for (s = n >> 1; s; s >>= w = 1,d = d * d % mod) {
        for (c = 0; c < s; ++ c,w = w * d % mod) {
            for (i = c; i < n; i += s << 1) {
                A[i | s] = (A[i] + mod - (t = A[i | s])) * w % mod;
                A[i] = (A[i] + t) % mod;
            }
        }
    }
    for (i = 1; i < n; ++ i) {
        for (j = 0,s = i,c = n >> 1; c; c >>= 1,s >>= 1)
            j = j << 1 | s & 1;
        if (i < j) std::swap(A[i],A[j]);
    }
}

void ntt(LL *a, int n, int flag)
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
				a[i|s]=(x-y+mod)*w%mod;
			}
	for (int i=1;i<n;i++)
	{
		int j=0;
		for (int s=i, k=n>>1; k; k>>=1, s>>=1)
			j=j<<1|s&1;
		if (i<j) swap(a[i], a[j]);
	}
}