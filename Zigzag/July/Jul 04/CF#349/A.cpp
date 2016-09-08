#include <bits/stdc++.h>
using namespace std;

double d, h, v, e, u;
const double eps=1e-9;
const double pi=acos(-1.0);
int dcmp(double x)
{
	if (fabs(x)<eps) return 0;
	else if (x>0) return 1;
	else return -1; 
}

int main()
{
	scanf("%lf%lf%lf%lf",&d, &h, &v, &e);
	u=v-pi*d*d*0.25*e;
	if (dcmp(u)<=0) printf("NO\n");
	else
		printf("YES\n%.5f\n",pi*d*d*0.25*h/u);

	return 0;
}