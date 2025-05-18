struct line { //Can be any pseudoline
    ll a, b;
    line(): a(0), b(0) {}
    line(ll _a, ll _b): a(_a), b(_b) {}
    bool overtakes(line l) { return a > l.a; }
    ll value(ll i) { return a * i + b; }
};

struct LiChaoTree {
    ll width;
    vector<line> tree; vi v;
    LiChaoTree(vi a) { //any increasing sequence
        for(width = 1; width < sz(a); width *= 2) ;
        v = vi(2 * width - 1);
        tree = vector<line>(2 * width - 1);
        REP(i, width)
          v[i + width - 1] = a[min(i, sz(a) - 1)];
        for(ll i = width - 2; i >= 0; i--)
          v[i] = v[2 * i + 2];
        for(ll i = 0; i < width - 1; i++)
          v[i] = v[2 * i + 1]; }
    void insert(line& l, ll i = 0) {
        if(i >= 2 * width - 1) return;
        line cur = tree[i];
        if(l.value(v[i]) > cur.value(v[i])) {
            tree[i] = l;
            swap(l,cur); }
        if(l.overtakes(cur)) insert(l, 2 * i + 2);
        else insert(l, 2 * i + 1); }
    ll query(ll i) { //query maximum value at a[i]
        ll k = (i + width - 1);
        ll res = tree[k].value(i);
        while(k > 0) {
            k = (k - 1) / 2;
            res = max(res, tree[k].value(i)); }
        return res; }
};