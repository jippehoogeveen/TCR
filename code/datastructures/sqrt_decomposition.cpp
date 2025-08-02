struct segment {
  vi arr;
  segment(vi _arr) : arr(_arr) { } };
vector<segment> T;
int K;
void rebuild() {
  int cnt = 0;
  REP(i,sz(T))
    cnt += sz(T[i].arr);
  K = static_cast<int>(ceil(sqrt(cnt)) + 1e-9);
  vi arr(cnt);
  for (int i = 0, at = 0; i < sz(T); i++)
    REP(j,sz(T[i].arr))
      arr[at++] = T[i].arr[j];
  T.clear();
  for (int i = 0; i < cnt; i += K)
    T.pb(segment(vi(arr.begin()+i,
                           arr.begin()+min(i+K, cnt)))); }
int split(int at) {
  int i = 0;
  while (i < sz(T) && at >= sz(T[i].arr))
    at -= sz(T[i].arr), i++;
  if (i >= sz(T)) return sz(T);
  if (at == 0) return i;
  T.insert(T.begin() + i + 1,
      segment(vi(T[i].arr.begin() + at, T[i].arr.end())));
  T[i] = segment(vi(T[i].arr.begin(), T[i].arr.begin() + at));
  return i + 1; }
void insert(int at, int v) {
  vi arr; arr.push_back(v);
  T.insert(T.begin() + split(at), segment(arr)); }
void erase(int at) {
  int i = split(at); split(at + 1);
  T.erase(T.begin() + i); }