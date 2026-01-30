struct cpdecomp {
    ll n; vvi adj;
    set<ii> bs; vb cut, split;
    vb seen; vi depth;
    vvi comps, adjcomp;
    cpdecomp(vvi& _adj) : n(sz(_adj)) {
        pair<vi, vii> cpbs = cut_points_and_bridges(_adj);
        for(ii b : cpbs.y) bs.emplace(ii(min(b.x,b.y), max(b.x,b.y)));
        cut = split = vb(n, false);
        for(ll c : cpbs.x) cut[c] = true;
        REP(i, n) if(sz(_adj[i]) == 1) cut[i] = true;
        adj = vvi(n);
        REP(i, n) for(ll j : _adj[i])
            if(bs.count(ii(min((ll)i,j), max((ll)i,j))) == 0)
                adj[i].pb(j);
        decomp();
    }
    void decomp() {
        adjcomp = vvi(n); seen = vb(n, false); depth = vi(n);
        REP(i, n) if(!seen[i]){
            vi c; makecomp(i, c, -1); decomp(c);
        }
        for(ii b : bs) addedge(b.x, b.y);
    }
    void decomp(vi& c) {
        vi cp;
        for(ll x : c) if(cut[x] && !split[x]) cp.pb(x);
        if(sz(cp) == 0) {
            comps.pb(c); adjcomp.pb(vi());
            for(ll x : c) if(cut[x]) addedge(x, sz(comps) - 1 + n);
            return;
        }
        for(ll x : c) {
            seen[x] = false;
            depth[x]++;
        }
        ll s = cp[rand() % sz(cp)];
        split[s] = true;
        for(ll i : adj[s]) if(!seen[i]) {
            seen[s] = false; vi d;
            makecomp(i, d, s); decomp(d);
        }
        for(ll x : c) depth[x]--;
    }
    void makecomp(ll i, vi& c, ll s) {
        if(seen[i]) return;
        seen[i] = true; c.pb(i);
        if(i == s) return;
        for(ll j : adj[i])
            if(depth[j] == depth[i])
                makecomp(j, c, s);
    }
    void addedge(ll u, ll v) { adjcomp[u].pb(v); adjcomp[v].pb(u); }
};