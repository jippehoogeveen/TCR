struct GHTree {
  Dinic d; int n;
  vvii tree;
  GHTree(int _n) : n(_n), d(_n){ }
  void addEdge(int u, int v, int c) {
    d.addEdge(u, v, c); d.G.back().c = c;
  }
  ll build(vi& nodes) {
    if(sz(nodes) == 1) return nodes[0];
    d.resetflow(); ll f = d.maxflow(nodes[0], nodes[1]);
    vb cut = d.mincut(nodes[0], nodes[1]);
    vi n1, n2;
    for(ll i : nodes)
      if(cut[i]) n1.pb(i);
      else n2.pb(i);
    ll p1 = build(n1), p2 = build(n2);
    tree[p1].eb(p2, f);
    tree[p2].eb(p1, f);
    if(cut[0]) return p1;
    return p2;
  }
  void buildTree() {
    tree = vvii(n);
    vi nodes; REP(i, n) nodes.pb(i);
    build(nodes);
  }
  void dfsedge(int i, int p, vector<tuple<int,int,ll>>& prev) {
    for(ii e : tree[i])
      if(e.x != p) {
        prev[e.x] = {i, e.x, e.y};
        dfsedge(e.x, i, prev);
      }
  }
  tuple<int, int, ll> findtreecut(int s, int t) {
    vector<tuple<int,int,ll>> prev(n); dfsedge(s, -1, prev);
    int small = t;
    for(int c = t; c != s; c = get<0>(prev[c]))
      if(get<2>(prev[c]) < get<2>(prev[small]))
        small = c;
    return prev[small];
  }
  ll maxflow(int s, int t) {
    auto e = findtreecut(s, t); return get<2>(e);
  }
  void dfscut(int i, int p, vb& cut) {
    cut[i] = true;
    for(ii e : tree[i])
      if(e.x != p) dfscut(e.x, i, cut);
  }
  vb mincut(int s, int t) {
    auto e = findtreecut(s, t);
    vb cut = vb(n, false); dfscut(get<0>(e), get<1>(e), cut);
    return cut;
  }
};