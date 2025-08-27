struct TwoSat {
	int n; SCC *scc = nullptr; vvi adj;
	TwoSat(int _n) : n(_n), adj(_n*2, vi()) {}
	~TwoSat() { delete scc; }

	// a => b, i.e. b is true or ~a
	void imply(int a, int b) {
		adj[n+a].pb(n+b); adj[n+(~b)].pb(n+(~a)); }
	void OR(int a, int b) { imply(~a, b); }
	void CONST(int a) { OR(a, a); }
	void IFF(int a, int b) { imply(a,b); imply(b,a); }

	bool solve(vb &sol) {
		delete scc; scc = new SCC(adj);
		REP(i, n) if (scc->cnr[n+i] == scc->cnr[n+(~i)])
			return false;
		vb seen(n, false);
		sol.assign(n, false);
		for (vi &cc : scc->comps) for (int v : cc) {
			int i = v<n ? n + (~v) : v - n;
			if (!seen[i]) seen[i]=true, sol[i] = v>=n;
		}
		return true;
	}
};