vi manacher(const string& s) {
    ll n = sz(s); vi res(2 * n - 1);
    ll k = 0, r = 0;
    REP(i, 2 * n - 1) {
        res[i] = i % 2;
        if(r > i) res[i] = res[r + k - i];
        if(i + res[i] >= r) {
            r = i + res[i];
            k = i - res[i];
            while(k >= 0 && r <= 2 * n - 2 && s[k / 2] == s[r / 2])
                r += 2, k -= 2;
            r -= 2; k += 2;
            res[i] = r - i; } }
    REP(i, 2 * n - 1) res[i]++;
    return res; }