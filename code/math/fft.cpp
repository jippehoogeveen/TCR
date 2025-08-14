typedef complex<ld> cpx;
typedef vector<cpx> vc;
vi rev; vc rt;
void fft(vc& A) {
	REP(i, sz(A)) if (i < rev[i]) swap(A[i], A[rev[i]]);
	for (int k = 1; k < sz(A); k *= 2)
		for (int i = 0; i < sz(A); i += 2*k) REP(j, k) {
			cpx t = rt[j + k] * A[i + j + k];
			A[i + j + k] = A[i + j] - t;
			A[i + j] += t;
		}
}
void multiply(vc& a, vc& b) { // a = a * b
	ll logn = 0; for(; (1 << logn) < sz(a); logn++);
	ll n = (1 << logn); a.rs(n); b.rs(n);
    const ld PI = acos(-1.0);
	rev = vi(n); rt = vc(n);
	rev[0] = 0; rt[1] = cpx(1, 0);
	REP(i, n) rev[i] = (rev[i/2] | (i&1)<<logn)/2;
	for (int k = 2; k < n; k *= 2) {
		cpx z(cos(PI/k), sin(PI/k));
		rep(i, k/2, k) rt[2*i]=rt[i], rt[2*i+1]=rt[i]*z;
	}
	fft(a); fft(b);
	REP(i, n) a[i] *= b[i] / (ld)(n);
	REP(i, n) rt[i] = 1 / rt[i]; fft(a); }