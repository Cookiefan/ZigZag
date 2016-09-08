#include<stdio.h>
#include<stdlib.h>
void UE(int s);
struct Matrix Mul(struct Matrix a,struct Matrix b,int n1);
struct Matrix Pow(struct Matrix a,int n,int n1);
struct Matrix
{
	long int a[10][10];
};
struct Matrix E;
int main()
{
	int n,k,i,j;
	struct Matrix matrix;
	struct Matrix mnew;
	scanf("%d",&n);
	UE(n);
	for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%ld",&matrix.a[i][j]);
        }
    }
    getchar();
	scanf("%d",&k);
    mnew=Pow(matrix,k,n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(j!=n-1)
                printf("%ld ",mnew.a[i][j]);
            else
                printf("%ld",mnew.a[i][j]);
        }
        printf("\n");
    }
	return 0;
}
void UE(int s)
{
	int i,j;
	for(i=0;i<s;i++)
	{
		for(j=0;j<s;j++)
		{
		    E.a[i][j]=(i==j);
		}
	}
}
struct Matrix Pow(struct Matrix a,int n,int n1)
{
    struct Matrix t=E;;
	while(n>0)
	{
		if(n%2!=0)
		{
		    t=Mul(t,a,n1);
		}
		a=Mul(a,a,n1);
		n/=2;
	}
	return t;
}
struct Matrix Mul(struct Matrix a,struct Matrix b,int n1)
{
	struct Matrix another;
	int i,j,k;
	for(i=0;i<n1;i++)
	{
		for(j=0;j<n1;j++)
		{
			another.a[i][j]=0;
			for(k=0;k<n1;k++)
			{
				another.a[i][j] += ((a.a[i][k])*(b.a[k][j]));
			}
		}
	}
	return another;
}

