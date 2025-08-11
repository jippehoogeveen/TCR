void solve(int n, vd& a, vd& b, vd& c, vd& d, vd& x) {
	c[0] /= b[0]; d[0] /= b[0];
	rep(i,1,n-1) c[i] /= b[i] - a[i]*c[i-1];
	rep(i,1,n) d[i] =
		(d[i] - a[i]*d[i-1]) / (b[i] - a[i]*c[i-1]);
	x[n-1] = d[n-1];
	for (int i = n-1; i--;) x[i] = d[i] - c[i]*x[i+1];
}