double min_mean_cycle(vector<vector<pair<int,ld>>> adj){
  int n = sz(adj); ld mn = INFINITY;
  vvd arr(n+1, vd(n, mn));
  arr[0][0] = 0;
  rep(k,1,n+1) REP(j,n) for(auto p : adj[j])
    arr[k][p.x] = min(arr[k][p.x],p.y + arr[k-1][j]);
  REP(k,n) {
    ld mx = -INFINITY;
    REP(i,n) mx = max(mx, (arr[n][i]-arr[k][i])/(n-k));
    mn = min(mn, mx); }
  return mn; }