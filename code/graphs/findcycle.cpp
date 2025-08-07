vvi G;
vb vis, done;
vi p;
ii backedge(ll i) {
	vis[i] = true;
	for(ll j : G[i])
		if(!vis[j]) {
			p[j] = i;
			ii antw = backedge(j);
			if(antw.x != -1) return antw;
		}
		else if(!done[j]) return {i,j};
	done[i] = true;
	return {-1,-1}; }
//directed
vi findcycledir() {
	ll n = sz(G);
	vis = vb(n,false), done = vb(n,false);
	p = vi(n,-1);
	REP(i,n) if(!vis[i]) {
		ii antw = backedge(i);
		if(antw.x != -1) {
			vi c; ll v = antw.x, w = antw.y;
			c.pb(v);
			while(v != w) c.pb(v = p[v]);
			reverse(all(c));
			return c;
		}
	}
	return {}; }

//undirected
vi findcycleundir(const vvi &G, int v0) {
	vi p(sz(G), -1), s{v0};
	while (!s.empty()) {
		int v = s.back(); s.pop_back();
		for (int w : G[v])
			if (p[w] == -1) s.pb(w), p[w] = v;
			else if (w != p[v]) {
				vi c;
				while (v != w) c.pb(v = p[v]);
				return c;
			}
	}
	return {}; }