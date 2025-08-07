#include "../datastructures/union_find.cpp"
struct arborescence {
  int n; dsu uf;
  vector<vector<pair<ii,ll> > > adj;
  arborescence(int _n) : n(_n), uf(n), adj(n) { }
  void add_edge(int a, int b, ll c) {
    adj[b].eb(ii(a,b),c); }
  vi find_min(int r) {
    vi vis(n,-1), mn(n,LLONG_MAX); vi par(n, -1);
    REP(i, n) {
      if (uf.find(i) != i) continue;
      int at = i;
      while (at != r && vis[at] == -1) {
        vis[at] = i;
        for (auto it : adj[at])
          if (it.y < mn[at] && uf.find(it.x.x) != at)
            mn[at] = it.y, par[at] = it.x.x;
        if (par[at] == -1) return vi();
        at = uf.find(par[at]);
      }
      if (at == r || vis[at] != i) continue;
      dsu tmp = uf;
      vi seq;
      do seq.pb(at), at = uf.find(par[at]);
      while (at != seq.front());
      int c = uf.find(seq[0]);
      for (auto it : seq) uf.unite(it, c);
      for (auto &jt : adj[c]) jt.y -= mn[c];
      for (auto it : seq) {
        if (it == c) continue;
        for (auto jt : adj[it])
          adj[c].eb(jt.x, jt.y - mn[it]);
        adj[it].clear();
      }
      vi rest = find_min(r);
      if (rest.empty()) return rest;
      ll use = rest[c];
      rest[at = tmp.find(c)] = use;
      for (int it : seq) if (it != at)
        rest[it] = par[it];
      return rest;
    }
    return par; } };