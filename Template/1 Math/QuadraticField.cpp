typedef long long LL;
const LL w=5;
const LL oo=1e9+7;
struct PP
{
	LL x, y;
	PP(){}
	PP(LL x, LL y):x(x%oo), y(y%oo){}
};
PP operator +(PP a, PP b){
	return PP((a.x+b.x)%oo, (a.y+b.y)%oo);
}
PP operator -(PP a, PP b){
	return PP((a.x-b.x+oo)%oo, (a.y-b.y+oo)%oo);
}
PP operator *(PP a, PP b){
	return PP((a.x*b.x%oo+a.y*b.y%oo*w%oo)%oo, (a.x*b.y%oo+a.y*b.x%oo)%oo);
}
void write(PP a){
	cout<<a.x<<' '<<a.y<<endl;
}
//快速幂
PP exp(PP a, LL b, LL p){
	PP tmp=PP(1, 0);
	while (b){
		if (b&1) tmp=tmp*a;
		a=a*a;
		b=b>>1;
	}
	return tmp;
}
//二次域逆元
PP inv(PP a)
{
	PP r=exp(PP((a.x*a.x%oo-a.y*a.y%oo*w%oo+oo)%oo, 0), oo-2, oo);
	return r*PP(a.x, oo-a.y);
}