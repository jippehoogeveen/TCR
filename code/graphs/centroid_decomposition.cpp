struct centroid_decomposition {
  int n; vvi adj;
  vvi parent, dist;
  vi sz, sepdepth;
  vvi children, tree;
  int logn, center;
  centroid_decomposition(int _n): n(_n), adj(n) {
    for(logn = 0; (1 << logn) < n; logn++);
    logn++;
    parent = dist = children = tree = vvi(n, vi(logn));
    sz = sepdepth = vi(n);
  }
  void add_edge(int a, int b) {
    adj[a].pb(b); adj[b].pb(a);
  }
  int dfs(int u, int p) {
    sz[u] = 1;
    for(int v : adj[u])
      if(v != p)
        sz[u] += dfs(v, u);
    return sz[u];
  }
  void makepaths(int sep, int u, int p, int len) {
    parent[u][sepdepth[sep]] = sep, dist[u][sepdepth[sep]] = len;
    int bad = -1;
    REP(i, sz(adj[u])) {
      if(adj[u][i] == p) bad = i;
      else makepaths(sep, adj[u][i], u, len + 1);
    }
    if(p == sep)
      swap(adj[u][bad], adj[u].back()), adj[u].pop_back();
  }
  int findcentroid(int u, int sep) {
    for(int v : adj[sep])
      if(sz[v] < sz[sep] && sz[v] > sz[u] / 2)
        return findcentroid(u, v);
    return sep;
  }
  int separate(int h, int u) {
    dfs(u, -1); int sep = findcentroid(u, u);
    sepdepth[sep] = h, makepaths(sep, sep, -1, 0);
    for(int v : adj[sep]) separate(h + 1, v);
    return sep;
  }
  void makeDecomp() {
    center = separate(0,0);
    REP(i,n) children[i].clear(), tree[i].clear();
    REP(i,n) {
      if(sepdepth[i] != 0)
        children[parent[i][sepdepth[i] - 1]].pb(i);
      REP(j, sepdepth[i] + 1)
          tree[parent[i][j]].pb(i); }
  }
};