vector<multiset<int>> adj;
int n, m;
vi res;
ii start_end() {
  vi odd; int any = 0;
  REP(i,n) {
    if(sz(adj[i]) % 2 == 1) odd.pb(i);
    if(sz(adj[i]) > 0) any = i;
  }
  if(sz(odd) == 2) return ii(odd[0],odd[1]);
  if(sz(odd) == 0) return ii(any,any);
  return ii(-1,-1); }
void makepath(ll i) {
  while(sz(adj[i]) > 0) {
    ll j = *adj[i].begin();
    adj[i].erase(adj[i].find(j));
    adj[j].erase(adj[j].find(i));
    makepath(j); }
  res.pb(i);
}
bool euler_path() {
  ii se = start_end();
  if (se.x == -1) return false;
  makepath(se.x); reverse(all(res));
  return (sz(res) == m + 1); }