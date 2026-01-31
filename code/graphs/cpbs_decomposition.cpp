struct bicomp {
	vvi adj; int n;
	vi low, num, block, cp; vvi blocks;
	vii bs; int curnum;

	void dfs(int u, int p) {
		block.pb(u);
		low[u] = num[u] = curnum++;
		int cnt = 0; bool found = false;
		for(int v : adj[u]) {
			if (num[v] == -1) {
				dfs(v, u);
				low[u] = min(low[u], low[v]);
				cnt++;
				found = found || low[v] >= num[u];
				if (low[v] > num[u]) bs.eb(u, v);
				if(low[v] >= num[u]) {
					vi b2;
					while(true) {
						int cur = block.back(); block.pop_back();
						b2.pb(cur); if(cur == v) break;
					} b2.pb(u);
					if(low[v] == num[u]) blocks.pb(b2);//excludes bridges
				}
			} else if (p != v) low[u] = min(low[u], num[v]);
		}
		if (found && (p != -1 || cnt > 1)) cp.pb(u); }

	bicomp(vvi &_adj) : n(sz(_adj)), adj(_adj) {
		num = vi(n, -1); low = vi(n);
		curnum = 0;
		REP(i,n) if (num[i] < 0) dfs(i, -1); }

	vvi blockadj; vb iscut; set<ii> bsset;
	void addedge(ll u, ll v){ blockadj[u].pb(v); blockadj[v].pb(u); }
	void makecpdecomp() {
		for(ii p : bs) bsset.emplace(ii(min(p.x,p.y), max(p.x,p.y)));
		iscut = vb(n, false);
		for(ll x : cp) iscut[x] = true;
		REP(i, n) if(sz(adj[i]) <= 1) iscut[i] = true;
		blockadj = vvi(n + sz(blocks));
		REP(i, sz(blocks)) for(ll x : blocks[i])
			if(iscut[x]) addedge(i + n, x);
		for(ii p : bs) addedge(p.x, p.y); }

	vector<map<ll,vi>> inblockedge; vi wblock;
	void dfsbe(ll i, ll p) {
		for(ll j : blockadj[i])
			if(j != p && (i >= n || j >= n)) dfsbe(j, i);
		if(i >= n) {
			for(ll x : blocks[i - n]) wblock[x] = i - n;
			for(ll j : blockadj[i])
				if(j < n && j != p)
					for(ll k : adj[j])
						if(bsset.count(ii(min(j, k), max(j, k))) == 0)
							inblockedge[wblock[k]][j].pb(k);
		} }
	void makeblockedges() {
		inblockedge = vector<map<ll,vi>>(sz(blocks));
		REP(i, sz(blocks)) for(ll j : blocks[i]) inblockedge[i].emplace(j, vi());
		wblock = vi(n, -1);
		REP(i, sz(blocks)) {
			if (wblock[blocks[i][0]] == -1) dfsbe(i + n, -1);
			for(ll j : blocks[i])
				if(!iscut[j])
					for(ll k : adj[j])
						inblockedge[i][j].pb(k); }
	} };