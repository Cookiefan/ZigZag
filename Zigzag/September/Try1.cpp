typedef long long ll;

ll fat[MAXN];
ll PD[MAXN][MAXN][MAXN][MAXN];
int N;

ll aller(int k, int l2, int l3, int l4) {
	if(k >= N) {
		if(l4 < k+1 || l3 < k+1) return 1;
		return 0;
	}
	ll &r = PD[k][l2][l3][l4];
	if(r != -1) return r;
	ll total = 0;
	total = (total + aller(k+1, l2+1, l3+1, l4+1))%MOD;
	for(int i = 2; i <= l2; i++)
		total = (total + aller(k+1, i, l3+1, l4+1))%MOD;
	for(int i = l2+1; i <= l3; i++)
		total = (total + aller(k+1, l2, i, l4+1))%MOD;
	for(int i = l3+1; i <= l4; i++)
		total = (total + aller(k+1, l2, l3, i))%MOD;
	return r = total;
}

int main() {
	memset(PD, -1, sizeof(PD));
	fat[0] = fat[1] = 1;
	fr(i, 2, MAXN) fat[i] = (fat[i-1]*i)%MOD;

	scanf("%d", &N);
	//cout << fat[N] << " " << aller(0, 1, 1, 1) << endl;
	printf("%lld\n", ((fat[N] - aller(0, 1, 1, 1))%MOD + MOD)%MOD);

}
