struct HLD {
	vvi adj; int cur_pos = 0;
	vi par, dep, hvy, head, pos;
	segmenttree st;

	HLD(int n, const vvi &A) : adj(all(A)), par(n),
		dep(n), hvy(n,-1), head(n), pos(n), st(n) {
		cur_pos = 0; dfs(0); decomp(0, 0);
	}

	int dfs(int v) { // determine parent/depth/sizes
		int wei = 1, mw = 0;
		for (int c : adj[v]) if (c != par[v]) {
			par[c] = v, dep[c] = dep[v]+1;
			int w = dfs(c);
			wei += w;
			if (w > mw) mw = w, hvy[v] = c;
		}
		return wei;
	}

	// pos: index in SegmentTree, head: root of path
	void decomp(int v, int h) {
		head[v] = h, pos[v] = cur_pos++;
		if (hvy[v] != -1) decomp(hvy[v], h);
		for (int c : adj[v])
			if (c != par[v] && c != hvy[v]) decomp(c, c);
	}

	void update(int i, ll v){ st.update(pos[i], v); }

	// requires queryST(a, b) = SUM{A[i] | a<=i<=b }.
	ll query(int a, int b) {
		ll res = 0;
		for (; head[a] != head[b]; b = par[head[b]]) {
			if (dep[head[a]] > dep[head[b]]) swap(a, b);
			res += st.query(pos[head[b]],pos[b]);
		}
		if (dep[a] > dep[b]) swap(a, b);
		return res + st.query(pos[a], pos[b]);
	}
};