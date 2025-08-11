const ll oo = 1e9;
int N, R;
vector<vii> g;
vi pred, label, node, helper;

int get_node(int n) {
	return node[n] == n ? n :
			(node[n] = get_node(node[n]));
}

ll update_node(int n) {
	ll m = oo;
	for (auto ed : g[n]) m = min(m, ed.y);
	REP(j, sz(g[n])) {
		g[n][j].y -= m;
		if (g[n][j].y == 0)
			pred[n] = g[n][j].x;
	}
	return m;
}

ll cycle(vi &active, int n, int &cend) {
	n = get_node(n);
	if (label[n] == 1) return false;
	if (label[n] == 2) { cend = n; return 0; }

	active.pb(n);
	label[n] = 2;
	auto res = cycle(active, pred[n], cend);
	if (cend == n) {
		int F = find(all(active), n)-active.begin();
		vi todo(active.begin() + F, active.end());
		active.rs(F);
		vii newg;
		for (auto i: todo) node[i] = n;
		for (auto i: todo) for(auto &ed : g[i])
			helper[ed.x = get_node(ed.x)] = ed.y;
		for (auto i: todo) for(auto ed : g[i])
			helper[ed.x] = min(ed.y, helper[ed.x]);
		for (auto i: todo) for(auto ed: g[i]) {
			if (helper[ed.x] != oo && ed.x != n) {
				newg.eb(ed.x, helper[ed.x]);
				helper[ed.x] = oo;
			}
		}
		g[n] = newg;
		res += update_node(n);
		label[n] = 0;
		cend = -1;
		return cycle(active, n, cend) + res;
	}
	if (cend == -1) {
		active.pop_back();
		label[n] = 1;
	}
	return res;
}

// Calculates value of minimal arborescence from R,
// assuming it exists.
// adj[i] contains (j, v) with edge i -> j with value v
// pred[i] is parent in arborescence
ll min_arbor(vector<vii>& adj, int r) {
	N = sz(adj); R = r; g = vector<vii>(N);
	REP(i, N) for(ii p : adj[i]) g[p.x].eb(i,p.y);
	pred = label = node = helper = vi(N);
	ll res = 0;
	REP(i, N) {
		node[i] = i;
		if (i != R) res += update_node(i);
	}
	REP(i, N) label[i] = (i==R);
	REP(i, N) {
		if (label[i] == 1 || get_node(i) != i)
			continue;
		vi active;
		int cend = -1;
		res += cycle(active, i, cend);
	}
	return res;
}