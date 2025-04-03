const int MAXN = 100100;
const int SIGMA = 26;
const char BASE = 'a';
char *s = new char[MAXN];
struct state {
  int len, link, to[SIGMA];
} *st = new state[MAXN+2];
struct eertree {
  int last, size, n;
  eertree() : last(1), size(2), n(0) {
    st[0].len = st[0].link = -1;
    st[1].len = st[1].link = 0; }
  int extend() {
    char c = s[n++]; int p = last;
    while (n - st[p].len - 2 < 0 || c != s[n - st[p].len - 2])
      p = st[p].link;
    if (!st[p].to[c-BASE]) {
      int q = last = size++;
      st[p].to[c-BASE] = q;
      st[q].len = st[p].len + 2;
      do { p = st[p].link;
      } while (p != -1 && (n < st[p].len + 2 ||
               c != s[n - st[p].len - 2]));
      if (p == -1) st[q].link = 1;
      else st[q].link = st[p].to[c-BASE];
      return 1; }
    last = st[p].to[c-BASE];
    return 0; } };