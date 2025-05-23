void fht(vi &A, bool inv, int l, int r) {
	if (l+1 == r) return;
	int k = (r-l)/2;
	if (!inv) fht(A, inv, l, l+k), fht(A, inv, l+k, r);
	rep(i,l,l+k) {
		ll x = A[i], y = A[i+k];
		if (!inv) A[i] =  x-y,    A[i+k] =   x+y;
		else      A[i] = (x+y)/2, A[i+k] = (-x+y)/2;
	}
	if (inv) fht(A, inv, l, l+k), fht(A, inv, l+k, r);
}

vi conv(vi A, vi B) {
	int n = sz(A);
	fht(A,false,0,n); fht(B,false,0,n);
	vi res = vi(n); REP(i,n) res[i] = A[i] * B[i];
	fht(res,true,0,n);
	return res;
}