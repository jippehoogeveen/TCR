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

//cnt[sa.locstr(s)] = #distinct substrings of sa with prefix s
vi distinct(suffix_automaton& sa) {
  vi cnt = vi(sa.sz, 1); cnt[0] = 0;
  for(ll i : sa.topo)
    for(auto p : sa.next[i])
      cnt[i] += cnt[p.y];
  return cnt;
}

//cnt[sa.locstr(s)] = #locations of s in sa
vi occur(suffix_automaton& sa) {
  vi cnt = vi(sa.sz, 0);
  for(int cur = 0, i = 0; i < sz(sa.s); i++) {
    cnt[cur = sa.next[cur][sa.s[i]]]++; }
  for(ll i : sa.topo) cnt[sa.link[i]] += cnt[i];
  return cnt;
}

//return endpositions of occurrences of t (unsorted!)
vi location(suffix_automaton& sa, string& t) {
  int cur = sa.locstr(t);
  if(cur == -1) return vi();
  vi res, stack(1,cur);
  while(sz(stack) > 0) {
    cur = stack.back(), stack.pop_back();
    res.pb(sa.first[cur]);
    for(ll n : sa.linkinv[cur]) stack.pb(n); }
  return res; }

//find the longest common substring
string lcs(vs& s) {
  //Make the automaton
  vc extra;
  REP(i,sz(s))
    extra.pb(i + 256);//assert not in s!
  suffix_automaton sa;
  REP(i,sz(s)) {
    for(char c : s[i]) sa.extend(c);
    sa.extend(extra[i]);
  }
  sa.maketopo();
  sa.makelinkinvs();

  //Determine possible locations
  vvb pos; int cur;
  REP(i, sz(s)) {
    pos.pb(vb(sz(s[i]), false));
    vi stack; cur = sa.next[0][extra[i]];
    for(char c : s[i]) {
      cur = sa.next[cur][c]; stack.pb(cur);
    }
    while(sz(stack) > 0) {
      cur = stack.back(); stack.pop_back();
      if(!pos[i][cur]) {
        pos[i][cur] = true;
        for(ll p : sa.linkinv[cur]) stack.pb(p);
      }}}

  //Determine the answer
  for(ll i : sa.topo) {
    bool can = true;
    REP(j, sz(s)) if(!pos[j][i]) {
      can = false;
      break;}
    if(can)
      return sa.maxstring(i);//sa.length[i]
    } return ""; }