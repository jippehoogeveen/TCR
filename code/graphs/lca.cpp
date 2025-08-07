ll n, logn;
vi P; vvi BP; vi H;
//n, P, H input, assert p[root] = root
void initLCA() {
	for(logn = 0; (1 << (logn++)) < n; ) ;
	BP = vvi(n, vi(logn));
	REP(i, n) BP[i][0] = P[i];
	rep(j, 1, logn) REP(i, n)
		BP[i][j] = BP[BP[i][j-1]][j-1];
}
int query(int a, int b) {
	if (H[a] > H[b]) swap(a, b);
	int dh = H[b] - H[a], j = 0;
	REP(i, logn) if (dh & (1 << i)) b = BP[b][i];
	while (BP[a][j] != BP[b][j]) j++;
	while (--j >= 0) if (BP[a][j] != BP[b][j])
		a = BP[a][j], b = BP[b][j];
	return a == b ? a : P[a];
}