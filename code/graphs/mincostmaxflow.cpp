struct edge { ll x, y, f, c, w; };
ll V; vi par, D; vector<edge> g;
vvi e;
void create(ll n)  {
	V = n; e = vvi(n);
	par = vi(n), D = vi(n);
}
inline void addEdge(int u, int v, ll c, ll w) {
	e[u].pb(sz(g));	g.pb({u, v, 0, c, w});
	e[v].pb(sz(g)); g.pb({v, u, 0, 0, -w});
}

void spBF(int s) {
	D = vi(V,LLONG_MAX); D[s] = 0;
	for (int ng = g.size(), _ = V; _--; ) {
		bool ok = false;
		for (int i = 0; i < ng; i++)
			if (D[g[i].x] != LLONG_MAX && g[i].f < g[i].c && D[g[i].x] + g[i].w < D[g[i].y]) {
				D[g[i].y] = D[g[i].x] + g[i].w;
				par[g[i].y] = i; ok = true;
			}
		if (!ok) break;
	}
}

//Can be omitted if n small enough
void spDijk(int s) {
	vi ed(V,LLONG_MAX); ed[s] = 0;
	set<ii> front{ii(0,s)};
	while(sz(front) > 0) {
		ll v = front.begin()->y;
		front.erase(front.begin());
		for(ll i : e[v]) if(g[i].f < g[i].c) {
			ll y = g[i].y, now = g[i].w + ed[v] - D[y] + D[v];
			if(now < ed[y]) {
				front.erase(ii(ed[y],y));
				ed[y] = now;
				front.emplace(ii(now,y));
				par[y] = i;
			}
		}
	}
	REP(i,V)
		if(ed[i] < LLONG_MAX) D[i] += ed[i];
		else D[i] = LLONG_MAX;
}

void minCostMaxFlow(int s, int t, ll &c, ll &f) {
	spBF(s);
	for (c = f = 0; spDijk(s), D[t] < LLONG_MAX; ) {
		ll df = LLONG_MAX, dc = 0;
		for (int v = t, e; e = par[v], v != s; v = g[e].x) df = min(df, g[e].c - g[e].f);
		for (int v = t, e; e = par[v], v != s; v = g[e].x) g[e].f += df, g[e^1].f -= df, dc += g[e].w;
		f += df; c += dc * df;
	}
}