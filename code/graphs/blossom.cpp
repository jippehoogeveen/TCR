vb marked;
vvb emarked;
vi S;
ll n;
vi find_augmenting_path(const vvi &adj,const vi &m){
  int n = sz(adj), s = 0;
  vi par(n,-1), height(n), root(n,-1), q, a, b;
  marked = vb(n,false);
  emarked = vvb(n,vb(n,false));
  REP(i,n) if (m[i] >= 0) emarked[i][m[i]] = true;
             else root[i] = i, S[s++] = i;
  while (s) {
    int v = S[--s];
    for(ll w:adj[v]) {
      if (emarked[v][w]) continue;
      if (root[w] == -1) {
        int x = S[s++] = m[w];
        par[w]=v, root[w]=root[v], height[w]=height[v]+1;
        par[x]=w, root[x]=root[w], height[x]=height[w]+1;
      } else if (height[w] % 2 == 0) {
        if (root[v] != root[w]) {
          while(v != -1) q.pb(v), v = par[v];
          reverse(all(q));
          while(w != -1) q.pb(w), w = par[w];
          return q;
        } else {
          int c = v;
          while(c != -1) a.pb(c), c = par[c];
          c = w;
          while(c != -1) b.pb(c), c = par[c];
          while(!a.empty() && !b.empty() && a.back() == b.back())
            c = a.back(), a.pop_back(), b.pop_back();
          marked = vb(n,false);
          fill(par.begin(), par.end(), 0);
          for(ll it : a) par[it] = 1; for(ll it : b) par[it] = 1;
          par[c] = s = 1;
          REP(i,n) root[par[i] = par[i] ? 0 : s++] = i;
          vvi adj2(s);
          REP(i,n) for(ll it : adj[i]) {
            if (par[it] == 0) continue;
            if (par[i] == 0) {
              if (!marked[par[it]])  {
                adj2[par[i]].pb(par[it]);
                adj2[par[it]].pb(par[i]);
                marked[par[it]] = true; }
            } else adj2[par[i]].pb(par[it]); }
          vi m2(s, -1);
          if (m[c] != -1) m2[m2[par[m[c]]] = 0] = par[m[c]];
          REP(i,n) if(par[i]!=0 && m[i]!=-1 && par[m[i]]!=0)
            m2[par[i]] = par[m[i]];
          vi p = find_augmenting_path(adj2, m2);
          int t = 0;
          while (t < sz(p) && p[t]) t++;
          if (t == sz(p)) {
            REP(i,sz(p)) p[i] = root[p[i]];
            return p; }
          if (!p[0] || (m[c] != -1 && p[t+1] != par[m[c]]))
            reverse(all(p)), t = sz(p)-t-1;
          rep(i,0,t) q.pb(root[p[i]]);
          for(ll it : adj[root[p[t-1]]]) {
            if (par[it] != (s = 0)) continue;
            a.pb(c), reverse(all(a));
            for(ll jt : b) a.pb(jt);
            while (a[s] != it) s++;
            if ((height[it] & 1) ^ (s < sz(a) - sz(b)))
              reverse(all(a)), s = sz(a)-s-1;
            while(a[s]!=c)q.pb(a[s]),s=(s+1)%size(a);
            q.pb(c);
            rep(i,t+1,size(p)) q.pb(root[p[i]]);
            return q; } } }
      emarked[v][w] = emarked[w][v] = true; }
    marked[v] = true; } return q; }
vii max_matching(const vector<vi> &adj) {
  n = sz(adj);
  marked = vb(n);
  emarked = vvb(n,vb(n));
  S = vi(n);
  vi m(size(adj), -1), ap; vii res, es;
  REP(i,size(adj)) for(ll it:adj[i]) es.eb(i,it);
  random_shuffle(all(es));
  for(ii it: es) if (m[it.x] == -1 && m[it.y] == -1)
    m[it.x] = it.y, m[it.y] = it.x;
  do { ap = find_augmenting_path(adj, m);
       REP(i,size(ap)) m[m[ap[i^1]] = ap[i]] = ap[i^1];
  } while (!ap.empty());
  REP(i,size(m)) if (i < m[i]) res.eb(i, m[i]);
  return res; }