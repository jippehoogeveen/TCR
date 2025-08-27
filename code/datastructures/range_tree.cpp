struct rangetree {
    vi xtop, ytop;
    vi l, r; vvi lind, rind;
    ll base;
    rangetree(vii p) {
        sort(all(p));
        for(base = 1; base < sz(p); base *= 2);
        l = r = vi(2 * base - 1);
        lind = rind = vvi(2 * base - 1);
        ytop = build(p, 0, sz(p) - 1, 0);
        for(ii pt : p) xtop.pb(pt.x); }
    vi build(vii& p, ll _l, ll _r, ll i) {
        l[i] = _l, r[i] = _r;
        if(_l == _r) { return {p[_l].y}; }
        ll m = (_l + _r) / 2;
        vi left = build(p, _l, m, 2 * i + 1), right = build(p, m + 1, _r, 2 * i + 2);
        ll il = 0, ir = 0; vi res;
        while(il < sz(left) || ir < sz(right)) {
            lind[i].pb(il); rind[i].pb(ir);
            if(il < sz(left) && (ir == sz(right) || left[il] <= right[ir])) {
                res.pb(left[il]);
                il++; }
            else {
                res.pb(right[ir]);
                ir++; } }
        lind[i].pb(il); rind[i].pb(ir); return res; }
    ll nexti(vi& a, ll v) {//first i with a[i] >= v
        ll k = -1, r = sz(a), m;
        while(r - k > 1) {
            m = (k + r) / 2;
            if(a[m] < v) k = m;
            else r = m; }
        return r; }
    ll q(ll iy, ll _l, ll _r, ll i) {
        if(l[i] > _r || r[i] < _l) return 0;
        if(l[i] >= _l && r[i] <= _r) return iy;
        return q(lind[i][iy], _l, _r, 2 * i + 1) + q(rind[i][iy], _l, _r, 2 * i + 2); }
    //query #points in [xl, xr] x [yl, yr]
    ll query(ll xl, ll xr, ll yl, ll yr) {
        ll k = nexti(xtop, xl), r = nexti(xtop, xr + 1) - 1;
        ll y1 = nexti(ytop, yl), y2 = nexti(ytop, yr + 1);
        return q(y2, k, r, 0) - q(y1, k, r, 0); }};