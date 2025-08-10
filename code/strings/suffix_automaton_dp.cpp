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