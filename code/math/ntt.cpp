//include mod_pow
const ll mod = 998244353, g = 2;//g is primitive root of mod

vi rev, rt;
ll inv(ll x) { return mod_pow(x, mod - 2, mod);}
void ntt(vi &A) {
  REP(i, sz(A)) if (i < rev[i]) swap(A[i], A[rev[i]]);
  for (int k = 1; k < sz(A); k *= 2)
    for (int i = 0; i < sz(A); i += 2*k) REP(j, k) {
      ll t = rt[j + k] * A[i + j + k];
      A[i + j + k] = (A[i + j] - t + mod * mod) % mod;
      A[i + j] = (A[i + j] + t) % mod;
    }
}
void multiply(vi &A, vi &B) { //A = A * B
  ll logn; for(logn = 1; (1 << logn) < sz(A); logn++);
  ll n = 1 << logn; rev = rt = vi(n);
  A.rs(n), B.rs(n);
  rev[0] = 0; rt[1] = 1;
  REP(i, n) rev[i] = (rev[i/2] | (i&1)<<logn)/2;
  for (int i = 1; (1 << i) < n; ++i) {
    int k = 1<<i;
    ll z = mod_pow(g,(mod - 1) >> (i + 2),mod);
    rep(i, k/2, k) rt[2*i] = rt[i], rt[2*i+1] = (rt[i] * z) % mod;
  }
  ntt(A); ntt(B);
  REP(i, n) A[i] = (((A[i] * B[i]) % mod) * inv(n)) % mod;
  REP(i,n) rt[i] = inv(rt[i]);
  ntt(A); }