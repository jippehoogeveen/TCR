const int sigma = 26;
const char base = 'a';
struct state {
  int len, link, to[sigma];
};
struct eertree {
  int last, size, n;
  vector<state> nodes;
  string s;
  eertree() : last(1), size(2), n(0) {
    nodes.pb({-1,-1});
    nodes.pb({0,0}); }
  void extend(char c) {
    s.pb(c); n++; int p = last;
    while (n - nodes[p].len - 2 < 0 || c != s[n - nodes[p].len - 2])
      p = nodes[p].link;
    if (!nodes[p].to[c-base]) {
      int q = last = size++;
      nodes.pb({nodes[p].len + 2, 1});
      nodes[p].to[c-base] = q;
      do { p = nodes[p].link;
      } while (p != -1 && (n < nodes[p].len + 2 ||
               c != s[n - nodes[p].len - 2]));
      if(p != -1) nodes[q].link = nodes[p].to[c-base]; }
    else
      last = nodes[p].to[c-base];
  }};