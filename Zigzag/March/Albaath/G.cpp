#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL base_x(LL x, LL y)
{
	LL base;
	if(x > 0) {
		base = (x*2-1)*(x*2-1);
		if(y >= 0) {
			base += y + x - 1;
		} else {
			base += y + x - 1;
		}
	} else {
		base = (x*2)*(x*2);
		if(y >= 0) {
			base = base - x - y;
		} else {
			base = base - x - y; 
		}
	}
	return base;
}
LL base_y(LL x, LL y)
{
	LL base;
	if(y > 0) {
		base = (y*2)*(y*2);
		if(x >= 0) {
			base = base - y - x;
		} else {
			base = base - y - x;
		}
	} else {
		y = abs(y);
		base = (y*2+1)*(y*2+1) - 1;
		if(x >= 0) {
			base = base - y + x;
		} else {
			base = base - y + x;
		}
	}
	return base;
}

LL cal(LL x, LL y)
{
	if(abs(x) > abs(y)) return base_x(x, y);
	else return base_y(x, y);
}



int main()
{
	int T;
	LL x, y;
	scanf("%d", &T);
	while(T--)
	{
		cin >> x >> y;
		cout << cal(x, y) << endl;
	}



	return 0;
}