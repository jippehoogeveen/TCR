vvi adj;
int n, m;
vi indeg, outdeg, res;
ii start_end() {
  int start = -1, end = -1, any = 0, c = 0;
  REP(i, n) {
    if(outdeg[i] > 0) any = i;
    if(indeg[i] + 1 == outdeg[i]) start = i, c++;
    else if(indeg[i] == outdeg[i] + 1) end = i, c++;
    else if(indeg[i] != outdeg[i]) return ii(-1,-1);
  }
  if ((start == -1) != (end == -1) || (c != 2 && c))
    return ii(-1,-1);
  if (start == -1) start = end = any;
  return ii(start, end); }
void makepath(ll i) {
  while(outdeg[i] > 0) makepath(adj[i][--outdeg[i]]);
  res.pb(i);
}
bool euler_path() {
  ii se = start_end();
  if (se.x == -1) return false;
  makepath(se.x); reverse(all(res));
  return (sz(res) == m + 1);
}