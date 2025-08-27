struct sparse_table {
	vvi m;
	sparse_table(vi arr) {
		m.pb(arr);
		for (int b=0; (1<<(++b)) <= sz(arr); ) {
			int w = (1<<b), hw = w/2;
			m.pb(vi(sz(arr) - w + 1));
			for (int i = 0; i+w <= sz(arr); i++) {
				m[b][i] = min(m[b-1][i], m[b-1][i+hw]);
			}
		}
	}
	int query(int k, int r) { // query min in [l,r]
		int b = 31 - __builtin_clz(r-k);
		// for (b = 0; 1<<(b+1) <= r-k+1; b++);
		return min(m[b][k], m[b][r-(1<<b)+1]);
	}
};