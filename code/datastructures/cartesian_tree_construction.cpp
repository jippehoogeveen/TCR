//if points, sort(vii a) and compare .y in walk
vi a, l, r; ll root;
vi walk(vi& a, bool eq) {
    vi stack, res;
    REP(i, sz(a)) {
        ll b = -1;
        while(sz(stack) > 0) {
            if(a[i] > a[stack.back()] ||
              (eq && a[i] == a[stack.back()])) break;
            b = stack.back(); stack.pop_back();}
        stack.pb(i); res.pb(b);}
    return res; }
void constructtree() {
    l = walk(a, true);
    reverse(all(a));
    r = walk(a, false);
    reverse(all(r)); reverse(all(a));
    REP(i, sz(r)) if(r[i] != -1)
        r[i] = sz(a) - 1 - r[i];
    root = 0;
    REP(i,sz(a)) if(a[i] < a[root]) root = i; }