//矩阵乘法&快速幂(ms<=500)
const int ms=5;
struct matrix
{
	LL e[ms][ms];
	matrix()
	{
		memset(e,0,sizeof(e));
	}
	matrix(int x)
	{
		memset(e,0,sizeof(e));
		for (int i=0;i<ms;i++) e[i][i]=x;
	}
	void clear()
	{
		memset(e,0,sizeof(e));
	}
	friend matrix operator *(matrix a, matrix b)
	{
		matrix c;
		for (int k=0;k<ms;k++)
			for (int i=0;i<ms;i++)
				for (int j=0;j<ms;j++)
					(c.e[i][j]+=a.e[i][k]*b.e[k][j]%oo)%=oo;
		return c;
	}
	friend matrix operator ^(matrix e, LL k)
	{
		matrix tmp=matrix(1);
		while (k)
		{
			if (k&1) tmp=tmp*e;
			k=k>>1;
			e=e*e;
		}
		return tmp;
	}
};