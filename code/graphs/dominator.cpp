vvi g, grev, bucket;
vi pos, order, par, sdom, p, best, idom, lnk;
int cnt;

void create(ll n) {
	g = vvi(n), grev = vvi(n), bucket = vvi(n);
	pos = vi(n, -1), order = vi(n), par = vi(n), sdom = vi(n);
	p = vi(n), best = vi(n), idom = vi(n), lnk = vi(n);
}

void addedge(int a, int b) {
	g[a].pb(b), grev[b].pb(a);
}

void dfs(int v) {
	pos[v] = cnt;
	order[cnt++] = v;
	for (int u : g[v])
		if (pos[u] < 0) par[u] = v, dfs(u);
}

int find_best(int x) {
	if (p[x] == x) return best[x];
	int u = find_best(p[x]);
	if (pos[sdom[u]] < pos[sdom[best[x]]])
		best[x] = u;
	p[x] = p[p[x]];
	return best[x];
}

void dominators(int n, int root) {
	pos = vi(n,-1);
	cnt = 0;
	dfs(root);
	REP(i, n) p[i] = best[i] = sdom[i] = i;

	for (int it = cnt - 1; it >= 1; it--) {
		int w = order[it];
		for (int u : grev[w]) {
			if(pos[u] == -1) continue;
			int t = find_best(u);
			if (pos[sdom[t]] < pos[sdom[w]])
				sdom[w] = sdom[t];
		}
		bucket[sdom[w]].pb(w);
		idom[w] = sdom[w];
		for (int u : bucket[par[w]])
			lnk[u] = find_best(u);
		bucket[par[w]].clear();
		p[w] = par[w];
	}

	for (int it = 1; it < cnt; it++) {
		int w = order[it];
		idom[w] = idom[lnk[w]];
	}
	REP(i,n) if(pos[i] == -1) idom[i] = -1;
	idom[root] = root;
}