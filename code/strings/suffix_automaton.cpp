typedef vector<char> vc;
struct suffix_automaton {
  vi len, link;
  vi first, topo;//reversed topological ordering
  vector<map<char,int>> next;
  vi previd; vc prevc;
  vvi linkinv;
  int sz, last;
  string s;
  suffix_automaton() : len(1), link(1),
  next(1), first(1), previd(1), prevc(1) {
    sz = 1; last = 0; }
  suffix_automaton(string s) : suffix_automaton() {
    for(char c : s) extend(c);
    maketopo(); makelinkinvs();
  }
  void extend(char c){ s.pb(c);
    int cur = sz++; len.pb(len[last]+1); link.pb(0);
    next.pb(map<char,int>()); first.pb(sz(s));
    previd.pb(last); prevc.pb(c);
    int p = last;
    for(; p != -1 && !next[p].count(c); p = link[p])
      next[p][c] = cur;
    if(p != -1) { int q = next[p][c];
      if(len[p] + 1 == len[q]){ link[cur] = q; }
      else { int clone = sz++;
        len.pb(len[p] + 1); first.pb(first[q]);
        link.pb(link[q]); next.pb(next[q]);
        previd.pb(p); prevc.pb(c);
        for(; p != -1 && next[p].count(c) && next[p][c] == q;
              p = link[p]){
          next[p][c] = clone; }
        link[q] = link[cur] = clone;
      } } last = cur; }
  void makelinkinvs() {
    linkinv = vvi(sz);
    rep(i,1,sz) linkinv[link[i]].pb(i); }
  void maketopo() {
    topo.clear();
    topo = vi(sz); REP(i,sz) topo[i] = i;
    sort(all(topo), [&](ll a, ll b)
      { return len[a] > len[b]; });
  }
  int locstr(string& other){//returns location of other (or -1)
    int cur = 0;
    for(int i = 0; i < sz(other); ++i){
      if(cur == -1) return -1;
      cur = next[cur][other[i]]; }
    return cur; }
  string maxstring(int loc) {
    string res;
    while(loc > 0) {
      res.pb(prevc[loc]); loc = previd[loc]; }
    reverse(all(res)); return res;
  }
};