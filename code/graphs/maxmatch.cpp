vb vis; vi L, R; vvi G; // L->{R,...}
void addedge(int a, int b) { G[a].pb(b);}
bool match(int u) {
	for (int v : G[u]) {
		if (vis[v]) continue;
		vis[v] = true;
		if (R[v] == -1 || match(R[v]))
		{ R[v] = u, L[u] = v; return true; }
	}
	return false; }
// perfect matching iff ret == n == m
int maxmatch(int n, int m) {
	L.assign(n, -1);
	R.assign(m, -1);
	int ret = 0;
	REP(i, n) vis.assign(m, false), ret += match(i);
	return ret; }